library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity sl2 is
	port (
		input  : in std_logic_vector(31 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end sl2;

architecture behavioral of sl2 is	  

begin
	output <= std_logic_vector(signed(input) sll 2);
end behavioral;

