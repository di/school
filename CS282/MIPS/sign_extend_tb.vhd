library IEEE;
use IEEE.std_logic_1164.all;

entity sign_extend_tb is
end sign_extend_tb;

architecture structural of sign_extend_tb is

component sign_extend is 
	port (
		input  : in std_logic_vector(15 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end component;

signal input_in : std_logic_vector(15 downto 0);
signal output_out : std_logic_vector(31 downto 0);

begin
uut : sign_extend
	port map(
		input => input_in,
		output => output_out
	);

		tb: 
	process begin
		input_in <= "0000000000110001";
		wait for 10 ns;
		input_in <= "0000000000011011";
		wait for 10 ns;
		input_in <= "1000000000011011";
		wait for 10 ns;
		wait;
	end process;
end structural;
