library IEEE;
use IEEE.std_logic_1164.all;
USE IEEE.numeric_std.all;

entity single_cycle is
end single_cycle;

architecture structural of single_cycle is

component adder is
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

component alu is
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Op: in STD_LOGIC_VECTOR (1 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0);
		Zero: out STD_LOGIC;
		Ovf: out STD_LOGIC
	);
end component;

component and_2 is
	port (
		i0, i1 : in std_logic;
		output : out std_logic
	);
end component;

component pc is
	port (
		next_pc : in std_logic_vector(31 downto 0);
		clk : in std_logic;
		cur_pc : out std_logic_vector(31 downto 0)
	);
end component;

component clock is
	port (
		clk : out std_logic
	);
end component;

component control_unit is 
	port(
		Opcode : in std_logic_vector (5 downto 0);
		Funct : in std_logic_vector (5 downto 0);
		RegDst, Branch, MemRead, MemToReg, MemWrite, ALUSrc, RegWrite, Jump : out std_ulogic;
		ALUOp : out std_logic_vector (1 downto 0)
	);
end component;

component j_concat
	port (
		pc_plus_4 : in std_logic_vector(31 downto 0);
		inst_lower : in std_logic_vector(25 downto 0);
		jump_to : out std_logic_vector(31 downto 0)
	);
end component;

component memory is 
	port (
		address, write_data: in STD_LOGIC_VECTOR (31 downto 0);
		MemWrite, MemRead: in STD_LOGIC;
		read_data: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

component instruction_memory is
	port (
		address: in STD_LOGIC_VECTOR (31 downto 0);
		read_data: out STD_LOGIC_VECTOR (31 downto 0);
		opcode: out std_logic_vector(5 downto 0);
		rs: out std_logic_vector(4 downto 0);
		rt: out std_logic_vector(4 downto 0);
		rd: out std_logic_vector(4 downto 0);
		im: out std_logic_vector(15 downto 0);
		funct: out std_logic_vector(5 downto 0)
	);
end component;


component multiplexer_2 is
	port (
		i0: in std_logic_vector(31 downto 0);
		i1: in std_logic_vector(31 downto 0);
		sel: in std_logic;
		output: out std_logic_vector(31 downto 0)
	);
end component;

component multiplexer_2_5bit is
	port (
		i0: in std_logic_vector(4 downto 0);
		i1: in std_logic_vector(4 downto 0);
		sel: in std_logic;
		output: out std_logic_vector(4 downto 0)
	);
end component;

component regFile is
	port (
		clk : in std_logic;
		readReg1,readReg2, writeReg: in STD_LOGIC_VECTOR (4 downto 0); 
		write_data: in STD_LOGIC_VECTOR (31 downto 0);
		RegWrite: in STD_LOGIC;
		read_data1, read_data2: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

component sign_extend is
	port (
		input  : in std_logic_vector(15 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end component;

component sl2 is
	port (
		input  : in std_logic_vector(31 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end component;

----
signal  clock_signal,
	branch_mux_select,
	c_regdst,
	c_branch,
	c_memread,
	c_memtoreg,
	c_memwrite,
	c_alusrc,
	c_regwrite,
	c_jump,
	
	zero_out,
	ovf_out
	: std_logic;
	
signal  pc_in,
	pc_out,
	pc_plus_4_out,
	sl2_out,
	branch_mux_in_1,
	branch_mux_out,
	
	i_mem_out,
	
	reg_out_1,
	reg_out_2,
	reg_write_data,
	
	sign_extend_out,
	
	alu_mux_out,
	alu_out,
	mem_out,
	
	jump_address
	: std_logic_vector(31 downto 0);

signal c_aluop
	: std_logic_vector(1 downto 0);
	
signal 	i_mem_op,
	i_mem_funct
	: std_logic_vector(5 downto 0);

signal	i_mem_rs,
	i_mem_rt,
	i_mem_rd,
	regwrite_mux_out
	: std_logic_vector(4 downto 0);

signal  i_mem_im
	: std_logic_vector(15 downto 0);
----

begin
	clk :
		clock port map(clock_signal);
	prog_c :
		pc port map(pc_in, clock_signal, pc_out);
	pc_plus_4 :
		adder port map(pc_out, X"00000004", pc_plus_4_out);
	branch_adder:
		adder port map(pc_plus_4_out, sl2_out, branch_mux_in_1);
	branch_mux:
		multiplexer_2 port map(pc_plus_4_out, branch_mux_in_1, branch_mux_select, branch_mux_out);
	branch_mux_sel:
		and_2 port map(c_branch, zero_out, branch_mux_select);
	j_calc:
		j_concat port map(pc_plus_4_out, i_mem_out(25 downto 0),jump_address);
	jump_mux:
		multiplexer_2 port map(branch_mux_out, jump_address, c_jump, pc_in);
	i_mem:
		instruction_memory port map(pc_out, i_mem_out, i_mem_op, i_mem_rs, i_mem_rt, i_mem_rd, i_mem_im, i_mem_funct);
	control:
		control_unit port map(i_mem_op, i_mem_funct, c_regdst, c_branch, c_memread, c_memtoreg, c_memwrite, c_alusrc, c_regwrite, c_jump, c_aluop);
	reg_mux:
		multiplexer_2_5bit port map(i_mem_rt, i_mem_rd, c_regdst, regwrite_mux_out); -- check order
	registers:
		regFile port map(clock_signal, i_mem_rs, i_mem_rt, regwrite_mux_out, reg_write_data, c_regwrite, reg_out_1, reg_out_2);
	sign_ext:
		sign_extend port map(i_mem_im, sign_extend_out);
	sleft:
		sl2 port map (sign_extend_out, sl2_out);
	alu_mux:
		multiplexer_2 port map(reg_out_2, sign_extend_out, c_alusrc, alu_mux_out);
	main_alu:
		alu port map(reg_out_1, alu_mux_out, c_aluop, alu_out, zero_out, ovf_out);
	data_mem:
		memory port map(alu_out, reg_out_2, c_memwrite, c_memread, mem_out);
	mem_mux:
		multiplexer_2 port map(alu_out, mem_out, c_memtoreg, reg_write_data);
end structural;



