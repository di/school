library IEEE;
use IEEE.std_logic_1164.all;

entity sl2_tb is
end sl2_tb;

architecture structural of sl2_tb is

component sl2 is 
	port (
		input  : in std_logic_vector(31 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end component;

signal input_in : std_logic_vector(31 downto 0);
signal output_out : std_logic_vector(31 downto 0);

begin
uut :  sl2
	port map(
		input => input_in,
		output => output_out
	);

		tb: 
	process begin
		input_in <= X"00000005";
		wait for 10 ns;
		input_in <= X"80110001";
		wait for 10 ns;
		input_in <= X"000000A2";
		wait for 10 ns;
		wait;
	end process;
end structural;
