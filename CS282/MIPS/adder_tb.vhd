library IEEE;
use IEEE.std_logic_1164.all;

entity adder_tb is
end adder_tb;

architecture structural of adder_tb is

component adder is 
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

signal	a_in, b_in, res_out : std_logic_vector(31 downto 0);

begin
uut : adder
	port map(
		a => a_in,
		b => b_in,
		Result => res_out
	);

		tb: 
	process begin
		a_in <= X"00000000";
		b_in <= X"00000000";
		wait for 10 ns;
		a_in <= X"00000002";
		b_in <= X"00000003";
		wait for 10 ns;
		a_in <= X"00000005";
		b_in <= X"0000000A";
		wait for 10 ns;
		a_in <= "11111111111111111111111111111100";
		b_in <= "11111111111111111111111111111101";
		wait for 10 ns;
		a_in <= "11111111111111111111111111111110";
		b_in <= "00000000000000000000000000000100";
		wait for 10 ns;
		wait;
	end process;
end structural;

