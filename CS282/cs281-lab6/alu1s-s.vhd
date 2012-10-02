-- structural model of the 1-bit ALU, supporting subtraction

library IEEE;
use IEEE.std_logic_1164.all;

entity alu1 is 
 port(a,b,CarryIn,Binvert : in std_ulogic;
      Operation : in std_ulogic_vector (1 downto 0);
	 Result, CarryOut : out std_ulogic);
end alu1;

architecture structural of alu1 is

component and_2
  port(a,b : in std_ulogic;
         c : out std_ulogic);
end component;

component or_2
  port(a,b : in std_ulogic;
         c : out std_ulogic);
end component;

component full_adder
 port(a,b,c_in : in std_ulogic;
	 sum,c_out: out std_ulogic);
end component;

component mux41
	port(I0,I1,I2,I3 : in std_ulogic;
		 Sel : in std_ulogic_vector(1 downto 0);
		 Z : out std_ulogic);
end component;

signal s1, s2, s3, binv : std_ulogic;
signal s4 : std_ulogic := 'X';

begin
  AG   : and_2 port map(a => a, b => b, c => s1);
  OG   : or_2 port map(a => a, b => b, c => s2);
  xB	: xor_2 port map(a => b, b => Binvert, c => binv);
  FA  : full_adder port map(a => a, b => binv, c_in => CarryIn, sum => s3, c_out => CarryOut);
  MUX : mux41 port map(I0 => s1, I1 => s2, I2 => s3, I3 => s4, Sel => Operation, Z => Result);

end structural;
