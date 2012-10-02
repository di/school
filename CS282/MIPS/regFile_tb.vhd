library IEEE;
use IEEE.std_logic_1164.all;

entity regFile_tb is
end regFile_tb;

architecture structural of regFile_tb is

component regFile is 
	port (
		clk : in std_logic;
		readReg1,readReg2, writeReg: in STD_LOGIC_VECTOR (4 downto 0); 
		write_data: in STD_LOGIC_VECTOR (31 downto 0);
		RegWrite: in STD_LOGIC;
		read_data1, read_data2: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

signal	readReg1_in, readReg2_in, writeReg_in : std_logic_vector(4 downto 0);
signal  write_data_in, data1_out, data2_out: std_logic_vector (31 downto 0); 
signal  RegWrite_in: std_logic; 
signal clk_in : std_logic := '0';
begin

uut : regFile
	port map(
		clk => clk_in,
		readReg1 => readReg1_in,
		readReg2 => readReg2_in, 
		writeReg => writeReg_in, 
		write_data => write_data_in,
		RegWrite => RegWrite_in, 
		read_data1 => data1_out, 
		read_data2 => data2_out
	);

		tb: 
	process begin
		clk_in <= '0' after 0 ns;
		writeReg_in <= "00010";
		write_data_in <= X"00000003";
		-- $r2 = 0
		clk_in <= '1'; -- $r2 = 3
		wait for 10 ns;
		clk_in <= '0';
		readReg1_in <= "00011";
		writeReg_in <= "00010";
		write_data_in <= data1_out;
		wait for 10 ns;
		clk_in <= '1'; -- $r2 = 3 or 0
		wait for 10 ns;
		clk_in <= '0';
		wait;
	end process;
end structural;



