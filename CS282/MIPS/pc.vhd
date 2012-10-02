library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity pc is
	port (
		next_pc : in std_logic_vector(31 downto 0);
		clk : in std_logic;
		cur_pc : out std_logic_vector(31 downto 0)
	);
end pc;

architecture behavioral of pc is	  

signal instruction : std_logic_vector(31 downto 0) := X"00000000";

begin
	main_p : process
	begin
		-- wait for clock
		wait until (clk'event and clk='1');
		instruction <= next_pc;
	end process main_p;
	cur_pc <= instruction;
end behavioral;
