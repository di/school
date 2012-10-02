library IEEE;
use IEEE.std_logic_1164.all;

entity alu32 is
   port (a, b, CarryIn, Binvert: in std_logic;
         Operation: in std_logic_vector (1 downto 0);
         Result, CarryOut, Overflow: out std_logic);
end entity;

architecture structural of alu32 is
component alu1 is
   port (a, b, CarryIn, Binvert: in std_logic;
         Operation: in std_logic_vector (1 downto 0);
         Result, CarryOut, Overflow: out std_logic);
end component;
signal c: std_logic_vector (30 downto 0);
begin
   Alu1st: alu1 port map (a(0), b(0), CarryIn, Binvert, Operation, Result(0), c(0), 0);
   Gen: for i in 1 to 30 generate
      ALUs: alu1 port map (a(i), b(i), c(i - 1), Binvert, Operation, Result(i), c(i), 0);
   end generate;
   Alu32nd: alu1 port map (a(31), b(31), c(30), Binvert, Operation, Result(31), CarryOut, Overflow);
end structural;


