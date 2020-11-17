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
use IEEE.NUMERIC_STD.ALL;
LIBRARY blk_mem_gen_v8_4_2;
--USE blk_mem_gen_v8_4_2.blk_mem_gen_v8_4_2;
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

  COMPONENT blk_mem_gen_0 IS
  PORT (
    clka : IN STD_LOGIC;
    ena : IN STD_LOGIC;
    wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    addra : IN STD_LOGIC_VECTOR(11 DOWNTO 0);
    dina : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    douta : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
  );
END COMPONENT;

	 -- Enum for checking if the instructions have loaded
	--type state is (loading,running, done);
	--signal s: state:= loading;
    signal readdata : std_logic_vector(31 downto 0);
    signal ALUresult : std_logic_vector(31 downto 0);
     signal ALUinput2 : std_logic_vector(31 downto 0);
     signal out_extend: std_logic_vector(31 downto 0);
    signal rg_out1 : std_logic_vector(31 downto 0);
    signal rg_out2 : std_logic_vector(31 downto 0);
    signal wrt_data : std_logic_vector(31 downto 0);
    signal pc_x1: std_logic_vector(11 downto 0);
    signal pc_x2: std_logic_vector(11 downto 0):="000000000000";
     signal temp: std_logic_vector(11 downto 0);
    signal rd_reg1: std_logic_vector(4 downto 0);
    signal rd_reg2: std_logic_vector(4 downto 0);
    signal op: std_logic_vector(5 downto 0);
    signal func: std_logic_vector(5 downto 0);
    signal wrt_reg: std_logic_vector(4 downto 0);
     signal mux_rt_rd: std_logic_vector(4 downto 0);
    signal for_extend: std_logic_vector(15 downto 0);
    signal mmwrt:std_logic_vector(0 downto 0):="0";
        signal manish:std_logic_vector(0 downto 0):="0";

     signal mmrd:std_logic;
     signal ALUctr: std_logic_vector(2 downto 0); 
     signal ALUsrc:std_logic;
    signal memtoreg:std_logic;
    signal regwrt:std_logic;
    signal regdst:std_logic;
    signal shift: std_logic_vector(4 downto 0);
	-- The clock for the other components; starts when the state is ready
	signal en: std_logic:= '0';
    signal a:integer:=0;
	signal b:std_logic:='1';
	signal b1:std_logic;
	signal flag:boolean:=false;
	signal flag1:boolean:=false;
   
   signal counter: integer:=0;
   signal counter1: integer:=0;
begin
    manish<=mmwrt;
    process(clk)
		begin
		en<=clk;
		if(clk'event and clk='1') then 
		
		  if(readdata="00000000000000000000000000000000") and flag=false then 
		  flag<=true;
		  elsif(readdata="00000000000000000000000000000000") and flag=true then
		   en<='0';
		end if;
		end if;

	end process;
process(en,a,b)
begin
if(en'event and en='1') then 
    a<=a+1;
    b<='0';
    if(a>2)then 
        b<='1';
        a<=0;
     end if;
  end if;    
end process;
--   PC: entity work.PROGRAM_COUNTER(Behavioral)
--     port map(
--            clk=>b,
--            current_address=>pc_x1,
--            addressTOread=>pc_x2
            
--       );


--    U1: entity work.INSTRUCTION_MEMORY(behavioral)
--    port map(
--        read_address=> readadd,
--		instruction=>inst,
--		last_instr_address=>last_instr_address
-- temp<=pc_x2;
-- process(en)
-- begin
-- if(en'event and en='1') then
-- if (ALUctr="110" or ALUctr="101") then 
--    counter1<=counter1+1;
--    pc_x2<=ALUresult(11 downto 0);
--    flag1<=true;
--    if(counter1=2) then 
--        counter1<=0;
--        pc_x2<=temp;
--     end if;
-- end if;
-- end if;
--end process;
  
--ADDER:entity work.ADDER(Behavioral)
--  Port map (
--           input_1=>"000000000001",
--           input_2=>pc_x2,
--           output=> pc_x1
--        );
  op<=readdata(31 downto 26);
  rd_reg1<=readdata(25 downto 21);
  rd_reg2<=readdata(20 downto 16);
  wrt_reg<=readdata(15 downto 11);
  for_extend<=readdata(15 downto 0); 
  func<=readdata(5 downto 0);    
  shift<=readdata(10 downto 6);
--b1<=(b and not (mmwrt(0))); 
--process(en,b1,manish)
--begin
--   if(en'event and en='1') then 
--    if(manish="1") then
--        b<=not(mmrd);
--        counter<=counter+1;
--        if(counter=5) then
--            counter<=0;
--               b<=mmrd;
--            manish<="0";
--        end if;
--      else
--         --   b1<=b;
--     end if;
--   end if;
--end process;


mmwrt(0)<= not(mmrd);
     
U10:blk_mem_gen_0
  PORT MAP(
        clka=>en,
        ena =>b,
        wea =>mmwrt,
        addra=>pc_x2,
        dina =>rg_out2,
        douta =>readdata
      );
  
U5:entity work.Register_file (beh) 
	port map(
        clk=>en,
		reg_write=>regwrt,
		read_reg_1=>rd_reg1,
	    read_reg_2=>rd_reg2,
	    
	    write_reg=>mux_rt_rd,
		write_data=>wrt_data,
		read_data_1=>rg_out1,
	    read_data_2=>rg_out2
	);



U8:entity work.control_unit(Behavioral)
Port map( 
        op=>op,
        fun=>func,
        memtoreg=>memtoreg,
      --  memwrite=>mmwrt,
        memrd=>mmrd,
        ALUcontrol=>ALUctr,
        ALUsrc=>ALUsrc,
        regdst=>regdst,
        regwrt=>regwrt
);   

U6:entity work.ALU(Behavioral)
        Port map( 
        clk=> b,
        srcA=>rg_out1,
        srcB=>ALUinput2,
        ALUcontrol=>ALUctr,
        writedata=>ALUresult,
        shift=>shift,
        count_in=>pc_x2,
        count_out=>pc_x2
);
U9:entity work.MUX_1(Behavioral)
  Port map(
            input_1=>rg_out2,
            input_2=>out_extend,
            output=>ALUinput2,
            switch=>ALUsrc
        );
U2:entity work.MUX_1(Behavioral)
  Port map(
            input_1=>ALUresult,
            input_2=>readdata,
            output=>wrt_data,
            switch=>memtoreg
        );

U3:entity work.SIGN_EXTEND(Behavioral)
  Port map(
            input_1=>for_extend,
            output_1=>out_extend
       ); 
    
U4:entity work.MUX_rt_rd(Behavioral)
  Port map(
            input_1=>rd_reg2,
            input_2=>wrt_reg,
            output=>mux_rt_rd,
            switch=>regdst
        ); 
    
    
    
    
end Behavioral;
