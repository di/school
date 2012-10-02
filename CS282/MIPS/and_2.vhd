library IEEE;
use IEEE.std_logic_1164.all;

entity and_2 is
	port (
		i0, i1 : in std_logic;
		output : out std_logic
	);
end and_2;

architecture behavioral of and_2 is

begin
	output <= i0 and i1;
end behavioral;
