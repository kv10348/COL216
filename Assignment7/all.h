// #ifndef DATA_MEMORY_H_INCLUDED
// #define DATA_MEMORY_H_INCLUDED
// #ifndef FILE_FUNC_INCLUDED
// #define FILE_FUNC_INCLUDED
// #ifndef INSTRUCTION_MEM_H_INCLUDED
// #define INSTRUCTION_MEM_H_INCLUDED
// #ifndef OPERATIONS_H_INCLUDED
// #define OPERATIONS_H_INCLUDED
// #ifndef REGISTERS_H_INCLUDED
// #define REGISTERS_H_INCLUDED
// #ifndef PC_INCLUDED
// #define PC_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct data_memory
{
	struct data_mem_element
	{
		char name[20];
		int val;
	
	}mem[1024]; 
};
void store(int pos,struct data_memory *dm,char*var_name,int val);
int get_mem_location(char*var_name,struct data_memory *dm);

char* int2bin(int input,int len,char*bin);
#define ADD 0b100000		//ADD   => 32
#define SUB 0b100010		//SUB   => 34
#define AND 0b100100		//AND   => 36
#define SLT 0b101010		//SLT   => 42
#define OR 0b100101		//OR    => 37
#define LI 0b100001		//LI    => 33
#define SYSCALL 0b001100	//SYSCALL=>12
#define LW 0b100011		//LW    => 35
#define SW 0b101011		//SW    => 43
#define J 0b000010		//J     => 2
#define BEQ 0b000100		//BEQ   => 4		
#define MOVE 0b000110		//MOVE  => 6
#define BNE 0b000111             // not equal 7
#define BLTZ 0b001111             // not equal 1
#define BGTZ 0b011111             // not equal 31


struct instruct_mem_element
{
	int code[4];
	char*c;
};


struct inst_mem
{
	struct instruct_mem_element mem[1024];
	
};

struct label_table
{
	struct label_element{
		char name[20];
		int inst_num;	
	}label[100];
}labels;
int label_num;



int* encode(char*input,int*coded,struct data_memory*dm,int num);	 //Function to convert text into opcodes.
void decode(int*encoded_inst,struct data_memory*dm);	// Decode and perform the instructions.

/*****************************************************************/


/********** FUNCTIONS TO LOAD & EXECUTE THE INSTRUCTIONS *********/

void load_instruct_mem(struct inst_mem*im,int mem_pos,int*instruct);  //Function to load the instruction into the instruction memory. 
void execute(struct inst_mem*im,int fin,struct data_memory*dm);


int label_pos(char*name);			// Returns the index of the label structure storing the label-name
void add (int dest,int reg1,int reg2);		// Stores the sum of values in reg1 and reg2 in dest.
void sub (int dest,int reg1,int reg2);		// Stores the difference of values in reg1 and reg2 in dest.
void and_(int dest,int reg1,int reg2);		// Stores the 'and' of values in reg1 and reg2 in dest.
void slt (int dest,int reg1,int reg2);		// Stores the slt of values in reg1 and reg2 in dest.
void or_ (int dest,int reg1,int reg2);		// Stores the 'or' of values in reg1 and reg2 in dest.
void li(int dest,int val);
void lw(int dest,int base,int addr,struct data_memory*dm);
void sw(int dest,int base,int addr,struct data_memory*dm);
void jump(int num);
void syscall();
void beq(int reg1,int reg2,int pc_dest);
void bne(int reg1,int reg2,int pc_dest);
void bgtz(int reg1,int pc_dest);
void bltz(int reg1,int pc_dest);
void move(int dest,int src);
int pc;
struct reg
{
	char first_name[4];			// Stores names like $t0, $fp, $at
	int val;
};


extern struct reg register_file[32];
void init_reg_file();	   // To initialise the register file (This is has to be called before the first reference to registers)
int reg_num(char*first_name);	// Returns the number of the register given the alternate name.
int reading(FILE*file,struct inst_mem*im,struct data_memory*dm);   //Reads the file and includes the necessary instructions into the Instruction Memory
					   //in the encoded form. 
void put_to_file(FILE*file,struct inst_mem*im,int len,struct data_memory*dm);
