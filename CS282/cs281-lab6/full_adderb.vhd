library IEEE;
use IEEE.std_logic_1164.all;

entity full_adder is 
 port(a,b,c_in : in std_ulogic;
	 sum,c_out: out std_ulogic);
end full_adder;

architecture behavioral of full_adder is
signal s1,s2,s3 : std_ulogic;
constant gate_delay: Time:=5 ns;
begin
s1 <= (a xor b) after gate_delay;
s2 <= (c_in and s1) after gate_delay;
s3 <= (a and b) after gate_delay;
sum <= (s1 xor c_in) after gate_delay;
c_out <= (s2 or s3) after gate_delay;
end behavioral;

	 
