library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.ALL;

entity alu is
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Op: in STD_LOGIC_VECTOR (1 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0);
		Zero: out STD_LOGIC;
		Ovf: out STD_LOGIC
	);
end alu;

architecture behavioral of alu is	  

begin
  alu_proc: process(a, b, Op)
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
	  
	  if(Op = "00") then
	  	res_int := a_int + b_int;
	  	if((a_int > 0) and (b_int > 0) and ((res_int < a_int) or (res_int < b_int))) then
	  		Ovf <= '1';
	  	elsif(a_int > 0 and b_int < 0 and (res_int > a_int or res_int < b_int)) then
	  		Ovf <= '1';
	  	elsif(a_int < 0 and b_int > 0 and (res_int < a_int and res_int > b_int)) then
	  		Ovf <= '1';
	  	elsif(a_int < 0 and b_int < 0 and (res_int > 0)) then
	  		Ovf <= '1';
	  	else
	  		Ovf <= '0';
	  	end if;
	  elsif(Op = "01") then
	  	res_int := a_int - b_int;
	  	if((a_int > 0) and (b_int > 0) and ((res_int > a_int) or (res_int < b_int))) then
	  		Ovf <= '1';
	  	elsif(a_int > 0 and b_int < 0 and (res_int < a_int or res_int < b_int)) then
	  		Ovf <= '1';
	  	elsif(a_int < 0 and b_int > 0 and (res_int > 0)) then
	  		Ovf <= '1';
	  	elsif(a_int < 0 and b_int < 0 and (res_int < a_int or res_int > b_int)) then
	  		Ovf <= '1';
	  	else
	  		Ovf <= '0';
	  	end if;
	  elsif(Op = "10") then
	  	res_int := a_int - b_int;
	  	if(res_int < 0) then
	  		res_int := 1;
	  	else
	  		res_int := 0;
	  	end if;
	  end if;
	  Result <= CONV_STD_LOGIC_VECTOR(res_int, 32);
	  if(res_int = 0) then
	  	Zero <= '1';
	  else
	  	Zero <= '0';
	  end if;
  end process alu_proc;
end behavioral;

