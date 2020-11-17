----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.01.2020 00:08:22
-- Design Name: 
-- Module Name: control_unit - Behavioral
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity control_unit is
Port ( 


op: in STD_LOGIC_VECTOR(5 DOWNTO 0); --OP FOR OUR ALL COMMANDS WILL BE "00000" EXCEPT FOR LW AND SW 
fun: in STD_LOGIC_VECTOR(5 DOWNTO 0);   -- FUNC LW AND SW IS NOT ZERO BUT OTHER THAN THIS FOR ALL IT IS ZERO

memtoreg: out STD_LOGIC;
memwrite: out STD_LOGIC;
memrd: out STD_LOGIC;
ALUcontrol: out STD_LOGIC_VECTOR(2 DOWNTO 0);
ALUsrc: out STD_LOGIC;
regdst: out STD_LOGIC;
regwrt: out STD_LOGIC
);
end control_unit;

architecture Behavioral of control_unit is

begin
process(op, fun)
begin

if op="000000" then
    CASE fun IS 
         when "100000" => ALUcontrol(2 downto 0) <= "000";     --add
         when "100010" => ALUcontrol(2 downto 0) <= "001";     -- sub
         when "100100" => ALUcontrol(2 downto 0) <= "010";     --and
         when "000010" => ALUcontrol(2 downto 0) <= "011";      -- srl
         when "000000" => ALUcontrol(2 downto 0) <= "100";      --sll
         when others => ALUcontrol(2 downto 0) <= "111";        -- error
     end case;
             
else
    case op is 
        when "100011" => ALUcontrol(2 downto 0) <= "101";      --lw
        when "101011" => ALUcontrol(2 downto 0) <= "110";      --sw
        when others => ALUcontrol(2 downto 0) <="111";          --error
    end case; 
end if;

end process;

process(op,fun)
begin 

if op="000000" then 
    memwrite<='0';
    regdst<='1';
    memtoreg<='0';
    ALUsrc<='0';
    regwrt<='1';
    memrd<='0';
else
    if op="100011" then
        memwrite<='0';
        regdst<='0';
        memtoreg<='1';
        ALUsrc<='1';
        regwrt<='1'; 
        memrd<='1';
    end if;
    if op="101011" then
        memwrite<='1';
        regdst<='0';
        memtoreg<='0';
        ALUsrc<='1';
        regwrt<='0';
        memrd<='0';
    end if;
   
end if ;
end process;





end Behavioral;
