library IEEE;
use IEEE.std_logic_1164.all;

entity pc_tb is
end pc_tb;

architecture structural of pc_tb is

component pc is 
	port (
		next_pc : in std_logic_vector(31 downto 0);
		clk : in std_logic;
		cur_pc : out std_logic_vector(31 downto 0)
	);
end component;

signal	pc_in, pc_out : std_logic_vector(31 downto 0);
signal  clk_in : std_logic;

begin
uut : pc
	port map(
		next_pc => pc_in,
		clk => clk_in,
		cur_pc => pc_out
	);

		tb: 
	process begin
		clk_in <= '0';
		wait for 10 ns;
		---
		pc_in <= X"00000000";
		wait for 5 ns;
		clk_in <= not clk_in;
		wait for 10 ns;
		---
		pc_in <= X"00000002";
		wait for 5 ns;
		clk_in <= not clk_in;
		wait for 10 ns;
		---
		pc_in <= X"00000004";
		wait for 5 ns;
		clk_in <= not clk_in;
		wait for 10 ns;
		wait;
	end process;
end structural;

