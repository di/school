--
--  File: or2.vhd
--  2 input OR gate
--
library IEEE;
use IEEE.std_logic_1164.all;

entity xor_2 is
    port(a, b: in std_ulogic;
         c : out std_ulogic);
end xor_2;

architecture behavioral of xor_2 is
begin
  c <= (a xor b) after 5 ns;
end behavioral;

