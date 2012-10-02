library IEEE;
use IEEE.std_logic_1164.all;

entity control_unit_tb is
end control_unit_tb;

architecture structural of control_unit_tb is

component control_unit is 
	port(
		Opcode : in std_logic_vector (5 downto 0);
		RegDst, Branch, MemRead, MemToReg, MemWrite, ALUSrc, RegWrite : out std_ulogic;
		ALUOp : out std_logic_vector (1 downto 0)
	);
end component;

signal	Opcode_input : std_logic_vector(5 downto 0);
begin

uut : control_unit
	port map(
		Opcode => Opcode_input
	);

		tb: 
	process begin
		-- R-type
		Opcode_input <= "000000";
		wait for 10 ns;
		-- addi
		Opcode_input <= "001000";
		wait for 10 ns;
		-- lw
		Opcode_input <= "100011";
		wait for 10 ns;
		-- beq
		Opcode_input <= "000100";
		wait for 10 ns;
		-- j
		Opcode_input <= "000010";
		wait for 10 ns;
		-- sw
		Opcode_input <= "101011";
		wait for 10 ns;
		-- INVALID test
		Opcode_input <= "111111";
		wait for 10 ns;
		wait;
	end process;
end structural;

