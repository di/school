--
--  File: mux.vhd
--  4:1 Multiplexer
--
Library IEEE;
use IEEE.std_logic_1164.all;
--Entity Declaration
entity mux41 is
	port(I0,I1,I2,I3 : in std_ulogic;
		 Sel : in std_ulogic_vector(1 downto 0);
		 Z : out std_ulogic);
end mux41;

--Architecture Definition
architecture behavioral of mux41 is
begin
  with Sel select
     Z <= I0 after 5 ns when "00",
          I1 after 5 ns when "01",
          I2 after 5 ns when "10",
          I3 after 5 ns when "11",
          'X' after 5 ns when others;
end behavioral;
