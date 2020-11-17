     ## ASSIGNMENT-3

-Execute Six instruction that is "add,sub,srl,sll,lw,sw".
-These are the following substituents that we have written in vhdl:

 Program_Counter: This will take 32bit input and it has one output which is also of 32bit.each clock cycle it will get incremented by plus one so that the it points to next instruction address.

 Adder: for incrementing the address by one which is coming from program counter.

 Instruction_Memory: it has array of array of length 32 bit each.In this i am storing the the instruction which is of 32 bit.it has one input and one outpu.input is the define address corresponding to which the 			     index will found and from that index instruction will send as output.

 Register file: There is 32 register we have defined here.In this we are taking 6 input.one for read_reg1(5 bit its address of the register from where the data is to be taken),one for read_reg2 (5 bit its 			address of the register from where the data is to be taken),one for,write_reg (register address on which the the result out get written),one for write_data (32 bit input from alu result),clk.
		And there are two output of 32 bit,the output the data stoted at the given address.

 Sign_extended: it has one input of 16 bit ,it basically extend that 16 bit to 32bit,means output of 32bit.

 Data_memory: it has an array of lenght 32.At each index there is array of 32bit to store data.it takes five input and have one output.address and write_data are output of 32 bit for first finding the index to 		      which read the data and second for write data.other two input is std_logic for indicating read or write mode and one for clock.
	      output is read_data(data readed from given address) of 32bit.
 
 MUX: Here,I have used total 3 mux,one which take two 5bit input and according to 0 and 1 it gives corresponding output,the other two mux that have been used are of 32bit input each and similarly corresponding 	to switch signal it pass either one of them as output.

 ALU:
	This will take two 32bits input one from register file and other from MUX_rd_rt. This will take ALUcontrol(2 downto 0), shift amount and will give one output writedata. Here ALUcontrol which is coming from controlunit will take care what to with these inputs. ALUcontrol will give the commands according to what we execution we have to do. 
inputs.

 Control_Unit:
	This is like controling everything and control every part of this project what they have to do. It will take op(31 downto 26) and func(5 downto 0) part of any execution then it will decide what they wants from us. Depending upon what execution say it will commands to everypart of this assignemnt what they have to do. 
	Here we are enconding all the six commands using 3bits binary number.
	
 
