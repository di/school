library IEEE;
use IEEE.std_logic_1164.all;

entity multiplexer_2_5bit is
	port (
		i0: in std_logic_vector(4 downto 0);
		i1: in std_logic_vector(4 downto 0);
		sel: in std_logic;
		output: out std_logic_vector(4 downto 0)
	);
end multiplexer_2_5bit;

architecture behavorial of multiplexer_2_5bit is
begin
	process(i0, i1, sel)
	begin
		if(sel = '0') then
			output <= i0;
		else
			output <= i1;
		end if;
	end process;
end behavorial;

