library IEEE;
use IEEE.std_logic_1164.all;

entity control_unit is 
	port(
		Opcode : in std_logic_vector (5 downto 0);
		Funct : in std_logic_vector (5 downto 0);
		RegDst, Branch, MemRead, MemToReg, MemWrite, ALUSrc, RegWrite, Jump : out std_ulogic;
		ALUOp : out std_logic_vector (1 downto 0)
	);
end control_unit;

architecture behavioral of control_unit is
begin
-- ALU Ops
-- 00 add
-- 01 sub
-- 10 slt
	process (Opcode)
	begin
		case Opcode is
			when "000000" => -- R-Type
				RegDst   <= '1';
				Branch   <= '0';
				MemRead  <= '0';
				MemToReg <= '0';
				MemWrite <= '0';
				ALUSrc   <= '0';
				RegWrite <= '1';
				if(Funct = "100000") then -- add
					ALUOp <= "00";
				elsif(Funct = "101010") then -- slt
					ALUOp <= "10";
				end if;
				Jump     <= '0';
			when "001000" => -- addi
				RegDst   <= '0';
				Branch   <= '0';
				MemRead  <= '0';
				MemToReg <= '0';
				MemWrite <= '0';
				ALUSrc   <= '1';
				RegWrite <= '1';
				ALUOp    <= "00"; -- add
				Jump     <= '0';
			when "100011" => -- lw
				RegDst   <= '0';
				Branch   <= '0';
				MemRead  <= '1';
				MemToReg <= '1';
				MemWrite <= '0';
				ALUSrc   <= '1';
				RegWrite <= '1';
				ALUOp    <= "00"; -- add
				Jump     <= '0';
			when "000100" => -- beq
				RegDst   <= '0';
				Branch   <= '1';
				MemRead  <= '0';
				MemToReg <= '0';
				MemWrite <= '0';
				ALUSrc   <= '0';
				RegWrite <= '0';
				ALUOp    <= "01"; -- sub
				Jump     <= '0';
			when "000010" => -- j
				RegDst   <= '0'; -- don't care
				Branch   <= '0';
				MemRead  <= '0';
				MemToReg <= '0';
				MemWrite <= '0';
				ALUSrc   <= '0';
				RegWrite <= '0';
				ALUOp    <= "00"; -- don't care
				Jump     <= '1';
			when "101011" => -- sw
				RegDst   <= '0';
				Branch   <= '0';
				MemRead  <= '0';
				MemToReg <= '0';
				MemWrite <= '1';
				ALUSrc   <= '1';
				RegWrite <= '0';
				ALUOp    <= "00"; -- add
				Jump     <= '0';
			when others =>
				RegDst   <= 'X';
				Branch   <= 'X';
				MemRead  <= 'X';
				MemToReg <= 'X';
				MemWrite <= 'X';
				ALUSrc   <= 'X';
				RegWrite <= 'X';
				ALUOp    <= "XX";
				Jump     <= 'X';
		end case;
	end process;
end behavioral;






