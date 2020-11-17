----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.01.2020 00:57:46
-- Design Name: 
-- Module Name: ALU - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU is
Port ( 
    
srcA: in STD_LOGIC_VECTOR(31 DOWNTO 0);
srcB: in STD_LOGIC_VECTOR(31 DOWNTO 0);
ALUcontrol: in STD_LOGIC_VECTOR(2 DOWNTO 0);
writedata: out STD_LOGIC_VECTOR(31 DOWNTO 0);
shift: in std_logic_vector(4 downto 0)
);
end ALU;

architecture Behavioral of ALU is
signal OUTALU:STD_LOGIC_VECTOR(31 DOWNTO 0);
begin
process(srcA, srcB)
begin

case ALUcontrol is
    when "000" => writedata<= srcA+srcB;
    when "001" => writedata <= srcA-srcB;
    when "010" => writedata <= srcA and srcB;
    when "011" => writedata <= std_logic_vector(unsigned(srcA) srl to_integer(unsigned(shift)));  --srl still did not solve
    when "100" => writedata <= std_logic_vector(unsigned(srcA) sll to_integer(unsigned(shift)));       --sll did not
    when "101" => writedata <= srcA+srcB;
    when "110" => writedata <= srcA+srcB;
    when others => writedata<="00000000000000000000000000000000";
    
end case;
    



end process;
end Behavioral;
