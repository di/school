library IEEE;
use IEEE.std_logic_1164.all;

entity multiplexer_2_tb is
end multiplexer_2_tb;

architecture structural of  multiplexer_2_tb is

component multiplexer_2 is
	port (
		i0: in std_logic_vector(31 downto 0);
		i1: in std_logic_vector(31 downto 0);
		sel: in std_logic;
		output: out std_logic_vector(31 downto 0)
	);
end component;

signal i0_in, i1_in, output_out :  std_logic_vector(31 downto 0);
signal sel_in : std_logic;

begin

TB : multiplexer_2
	port map(
		i0 => i0_in,
		i1 => i1_in,
		sel => sel_in,
		output => output_out
	);
	
	process begin
		i0_in <= X"0000000A";
		i1_in <= X"0000000B";
		sel_in <= '0';
		wait for 10 ns;
		sel_in <= '1';
		wait for 10 ns;
		sel_in <= '0';
		wait;
	end process;
end structural;
