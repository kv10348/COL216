----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.01.2020 13:50:33
-- Design Name: 
-- Module Name: SIGN_EXTEND - Behavioral
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
use IEEE.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SIGN_EXTEND is
  Port (
            input_1:in std_logic_vector(15 downto 0);
            output_1:out std_logic_vector(31 downto 0)
       );
end SIGN_EXTEND;

architecture Behavioral of SIGN_EXTEND is

begin
      output_1 <= std_logic_vector(resize(signed(input_1),output_1'length));  

end Behavioral;
