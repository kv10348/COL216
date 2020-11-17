----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.01.2020 15:57:12
-- Design Name: 
-- Module Name: DATA_MEMORY - Behavioral
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
use IEEE.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DATA_MEMORY is
  Port (
            address: in std_logic_vector(31 downto 0);
            write_data: in std_logic_vector(31 downto 0);
            clk: in std_logic;
            Memory_Write:in std_logic;
            Memory_Read: in std_logic;
            Read_Data: out std_logic_vector(31 downto 0)
                    );
end DATA_MEMORY;

architecture Behavioral of DATA_MEMORY is
type memory_array is array(0 to 31) of std_logic_vector (31 downto 0);
signal data_memory: memory_array := (
    X"00000000", 
    X"00000000", 
    X"00001111",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000", 
    X"00000000", 
    X"00000000", 
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",  
    X"00000000", 
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000", 
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000",
    X"00000000", 
    X"00000000", 
    X"00000000");

begin
    Read_Data <= data_memory(conv_integer(address(4 downto 0))) when Memory_Read= '1' else  X"00000000"; 
process(address,write_data,clk)
    begin
        if clk='0'and clk'event then
            if(Memory_Write='1') then
                data_memory(conv_integer(address(4 downto 0))) <= write_data;
            end if;
        end if;      
    end process;
end Behavioral;
