library IEEE;
use IEEE.std_logic_1164.all;

entity j_concat_tb is
end j_concat_tb;

architecture structural of j_concat_tb is

component j_concat is 
	port (
		pc_plus_4 : in std_logic_vector(31 downto 0);
		inst_lower : in std_logic_vector(25 downto 0);
		jump_to : out std_logic_vector(31 downto 0)
	);
end component;

signal	pc_plus_4_in, jump_to_out: std_logic_vector(31 downto 0);
signal  inst_lower_in : std_logic_vector(25 downto 0);

begin
uut : j_concat
	port map(
		pc_plus_4 => pc_plus_4_in,
		inst_lower => inst_lower_in,
		jump_to => jump_to_out
	);

		tb: 
	process begin
		pc_plus_4_in <= "10111000000000000000000000000000";
		inst_lower_in <= "00000000000000000000000101";
		wait for 20 ns;
		wait;
	end process;
end structural;
