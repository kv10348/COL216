----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.01.2020 23:18:19
-- Design Name: 
-- Module Name: PROGRAM_COUNTER - Behavioral
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

entity PROGRAM_COUNTER is
  Port (
            clk: in std_logic;
            current_address: in std_logic_vector(31 downto 0);
            addressTOread: out std_logic_vector(31 downto 0)
            
       );
end PROGRAM_COUNTER;

architecture Behavioral of PROGRAM_COUNTER is
signal address: std_logic_vector(31 downto 0):= "00000000000000000000000000000000";
begin
    process(clk)
        begin
        addressTOread <= address;
        if clk='0' and clk'event then
            address <= current_address;
        end if;
    end process;
end Behavioral;
