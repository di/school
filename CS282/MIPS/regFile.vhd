library IEEE;
use IEEE.std_logic_1164.all;

entity regFile is
	port (
		clk : in std_logic;
		readReg1,readReg2, writeReg: in STD_LOGIC_VECTOR (4 downto 0); 
		write_data: in STD_LOGIC_VECTOR (31 downto 0);
		RegWrite: in STD_LOGIC;
		read_data1, read_data2: out STD_LOGIC_VECTOR (31 downto 0)
	);
end regFile;
architecture behavioral of regFile is	  
type register_data is array(0 to 7) of STD_LOGIC_VECTOR (31 downto 0);
shared variable regBank: register_data := (
    X"00000000", -- initialize data memory
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000");
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
  reg_process: process--(readReg1, readReg2, writeReg, write_data, RegWrite)
  variable addr1: integer;
  variable addr2: integer;   
  variable writeAddr: integer;
  
  begin
  	  wait until (clk'event and clk='1');
	  
	  writeAddr := to_integer(writeReg(4 downto 0));
	  if (RegWrite = '1' and writeAddr > 0) then
		  regBank(writeAddr) := write_data;
	  end if;
  end process reg_process;
  read_process: process(readReg1, readReg2)
  begin
	read_data1 <=  regBank(to_integer(readReg1(4 downto 0)));
	read_data2 <=  regBank(to_integer(readReg2(4 downto 0)));
  end process read_process;
end behavioral;


