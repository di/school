library IEEE;
use IEEE.std_logic_1164.all;

entity alu_tester is
end entity;

architecture behavioral of alu_tester is

component alu32 is
       port(a,b,binvert,CarryIn : in std_ulogic;
                Operation : in std_ulogic_vector (1 downto 0);
                Result, CarryOut, Overflow : out std_ulogic);
end component;

signal aS,bS,bvertS,cinS,opt1S,opt2s,rS,coutS,overS  :  STD_LOGIC;

begin

 testbench : alu32
   port map(
        a=>aS, b=>bS, binvert=>bvertS, CarryIn=>cinS, Operation(0)=>opt1S, Operation(1)=>opt2s, Result=>rS, CarryOut=>coutS, Overflow => overS
   );

       aS <= '0' after 0 ns, '1' after 20 ns, '0' after 40 ns, '1' after 60 ns, '0' after 80 ns,
       '1' after 100 ns, '0' after 120 ns, '1' after 140 ns, '0' after 160 ns, '1' after 180 ns,
       '0' after 200 ns, '1' after 220 ns, '0' after 240 ns;
       bS <= '0' after 0 ns, '1' after 10 ns, '0' after 20 ns, '1' after 30 ns, '0' after 40 ns,
             '1' after 50 ns, '0' after 60 ns, '1' after 70 ns, '0' after 80 ns, '1' after 90 ns,
             '0' after 100 ns, '1' after 110 ns, '0' after 120 ns,'1' after 130 ns, '0' after 140 ns,
             '1' after 150 ns, '0' after 160 ns, '1' after 170 ns, '0' after 180 ns, '1' after 190 ns,
             '0' after 200 ns, '1' after 210 ns, '0' after 220 ns, '1' after 230 ns, '0' after 240 ns;
       cinS <= '0' after 0 ns, '1' after 120 ns, '0' after 160 ns, '1' after 200 ns, '0' after 240 ns;
       bvertS <= '0' after 0 ns, '1' after 160 ns;
       opt1S <= '0' after 0 ns, '1' after 40 ns, '0' after 80 ns;
       opt2S <= '0' after 0 ns, '1' after 80 ns;


end behavioral;


