library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.ALL;

entity adder is
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0)
	);
end adder;

architecture behavioral of adder is	  

begin
  add_proc: process(a, b)
  variable a_int, b_int, res_int: integer;
  function to_integer(X: STD_LOGIC_VECTOR) return INTEGER is
  variable result: INTEGER;
  begin
	  result := 0;
	  for i in X'range loop
		  result := result * 2;
		  case X(i) is
			  when '0' | 'L' => null;
			  when '1' | 'H' => result := result + 1;
			  when others => null;
		  end case;
	  end loop;
	  return result;
  end to_integer;
  
  begin
	  a_int := to_integer(a);
	  b_int := to_integer(b);
	  	res_int := a_int + b_int;
	  Result <= CONV_STD_LOGIC_VECTOR(a_int + b_int, 32);
  end process add_proc;
end behavioral;
