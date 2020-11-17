----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.01.2020 19:53:32
-- Design Name: 
-- Module Name: Mips - Behavioral
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
use ieee.std_logic_unsigned.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Mips is
Port ( 
    clk: in std_logic
    --reset: in std_logic
);
end Mips;

architecture Behavioral of Mips is
  signal se_in: std_logic_vector(15 downto 0) := x"0000";
  signal se_out: std_logic_vector(31 downto 0):= x"00000000";
  signal reg2: std_logic_vector(31 downto 0):= x"00000000";  
  signal MUX_1_out: std_logic_vector(31 downto 0):= x"00000000"; 
  signal rd_reg1: std_logic_vector(4 downto 0) := "00000"; 
  signal rd_reg2: std_logic_vector(4 downto 0) := "00000"; 
  signal wrt_reg: std_logic_vector(4 downto 0) := "00000";
  signal MUX_rt_rd_out: std_logic_vector(4 downto 0) := "00000"; 
  signal out_reg1: std_logic_vector(31 downto 0) := x"00000000";
   signal in_reg: std_logic_vector(31 downto 0) := x"00000000";
  signal out_reg2: std_logic_vector(31 downto 0) := x"00000000"; 
  signal ALU_result: std_logic_vector(31 downto 0) := x"00000000"; 
  signal readdata: std_logic_vector(31 downto 0) := x"00000000"; 
   signal readadd: std_logic_vector(31 downto 0) := x"00000000"; 
    signal inst: std_logic_vector(31 downto 0) := x"00000000"; 
  signal ALUcontrol: std_logic_vector(2 downto 0) := "000"; 
  signal op: std_logic_vector(5 downto 0) := "000000"; 
  signal fun: std_logic_vector(5 downto 0) := "000000"; 
  signal ALUctr: std_logic:='0';  
  signal regdst: std_logic:='0'; 
  signal rgwrt: std_logic:='0';  
  signal memwrt: std_logic:='0';  
  signal memrd: std_logic:='0'; 
  signal memtoreg: std_logic:='0'; 
    signal curr: std_logic_vector(31 downto 0) := x"00000000"; 
     signal shift: std_logic_vector(4 downto 0) := "00000"; 
    --signal output: std_logic_vector(31 downto 0) := x"00000000"; 
    
   signal last_instr_address: std_logic_vector(31 downto 0) := x"00000000";  
    
    
	 -- Enum for checking if the instructions have loaded
	type state is (loading,running, done);
	signal s: state:= loading;

	-- The clock for the other components; starts when the state is ready
	signal en: std_logic:= '0';
   
begin
    process(clk)
		begin
		case s is
			when running =>
				en <= clk;
			when others =>
				en <= '0';
		end case;

		if clk='1' and clk'event then
			case s is
			    when loading =>
			         s <= running;
				 -- give 1 cycle to load the instructions into memory
				when running =>
					if readadd > last_instr_address then
						s <= done; -- stop moving the pc after it has passed the last instruction
						en <= '0';
					end if;
				when others =>
					null;
			end case;
		end if;
	end process;
    






    U1: entity work.INSTRUCTION_MEMORY(behavioral)
    port map(
        read_address=> readadd,
		instruction=>inst,
		last_instr_address=>last_instr_address
   
    );
    PC: entity work.PROGRAM_COUNTER(behavioral)
        port map(
            clk=> en,
            current_address=> curr,
            addressTOread=> readadd
        
        
        );
    ADDER: entity work.ADDER(behavioral)
    port map(
             input_1=> readadd ,
             input_2=>"00000000000000000000000000000100",
             output=> curr 
    
    
    
    
    );


    U2: entity work.MUX_1(Behavioral)
    port map(
            input_1=>out_reg2,
            input_2=>se_out ,
            output=> MUX_1_out,
            switch=>ALUctr
    
    );
    
    U3: entity work.SIGN_EXTEND(behavioral)
        port map(
            input_1=> se_in,
            output_1=> se_out
    
        );
    
    U4: entity work.MUX_rt_rd(behavioral)
        port map(
            input_1=> rd_reg2,
            input_2=>wrt_reg,
            output=>MUX_rt_rd_out,
            switch=>regdst   
        );
        
        op <=  inst(31 downto 26 );   
        fun<=  inst(5 downto 0);
        rd_reg1<=  inst(25 downto 21);   
        rd_reg2<=  inst(20 downto 16);        
        wrt_reg<= inst(15 downto 11);
        se_in<= inst(15 downto 0);
        shift<= inst(10 downto 6);
        
        
    U5: entity work. Register_file(beh)
    port map(
            clk=> en,
		reg_write=> rgwrt,
		read_reg_1=>rd_reg1, 
		read_reg_2=> rd_reg2, 
		write_reg=>MUX_rt_rd_out,
		write_data=> in_reg,
		read_data_1=> out_reg1,
		 read_data_2=> out_reg2
 
   
    );

    
    U6: entity work.ALU(behavioral)
    port map(
        srcA=> out_reg1,
        srcB=> MUX_1_out,
        ALUcontrol=> ALUcontrol,
        writedata=> ALU_result,
        shift=> shift
        
        );
    
    
    U7: entity work.DATA_MEMORY(behavioral)
        port map(
        
            address=>ALU_result,
            write_data=>out_reg2,
            clk=>en,
            Memory_Write=>memwrt,
            Memory_Read=>memrd,
            Read_Data=>readdata
  
        );
        
     U8: entity work.control_unit(behavioral)
        port map(
             op=> op, --OP FOR OUR ALL COMMANDS WILL BE "00000" EXCEPT FOR LW AND SW 
             fun=> fun,   -- FUNC LW AND SW IS NOT ZERO BUT OTHER THAN THIS FOR ALL IT IS ZERO

             memtoreg=>  memtoreg,
             memwrite=> memwrt,
             memrd=> memrd,
             ALUcontrol=> ALUcontrol,
             ALUsrc=>ALUctr,
             regdst=> regdst,
             regwrt=> rgwrt
      
        );
    U9: entity work.MUX_1(Behavioral)
    port map(
            input_1=> AlU_result,
            input_2=>readdata,
            output=> in_reg,
            switch=>memtoreg
    
    );
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
end Behavioral;
