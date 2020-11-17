----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 24.01.2020 23:42:22
-- Design Name: 
-- Module Name: MUX_rt_rd - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity MUX_rt_rd is
  Port (
            input_1:in std_logic_vector(4 downto 0);
            input_2:in std_logic_vector(4 downto 0);
            output:out std_logic_vector(4 downto 0);
            switch: in std_logic
        );
end MUX_rt_rd;

architecture Behavioral of MUX_rt_rd is

begin
        output <= input_1 when (switch='0') 
                  else input_2;

end Behavioral;
