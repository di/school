-- behavioral model of the 1-bit ALU on page 234

library IEEE;
use IEEE.std_logic_1164.all;

entity alu1 is 
 port(a,b,CarryIn : in std_ulogic;
      Operation : in std_ulogic_vector (1 downto 0);
	 Result, CarryOut : out std_ulogic);
end alu1;

architecture behavioral of alu1 is
constant gate_delay: Time:=5 ns;

begin
with Operation select
  Result <= (a and b) after gate_delay when "00",
            (a or b) after gate_delay when "01",
            (a xor b xor CarryIn) after gate_delay when "10",
            'X' after gate_delay when others;
  CarryOut <= ((a and b) or (a and CarryIn) or (b and CarryIn)) after gate_delay;
end behavioral;

	 
