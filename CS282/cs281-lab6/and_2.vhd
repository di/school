library IEEE;
use IEEE.std_logic_1164.all;

entity and_2 is
	port (
		a: in STD_LOGIC;
		b: in STD_LOGIC;
		c: out STD_LOGIC
	);
end and_2;

architecture behavioral of and_2 is
begin
  c <= (a and b) after 2 ns;
end behavioral;
