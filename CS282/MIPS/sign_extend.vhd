library IEEE;
use IEEE.std_logic_1164.all;
USE IEEE.numeric_std.all;

entity sign_extend is
	port (
		input  : in std_logic_vector(15 downto 0);
		output : out std_logic_vector(31 downto 0)
	);
end sign_extend;

architecture behavioral of sign_extend is	  

begin
	output <= std_logic_vector(resize(signed(input), output'length));
end behavioral;
