----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.01.2020 23:13:53
-- Design Name: 
-- Module Name: ADDER - Behavioral
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ADDER is
  Port (
            input_1: in std_logic_vector (31 downto 0);
           input_2: in std_logic_vector (31 downto 0);
            output: out std_logic_vector(31 downto 0) 
        );
end ADDER;

architecture Behavioral of ADDER is
--signal input_2:std_logic_vector(31 downto 0):= "00000000000000000000000000000100";
begin
        output <= input_1+input_2;

end Behavioral;
