-- structural model of a full adder

library IEEE;
use IEEE.std_logic_1164.all;

entity full_adder is 
 port(a,b,c_in : in std_ulogic;
	 sum,c_out: out std_ulogic);
end full_adder;

architecture structural of full_adder is

component half_adder
  port(a,b : in std_ulogic;
       sum,carry : out std_ulogic);
end component;

component or2
  port(a,b : in std_ulogic;
       c : out std_ulogic);
end component;

signal s1, s2, s3 : std_ulogic;

begin
  HA1 : half_adder port map(a => a, b => b, sum => s1, carry => s3);
  HA2 : half_adder port map(a => s1, b => c_in, sum => sum, carry => s2);
  O1  : or2 port map(a => s2, b => s3, c => c_out);
end structural;

	 
