library IEEE;
use IEEE.std_logic_1164.all;

entity alu_tb is
end alu_tb;

architecture structural of alu_tb is

component alu is 
	port (
		a, b: in STD_LOGIC_VECTOR (31 downto 0);
		Op: in STD_LOGIC_VECTOR (1 downto 0);
		Result: out STD_LOGIC_VECTOR (31 downto 0);
		Zero: out STD_LOGIC;
		Ovf: out STD_LOGIC
	);
end component;

signal	a_in, b_in, res_out : std_logic_vector(31 downto 0);
signal  op_in : std_logic_vector(1 downto 0);
signal  zero_out, ovf_out : std_logic;

begin
uut : alu
	port map(
		a => a_in,
		b => b_in,
		Op => op_in,
		Zero => zero_out,
		Result => res_out,
		Ovf => ovf_out
	);

		tb: 
	process begin
		a_in <= "01111111111111111111111111111111";
		b_in <= "00000000000000000000000000000001";
		op_in <= "00";
		wait for 10 ns;
		a_in <= "00000000000000000000000000000001";
		b_in <= "00000000000000000000000000000001";
		wait for 10 ns;
		op_in <= "01";
		a_in <= "00000000000000000000000000000010";
		b_in <= "00000000000000000000000000000001";
		wait for 10 ns;
		a_in <= "10000000000000000000000000000000";
		b_in <= "00000000000000000000000000000001";
		wait for 10 ns;
		wait;
	end process;
end structural;
