library IEEE;
use IEEE.std_logic_1164.all;

entity clock is
	port (
		clk : out std_logic
	);
end clock;
architecture behavioral of clock is

constant clock_rate: Time := 50 ns;
signal output : std_logic := '0';

begin
	main_p : process
	begin
	  	while true loop
	  	wait for clock_rate;
	  	output <= not output;
	    	end loop;
	end process main_p;
  	clk <= output;
end behavioral;


