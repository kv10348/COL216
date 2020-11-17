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
clk: in std_logic;
srcA: in STD_LOGIC_VECTOR(31 DOWNTO 0);
srcB: in STD_LOGIC_VECTOR(31 DOWNTO 0);
ALUcontrol: in STD_LOGIC_VECTOR(2 DOWNTO 0);
writedata: out STD_LOGIC_VECTOR(31 DOWNTO 0);
shift: in std_logic_vector(4 downto 0);
count_in: in std_logic_vector(11 downto 0);
count_out:out std_logic_vector(11 downto 0)

);
end ALU;

architecture Behavioral of ALU is
signal OUTALU:STD_LOGIC_VECTOR(31 DOWNTO 0);
signal address: std_logic_vector(11 downto 0):= "000000000000";
signal address1: std_logic_vector(11 downto 0):= "000000000000";
signal counter: integer:=0;
begin
process(srcA, srcB,ALUcontrol)
begin
OUTALU<=srcA+srcB;
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
--process(clk)
--begin
--if(clk'event and clk='1') then
--    counter<=counter+1;
--    if(counter=1) then
--    counter<=0;
--    end if;
--   end if;
--end process;


    process(clk)
        begin
            if(ALUcontrol="101" or ALUcontrol="110" ) then
                counter<=counter+1;
                count_out<=OUTALU(11 downto 0);
--            counter<=counter+1;
                if(counter=1) then
                    counter<=0;
            --address <= address+"00000000001";
                    count_out<=address;
                    address <= address+"00000000001";
                end if;
            else 
                count_out<=address;
                if clk='1' and clk'event then
                        address <= count_in+"00000000001";
                end if;
            end if;
        end process;
--process(clk)
--begin
--    if( ALUcontrol="101" or ALUcontrol="110" ) then
--    count_out<=OUTALU(11 downto 0);
--    else
--    count_out<=count_in+"000000000001";
--    end if;
--end process;

   
end Behavioral;
