library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity j_concat is
	port (
		pc_plus_4 : in std_logic_vector(31 downto 0);
		inst_lower : in std_logic_vector(25 downto 0);
		jump_to : out std_logic_vector(31 downto 0)
	);
end j_concat;

architecture behavioral of j_concat is

begin
	main_p : process(pc_plus_4, inst_lower)
	begin
		jump_to <= pc_plus_4(31 downto 28) & inst_lower(25 downto 0) & "00";
	end process main_p;
end behavioral;
