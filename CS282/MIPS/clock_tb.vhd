library IEEE;
use IEEE.std_logic_1164.all;

entity clock_tb is
end clock_tb;

architecture structural of clock_tb is

component clock is 
	port (
		clk : out std_logic
	);
end component;

signal c_out : std_logic;

begin
uut :  clock
	port map(
		clk => c_out
	);
end structural;
