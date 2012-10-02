library IEEE;
use IEEE.std_logic_1164.all;

entity memory_tb is
end memory_tb;

architecture structural of memory_tb is

component memory is 
	port (
		address, write_data: in STD_LOGIC_VECTOR (31 downto 0);
		MemWrite, MemRead: in STD_LOGIC;
		read_data: out STD_LOGIC_VECTOR (31 downto 0)
	);
end component;

signal	address_input, write_data_input, read_data_out : STD_LOGIC_VECTOR(31 downto 0);
signal  MemWrite_input, MemRead_input : STD_LOGIC;

begin
uut : memory
	port map(
		address => address_input,
		write_data => write_data_input,
		MemWrite => MemWrite_input,
		MemRead => MemRead_input,
		read_data => read_data_out
	);

		tb: 
	process begin
		MemRead_input <= '1';
		MemWrite_input <= '0';
		wait for 20 ns;
		address_input    <= X"00000001";
		write_data_input <= X"00000002";
		wait for 20 ns;
		MemWrite_input <= '1';
		wait for 20 ns;
		MemWrite_input <= '0';
		wait for 20 ns;
		write_data_input <= X"0000000A";
		wait for 20 ns;
		write_data_input <= X"0000000B";
		wait for 20 ns;
		write_data_input <= X"0000000C";
		wait;
	end process;
end structural;
