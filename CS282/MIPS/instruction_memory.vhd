library IEEE;
use IEEE.std_logic_1164.all;

entity instruction_memory is
	port (
		address: in STD_LOGIC_VECTOR (31 downto 0);
		read_data: out STD_LOGIC_VECTOR (31 downto 0);
		opcode: out std_logic_vector(5 downto 0);
		rs: out std_logic_vector(4 downto 0);
		rt: out std_logic_vector(4 downto 0);
		rd: out std_logic_vector(4 downto 0);
		im: out std_logic_vector(15 downto 0);
		funct: out std_logic_vector(5 downto 0)
	);
end instruction_memory;

architecture behavioral of instruction_memory is	  

type mem_array is array(0 to 13) of STD_LOGIC_VECTOR (31 downto 0);

begin
  -- <<enter your statements here>>								
  mem_process: process(address)
  variable data_mem: mem_array := (
    "00100000000000010000000000000111", -- addi
    "00000000000000000001000000100000", -- add
    "00100000000000110000000000000000", -- addi
    "00100000000001000000000000000000", -- addi
    "00000000010000100010100000100000", -- add (loop)
    "00000000101001010010100000100000", -- add
    --"00000000000000000000000000000000", -- NOP
    "00000000101000110010100000100000", -- add
    "10001100101001100000000000000000", -- lw
    "00000000110001000010000000100000", -- add
    "00100000010000100000000000000001", -- add
    "00000000010000010011100000101010", -- slt
    "00010000000001110000000000000001", -- beq
    "00001000000000000000000000000100", -- j
    "10101100000001000000000000011100"  -- sw
    );
  variable addr: integer;
  
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
	  addr := to_integer(address(31 downto 0)) / 4;
	  read_data <= data_mem(addr);
	  opcode <= data_mem(addr)(31 downto 26);
	  rs <= data_mem(addr)(25 downto 21);
	  rt <= data_mem(addr)(20 downto 16);
	  rd <= data_mem(addr)(15 downto 11);
	  im <= data_mem(addr)(15 downto 0);
	  funct <= data_mem(addr)(5 downto 0);
  end process mem_process;
end behavioral;






