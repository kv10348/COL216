#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <time.h>
#include <stdlib.h>
#define PROBABILITY 0.70
#define N 30
using namespace std;
#include "all.h"
stack<int> STACK;  // STACK.push(data)  , STACK.pop() delete the top data , STACK.top() give the data which is in the top

extern const char func[][8]={"add","sub","slt","and","or","syscall","beq","lw","sw","li","move","j","bne","bgtz","bltz","jr","jal","end"};
extern const int opcode[]={ADD, SUB, SLT, AND, OR,SYSCALL, BEQ, LW, SW, LI, MOVE, J,BNE,BGTZ,BLTZ,JR,JAL, END};
int pc;
int jal_inst;
struct label_table labels;
int FUNC_HIT_MISS(float x, int a){
        srand(time(0));
    bool res = (rand() % 100) < (100*x);
    if (res) return 1;
    else return a;
}
int bubbles=0;;
void encode(char* input,int* coded, struct data_memory *dm, int num){
       // printf("%d %s\n", global_pc, "**********************");
        char inst[10];
     
//        printf("%s\n","--------------");
//        printf("%s\n",input);
       
        int i;
        char *ptr;
        int j;

        if(ptr=strchr(input,':')){
              //  printf("%s\n","pointer");
                coded[0]=0;
                int exit=0;
                i=0;
               for(;input[i]!=':' && input[i]!=32;i++){
			inst[i]=input[i];
               }
		inst[i]='\x0';
             //   printf("%s\n","pointer");
                for(j=0;j<label_num;j++){
                        if(!strcmp(labels.label[j].name,inst)){
                                if(labels.label[j].inst_num==-1){
                                        exit=1;
                                        labels.label[j].inst_num=num;
                                        return;
                                }else{
                                        printf("%s\n","mulitiple defintions ");
                                      EXIT_FAILURE;
                                }
                        }
                }
              //   printf("%s\n","pointer");
                if(!exit){
                          
                          for(;input[i]==32 || input[i]==':' || input[i]==9;i++);
                        
                        strcpy(labels.label[label_num].name,inst);
                        labels.label[label_num].inst_num=num;
                        label_num++;
                        if(input[i]=='#' ||  input[i]=='\x0'|| input[i]=='\n')
                                return;
                               
                        
                      

                }

        }


        for(j=0,i=0;(input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=9);j++,i++){
        
                inst[j]=input[i]; //copying the first word
        }
        inst[j]='\x0';
       // printf("%s*****************\n",inst);
        for(j=0;j<18;j++){
                if(!strcmp(inst,func[j])){
                        break;
                }
        }
        if(j<18){
                coded[0]=opcode[j];
        }else{
               printf("Given instruction %s is not valid",inst);
              // exit(3);
        }

        //R type 
        if(coded[0]==ADD|| coded[0]==SUB || coded[0]==AND || coded[0]==OR|| coded[0]==SLT){
                char reg[3];
               
            //    printf("%d\n",coded[0]);
        
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
        
        //regsiter one
                if(input[i-1]!='$'){

                       printf("%s\n","Syntax error");

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                                reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[1]=reg_num(reg);



                }
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
        //register two
                  if(input[i-1]!='$'){

                       

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                        reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[2]=reg_num(reg);
                }
                 for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
        //register three
                  if(input[i-1]!='$'){

                         printf("%s\n","Syntax error");

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                        reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[3]=reg_num(reg);
                }
                coded[4]=-1;
               
              //  printf("%d %d %d %d \n", coded[0],coded[1],coded[2],coded[3]);
                
        }else if(coded[0]==BLTZ|| coded[0]==BGTZ){
               
            //    printf("%s\n","88888888888888888888888888888");
                char reg[3];
                char var_name[20];
                int j;
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);
                 if(input[i-1]!='$'){

                       printf("%s\n","Syntax error");

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                        reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[2]=reg_num(reg);
                      //  printf("%d\n", coded[1]);



                }
                 for(;input[i]==',' || input[i]==32;i++);		
		
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';				// Add NULL character to terminate string
		
		coded[4]=label_pos(var_name);
                //coded[4]=-1;
        }
        else if(coded[0]==BEQ || coded[0]==BNE   ){
               
                char reg[3];
                  char var_name[20];
                   int j;
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
        
        //regsiter one
                if(input[i-1]!='$'){

                       printf("%s\n","Syntax error");

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                        reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[2]=reg_num(reg);



                }
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
        //register two
                  if(input[i-1]!='$'){

                       

                }else{
                        j=0;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                        reg[j]=input[i];
                        }
                        reg[j]='\0';
                        coded[3]=reg_num(reg);
                }
                for(;input[i]==',' || input[i]==32;i++);		
		
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';				// Add NULL character to terminate string
		
		coded[4]=label_pos(var_name);
              //  coded[4]=-1;

        }else if(coded[0]==J || coded[0]==JAL){ 
               
                char var_name[20];
                int j;
                for(;input[i]==32 ;i++);

		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';
                coded[4]=label_pos(var_name);

        }
        else if(coded[0]==LI){
             
                char reg[3];
                int j;
        // LW and SW
        }else if(coded[0]==LW || coded[0]==SW){
              //  printf("%s\n","SW-------------->");
              
                char reg[3];
                char var_name[20];
                int j;
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
                for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                       reg[j]=input[i];
                }
                reg[j]='\x0';
                coded[3]=reg_num(reg);
            //    printf("%s %d \n","coded[1] ",coded[1]);
                for(; input[i]==32 ||input[i]==',';i++);
                for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!='(' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++){
                       var_name[j]=input[i];
                }
               
                var_name[j]='\x0';
               // printf("varname %s\n",var_name);
                int a=atoi(var_name);
                coded[4]=a;
                if(input[i+1]=='$'){
                        i=i+2;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=','&& input[i]!=')' && input[i]!='#' && input[i]!=9;i++,j++){
                                reg[j]=input[i];
                        }
                        reg[j]='\x0';
                        coded[2]=reg_num(reg);
                      //    printf("%s %d \n","coded[3] ",coded[3]);
                }else{
                       printf("%s\n","Syntax error");
                }

        }else {

        }

       // printf("%s %d\n", "++++++++++++", global_pc);
}
int label_pos(char*name)
{
	int i;
	
	for(i=0;i<=label_num;i++)
	{
		if(!strcmp(labels.label[i].name,name))
		return i;
	}
	
	// This means the reference has not been found yet. Store it in the array 
	strcpy(labels.label[label_num].name,name);
	labels.label[label_num].inst_num=-1;
	
	return label_num++;
	
}
int   	ALU_input_1,ALU_input_2,ALU_output;        // ALU intputs and output
struct instruction {
	int     op;		/* operation (op-code) */
	int	rd;		/* rd register tag */
	int	rs;		/* rs register tag */
	int	rt;		/* rt register tag */
	int	imm;		/* actual immediate value in assembler inst */
};
struct pipline {
	struct 	instruction   IR;
	int 	pc;
	int 	npc;
	int   	A,B; 
	int   	LMD;
	int   	ALU_output;
};
int cycle;
int npc;
int   	stall_lw;
int	stall_branch;
struct pipline IF_ID;
struct pipline ID_EX;
struct pipline EX_MEM;
struct pipline MEM_WB;
struct pipline deposit_IF_ID;
struct pipline deposit_ID_EX;
struct pipline deposit_EX_MEM;
struct pipline deposit_MEM_WB;

void IF(struct inst_mem *im){
        //printf("%d\n",pc);
        
       
        int* encoded_inst;
        encoded_inst=im->mem[pc].code;
        IF_ID.IR.op=encoded_inst[0];
        IF_ID.IR.rd=encoded_inst[1];
        IF_ID.IR.rs=encoded_inst[2];
        IF_ID.IR.rt=encoded_inst[3];
        IF_ID.IR.imm=encoded_inst[4];
         if(encoded_inst[0]==JAL){
                //printf("")
                jal_inst=pc+1;
               // printf("%s%d%d\n","JAL------",encoded_inst[2],encoded_inst[3]);
        }
          if (deposit_IF_ID.IR.op==END || deposit_ID_EX.IR.op==END || deposit_EX_MEM.IR.op==END || deposit_MEM_WB.IR.op==END){
                IF_ID.IR.op=0;
                IF_ID.IR.rd=-1;
                IF_ID.IR.rs=-1;
                IF_ID.IR.rt=-1;
                IF_ID.IR.imm=0;
                //printf("%s%d%d\n","J------",encoded_inst[2],encoded_inst[3]);
        }
        IF_ID.pc=pc;
        IF_ID.npc=npc;
        npc=pc+1;
        //printf("%d\n", pc);
        if(IF_ID.IR.op==0){
                printf("   %s\t\t\t","---");
        }else{
                 printf("   %d\t\t\t",IF_ID.IR.op);
        }
        
        // printf("%s\n", "IF stage ==========");
        // printf("%s %d\n","global_pc",global_pc);
        // printf("%s %d\n","Opcode " ,encoded_inst[0]);
        // printf("%s %d\n","rd ", encoded_inst[1]);
        // printf("%s %d\n","rs", encoded_inst[2]); 
        // printf("%s %d\n","rt", encoded_inst[3]); 
        //  printf("%s %d\n","imm", encoded_inst[4]); 
       
       
}

void ID(){
       // printf("%s\n", " ID stage ===========");
        if(deposit_IF_ID.IR.op==0){
                printf("\t   %s\t\t\t","---");
        }else{
                printf("\t   %d\t\t\t",deposit_IF_ID.IR.op);
        }
        if (deposit_IF_ID.pc < 0||deposit_IF_ID.pc >= global_pc)  { 
            //    printf("%s\n","ID <0 ============");
                ID_EX.npc=deposit_IF_ID.npc;
                ID_EX.IR=deposit_IF_ID.IR;
                ID_EX.pc=deposit_IF_ID.pc;
                
                deposit_IF_ID.IR=IF_ID.IR;
                deposit_IF_ID.pc=IF_ID.pc;
                deposit_IF_ID.npc=IF_ID.npc;
                return;
	}
	
	
	// predict stall or not for lw
        // printf("%d\n",deposit_ID_EX.IR.op );
        //  printf("%d\n",deposit_ID_EX.IR.rt );
         // printf("%d\n",deposit_ID_EX.IR.op );
	// predict stall or not for lw
	// if (deposit_ID_EX.IR.op == LW && (deposit_IF_ID.IR.rt==deposit_ID_EX.IR.rt||deposit_IF_ID.IR.rs==deposit_ID_EX.IR.rt)) //it is forwarding and lw
	// {
	// stall_lw=1;
        // }
       
              

  
 
	ID_EX.npc=deposit_IF_ID.npc;  
	ID_EX.IR=deposit_IF_ID.IR;
    	ID_EX.pc=deposit_IF_ID.pc;
	// printf("%s %d \n","ID_EX.IR.rd",ID_EX.IR.rd);
        // printf("%s %d \n","ID_EX.IR.rs",ID_EX.IR.rs);
        // printf("%s %d \n","ID_EX.IR.rt",ID_EX.IR.rt);
        // printf("%s %d \n","ID_EX.IR.op",ID_EX.IR.op);
	deposit_IF_ID.IR=IF_ID.IR;
	deposit_IF_ID.pc=IF_ID.pc;
	deposit_IF_ID.npc=IF_ID.npc;
     
        
}
int   A, B;                                     // ID register read values
int   	cond;                                     // branch condition test
void EXE(struct data_memory *data_mem){
        if(deposit_ID_EX.IR.op==0){
                printf("\t   %s\t\t\t","---");
        }else{
                printf("\t   %d\t\t\t",deposit_ID_EX.IR.op);
        }
       // printf("%s\n","EXE stage ========");
         /* ------------------------------ EX stage ------------------------------ */
  
  if (deposit_ID_EX.pc < 0||deposit_ID_EX.pc >= global_pc)  { 
      //  printf("%s","EXE <0 ========" );
	EX_MEM.A=A;
	EX_MEM.B=B;
	EX_MEM.npc= deposit_ID_EX.npc;
	EX_MEM.IR= deposit_ID_EX.IR;
        EX_MEM.pc =deposit_ID_EX.pc;
	EX_MEM.ALU_output =ALU_output;
	deposit_ID_EX.npc= ID_EX.npc;
	deposit_ID_EX.IR= ID_EX.IR;
        deposit_ID_EX.pc= ID_EX.pc;
        return;
	}
	
	
	A=register_file[deposit_ID_EX.IR.rs].val;   /* read registers */
       // printf("%s %d\n","*************",deposit_ID_EX.IR.rs);
        //  printf("%s %d\n","EXE ",A);

        // B=register_file[deposit_ID_EX.IR.rt].val;
        // ALU_input_1 = A;
        // ALU_input_2 = B;
        //register_file[reg1].val;
	//DATA fowarding for SW
	//DATA fowarding for SW
	if (deposit_ID_EX.IR.op== SW){
		if((deposit_EX_MEM.IR.op == ADD || deposit_EX_MEM.IR.op == SUB || deposit_EX_MEM.IR.op ==AND || deposit_EX_MEM.IR.op == OR  )&& deposit_ID_EX.IR.rt==deposit_EX_MEM.IR.rd)
			B= deposit_EX_MEM.ALU_output;
		
		else if ((deposit_MEM_WB.IR.op == ADD || deposit_MEM_WB.IR.op == SUB || deposit_MEM_WB.IR.op ==AND || deposit_MEM_WB.IR.op == OR  )&& deposit_ID_EX.IR.rt==deposit_MEM_WB.IR.rd) 
			B=deposit_MEM_WB.ALU_output;
		
		else if (deposit_MEM_WB.IR.op == LW && deposit_ID_EX.IR.rt== deposit_MEM_WB.IR.rt) 
			B=deposit_MEM_WB.LMD;
                else
                B=register_file[deposit_ID_EX.IR.rt].val;
        }
	else{	B=register_file[deposit_ID_EX.IR.rt].val;}

	// //DATA forwarding for ADD,SUB and so on
	if ((deposit_EX_MEM.IR.op == ADD || deposit_EX_MEM.IR.op ==SUB || deposit_EX_MEM.IR.op ==AND || deposit_EX_MEM.IR.op == OR  )&& deposit_ID_EX.IR.rs==deposit_EX_MEM.IR.rd) 
    	{
                    ALU_input_1=deposit_EX_MEM.ALU_output;
            }	
	 
        else if ((deposit_MEM_WB.IR.op == ADD || deposit_MEM_WB.IR.op == SUB || deposit_MEM_WB.IR.op ==AND || deposit_MEM_WB.IR.op == OR  )&& deposit_ID_EX.IR.rs==deposit_MEM_WB.IR.rd) 
            {
                     ALU_input_1=deposit_MEM_WB.ALU_output;
            }   

	else if (deposit_MEM_WB.IR.op == LW && deposit_ID_EX.IR.rs==deposit_MEM_WB.IR.rt) 
	{
                ALU_input_1=deposit_MEM_WB.LMD;
        }	
	else if (deposit_EX_MEM.IR.op == LW && deposit_ID_EX.IR.rs==deposit_EX_MEM.IR.rt)
           {
                    //  printf("%s\n","&&&&&&&&&&&&&&&&");
                    ALU_input_1=data_mem->mem[deposit_EX_MEM.ALU_output].val;
           }    
        else
	    {
                    ALU_input_1 = A;
            }    
	
	
	//DATA forwarding for ADD,SUB and so on
	if (deposit_ID_EX.IR.op == LW   ||deposit_ID_EX.IR.op == SW ){
                ALU_input_2 = deposit_ID_EX.IR.imm;
        }else if ((deposit_EX_MEM.IR.op == ADD || deposit_EX_MEM.IR.op == SUB || deposit_EX_MEM.IR.op ==AND || deposit_EX_MEM.IR.op == OR )&& deposit_ID_EX.IR.rt==deposit_EX_MEM.IR.rd){
                ALU_input_2=deposit_EX_MEM.ALU_output;
        }else if ((deposit_MEM_WB.IR.op == ADD || deposit_MEM_WB.IR.op == SUB || deposit_EX_MEM.IR.op ==AND || deposit_EX_MEM.IR.op == OR  )&&deposit_ID_EX.IR.rt==deposit_MEM_WB.IR.rd) 
	{
                ALU_input_2=deposit_MEM_WB.ALU_output;
        }	
	else if (deposit_MEM_WB.IR.op == LW &&deposit_ID_EX.IR.rt==deposit_MEM_WB.IR.rt) 
	{
                ALU_input_2=deposit_MEM_WB.LMD;
        }	
        else if (deposit_EX_MEM.IR.op == LW && deposit_ID_EX.IR.rt==deposit_EX_MEM.IR.rt)
          {
                        //  printf("%s\n","&&&&&&&&&&&&&&&&");
                ALU_input_2=data_mem->mem[deposit_EX_MEM.ALU_output].val;
          }    
	else
	{
                ALU_input_2 = B;
        }	

        // DATA forwarding for SLT, BEQ, BNQ , BGTZ , BLTZ
        // if((deposit_EX_MEM.IR.op == ADD || deposit_EX_MEM.IR.op == SUB || deposit_EX_MEM.IR.op ==AND || deposit_EX_MEM.IR.op == OR )&& deposit_ID_EX.IR.rt==deposit_EX_MEM.IR.rd){

        // }else{

        // }

       
               
	

	
        //cout<<ALU_input_1<<" "<<ALU_input_2<<"   8888888888888888888888888888pppppp"<<endl;
		
        // printf("%s %d\n %s %d\n ","deposit_ID_EX.IR.rs",deposit_ID_EX.IR.rs,"deposit_ID_EX.IR.rt",deposit_ID_EX.IR.rt);
        // printf("%s %d\n %s %d\n", "ALU_input1", ALU_input_1, "ALU_input2", ALU_input_2);
        // printf("%s %d\n", "opcode ===>",deposit_ID_EX.IR.op);
	/* calculate ALU output */
	if(deposit_ID_EX.IR.op == SUB )              //||deposit_ID_EX.IR.op == SUBI
		ALU_output = ALU_input_1 - ALU_input_2;
	else if( deposit_ID_EX.IR.op == ADD ){          //deposit_ID_EX.IR.op == ADDI||
                ALU_output = ALU_input_1+ ALU_input_2;
        }else if (deposit_ID_EX.IR.op == LW || deposit_ID_EX.IR.op == SW ){
                ALU_output= ALU_input_1+ALU_input_2;
        }                       	
        else if (deposit_ID_EX.IR.op==AND){
                ALU_output = (ALU_input_1&ALU_input_2);
        }else if (deposit_ID_EX.IR.op==OR){
                ALU_output= ALU_input_1 | ALU_input_2;
        }else if(deposit_ID_EX.IR.op==SLT){
                if (ALU_input_1<ALU_input_2){
                        ALU_output=1;
                }else{
                        ALU_output=0;
                }
        }
	int temp=deposit_ID_EX.IR.imm;
	
	/* Calculate branch condition codes 
     and change PC if condition is true */
       // printf("%s %d\n", "alu_input1 ",ALU_input_1);
	if (deposit_ID_EX.IR.op==BNE){
                cond=(ALU_input_1!=ALU_input_2);      //when BNE, the value of reg1 and reg2 would'nt be equal
        }else if (deposit_ID_EX.IR.op==BGTZ){
                //printf("%d\n",ALU_input_1);
                
		cond=(ALU_input_1>0);         //when bnez, true if A is not 0
               // printf("%s %d %s  %d\n","kapil" , ALU_input_1,"+++++++++++++++",deposit_ID_EX.IR.rs);
        }else if (deposit_ID_EX.IR.op==J){
                cond=1;          //when jump, it is always true
        }else if (deposit_ID_EX.IR.op== BLTZ){
                cond=(ALU_input_1<0);    
        }else if (deposit_ID_EX.IR.op==JAL){
                cond=1;
                if(register_file[31].val==0){
                       // printf("%s %d\n","--------------", register_file[31].val);
                        register_file[31].val=jal_inst;
                        //printf("%s %d\n","--------------", register_file[31].val);
                }else{
                        STACK.push(jal_inst);
                }
        }else if(deposit_ID_EX.IR.op==JR){
                cond=0;
                if(register_file[31].val==0){
                        printf("%s \n", "There is some ambigousity");
                        exit;
                }
                npc=register_file[31].val;
                register_file[31].val=0;
                if(STACK.size()!=0){
                        int k=STACK.top();
                        STACK.pop();
                        register_file[31].val= k;
                }
		//npc=deposit_ID_EX.npc+deposit_ID_EX.IR.imm;
		stall_branch=1;
        }
	else{
                cond=0;         
        }
		  
		
	if (cond)           
		{
                
              //  printf("%s %s %d \n","cond------> ",labels.label[temp].name,labels.label[temp].inst_num);
                npc=labels.label[temp].inst_num;
		//npc=deposit_ID_EX.npc+deposit_ID_EX.IR.imm;
		stall_branch=1;
		}
  
  
	EX_MEM.A=A;
	EX_MEM.B=B;
	EX_MEM.npc=deposit_ID_EX.npc;
	EX_MEM.IR=deposit_ID_EX.IR;
   	EX_MEM.pc=deposit_ID_EX.pc;
	EX_MEM.ALU_output=ALU_output;
	
	deposit_ID_EX.npc=ID_EX.npc;
	deposit_ID_EX.IR=ID_EX.IR;
    	deposit_ID_EX.pc=ID_EX.pc;
       


}
int   	LMD;                                     // data memory output
int   	mem_addr;                                // data memory address
void MEM(struct data_memory *data_mem){
        if(deposit_EX_MEM.IR.op==0){
                printf("\t   %s\t\t\t","---");
        }else{
                printf("\t   %d\t\t\t",deposit_EX_MEM.IR.op);
        }
      //  printf("%s\n","MEM stage ==============");
        
  /* ------------------------------ MEM stage ----------------------------- */
  if ( deposit_EX_MEM.pc < 0 ||deposit_EX_MEM.pc >= global_pc) { 
	MEM_WB.A= deposit_EX_MEM.A;
	MEM_WB.B =deposit_EX_MEM.B;
	MEM_WB.npc= deposit_EX_MEM.npc;
	MEM_WB.IR =deposit_EX_MEM.IR;
        MEM_WB.pc= deposit_EX_MEM.pc;
	MEM_WB.ALU_output= deposit_EX_MEM.ALU_output;
	MEM_WB.LMD =LMD;
	
	deposit_EX_MEM.A =EX_MEM.A;
	deposit_EX_MEM.B =EX_MEM.B;
	deposit_EX_MEM.npc= EX_MEM.npc;
	deposit_EX_MEM.IR= EX_MEM.IR;
        deposit_EX_MEM.pc= EX_MEM.pc;
	deposit_EX_MEM.ALU_output =EX_MEM.ALU_output;
        return;}
	
  
	
	mem_addr = deposit_EX_MEM.ALU_output;
      //  printf("%s %d\n","Mem_addr ===>",mem_addr );
  /* check if data memory access is within bounds */
	if (deposit_EX_MEM.IR.op ==LW ||deposit_EX_MEM.IR.op == SW){
		if (mem_addr < 0 || mem_addr >= 1024){
		printf("Exception: out-of-bounds data memory access at PC=%d\n",pc);
		exit(0);
		}
	}
        
        //  printf("%s %d\n %s %d\n ","deposit_EX_MEM.IR.rs",deposit_EX_MEM.IR.rs,"deposit_EX_MEM.IR.rt",deposit_EX_MEM.IR.rt);
        //  printf("%s %d \n", "Opcode ==>",deposit_EX_MEM.IR.op);
	if(deposit_EX_MEM.IR.op == LW){        
                int result_value=FUNC_HIT_MISS(PROBABILITY,N);
                if(result_value==1)       /* read memory for lw instruction */
                {

                }else{
                        bubbles=N;
                }
		LMD = data_mem->mem[mem_addr].val;}
	else if (deposit_EX_MEM.IR.op== SW )    {     /* or write to memory for sw instruction */
              //  printf("%s %d\n","SW ----->",deposit_EX_MEM.B);
                int result_value=FUNC_HIT_MISS(PROBABILITY,N);
                if(result_value==1)       /* read memory for lw instruction */
                {

                }else{
                        bubbles=N;
                }
		data_mem->mem[mem_addr].val= deposit_EX_MEM.B;
        }
		MEM_WB.A= deposit_EX_MEM.A;
		MEM_WB.B= deposit_EX_MEM.B;
		MEM_WB.npc =deposit_EX_MEM.npc;
		MEM_WB.IR =deposit_EX_MEM.IR;
		MEM_WB.pc =deposit_EX_MEM.pc;
		MEM_WB.ALU_output= deposit_EX_MEM.ALU_output;
		MEM_WB.LMD= LMD;
                // printf("%s\n","&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
                // printf("%d\n",MEM_WB.IR.op);
		deposit_EX_MEM.A =EX_MEM.A;
		deposit_EX_MEM.B =EX_MEM.B;
		deposit_EX_MEM.npc= EX_MEM.npc;
		deposit_EX_MEM.IR= EX_MEM.IR;
		deposit_EX_MEM.pc= EX_MEM.pc;
		deposit_EX_MEM.ALU_output =EX_MEM.ALU_output;

      //  printf("%s %d\n", "---------------->",LMD);


}
int   	wrote_r0=0;                              // register R0 written?
int   	inst_executed;                          // number of instr executed

void WB(){
         if(deposit_MEM_WB.IR.op==0){
                printf("\t   %s\t\t\t\n","---");
        }else{
                printf("\t   %d\t\t\t\n",deposit_MEM_WB.IR.op);
        }
       // printf("%s\n", "WB ====================");
         /* ------------------------------ WB stage ------------------------------ */
	if ( deposit_MEM_WB.pc < 0||deposit_MEM_WB.pc >= global_pc)  { 
		deposit_MEM_WB.A=MEM_WB.A;
		deposit_MEM_WB.B=MEM_WB.B;
		deposit_MEM_WB.npc=MEM_WB.npc;
		deposit_MEM_WB.IR=MEM_WB.IR;
		deposit_MEM_WB.pc=MEM_WB.pc;
		deposit_MEM_WB.ALU_output=MEM_WB.ALU_output;
		deposit_MEM_WB.LMD=MEM_WB.LMD;
		return;
		}
	//printf("%d\n",deposit_MEM_WB.IR.op );
  /* write to register and check if output register is R0 */
	if (deposit_MEM_WB.IR.op == ADD|| deposit_MEM_WB.IR.op == SUB) {
		register_file[deposit_MEM_WB.IR.rd].val=deposit_MEM_WB.ALU_output;
		wrote_r0=(deposit_MEM_WB.IR.rd==0);
	}
	// else if (deposit_MEM_WB.IR.op == ADDI|| deposit_MEM_WB.IR.op == SUBI) {
	// 	int_regs[deposit_MEM_WB.IR.rt]=deposit_MEM_WB.ALU_output;
	// 	wrote_r0=(deposit_MEM_WB.IR.rt==R0);
	//} 
	else if (deposit_MEM_WB.IR.op == LW){
                // printf("%s\n","LW --------------->");
                // printf("%d\n", deposit_MEM_WB.LMD);
                // printf("%d\n", deposit_MEM_WB.IR.rt);
		register_file[deposit_MEM_WB.IR.rt].val=deposit_MEM_WB.LMD;
		wrote_r0= (deposit_MEM_WB.IR.rd==0);
	}
	
	deposit_MEM_WB.A= MEM_WB.A;
	deposit_MEM_WB.B= MEM_WB.B;
	deposit_MEM_WB.npc =MEM_WB.npc;
	deposit_MEM_WB.IR =MEM_WB.IR;
        deposit_MEM_WB.pc= MEM_WB.pc;
	deposit_MEM_WB.ALU_output= MEM_WB.ALU_output;
	deposit_MEM_WB.LMD= MEM_WB.LMD;
  

	inst_executed++;

  /* if output register is R0, exit with error */
	if (wrote_r0) {
                printf("Exception: Attempt to overwrite R0 at PC=%d\n",pc);
        exit(0);
   }


}



void decode(struct inst_mem *im, struct data_memory *dm){




        if(bubbles!=0){
		//printf("%s %d \n","===================",bubbles);
                cycle=cycle+bubbles-2;
                bubbles=0;
                WB();
                return;
        }else{
        // if(encoded_inst[0]==ADD)
	// {	
        //         // printf("%s\n","add");
	// 	add(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        // }else if(encoded_inst[0]==J){
        //         jump(encoded_inst[1]);
        // }else if(encoded_inst[0]==BNE){
        //         bne(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        // }else if(encoded_inst[0]==BEQ){
        //          beq(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        // }else if(encoded_inst[0]==BGTZ){
        //          bgtz(encoded_inst[1],encoded_inst[2]);
        // }else if(encoded_inst[0]==BLTZ){
        //          bltz(encoded_inst[1],encoded_inst[2]);
        // }
	// 	else if(encoded_inst[0]== SUB){
	// 			sub(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        //         }else if (encoded_inst[0]==AND){
		
	// 			and_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        //         }else if(encoded_inst[0]==OR){
		
	// 			or_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
	// 	}else if(encoded_inst[0]==SLT){
	// 			slt(encoded_inst[1],encoded_inst[2],encoded_inst[3]);	
        //         }else if(encoded_inst[0]==LW){
		
	// 			lw(encoded_inst[1],encoded_inst[2],encoded_inst[3],dm);
	// 	}else if(encoded_inst[0]==SW){
		
	// 			sw(encoded_inst[1],encoded_inst[2],encoded_inst[3],dm);
        //         }else{ 
	// 		printf("Unknown instruction\n");
	// 			pc++;
        // }
        // if (pc < 0 || pc > global_pc){
        //         printf("%s\n","decode");
        //         printf("Exception: out-of-bounds inst memory access at PC=%d\n",pc);
        //         exit(0);
        //
        // printf("%s\n","programm stalled -----------------");       
	// printf("%d\n",pc);
	if(stall_lw==1){
                printf("%s\n","programm stalled --------------------------------------------------------------------------------------------------------------------------");
                stall_lw=0;	
                if(IF_ID.IR.op==0){
                        printf("   %s\t\t\t","---");
                }else{
                printf("   %d\t\t\t",IF_ID.IR.op);
                }
                if(deposit_IF_ID.IR.op==0){
                        printf("\t   %s\t\t\t","---");
                }else{
                        printf("\t   %d\t\t\t",deposit_IF_ID.IR.op);
                }
                 if(deposit_ID_EX.IR.op==0){
                        printf("\t   %s\t\t\t","---");
                }else{
                        printf("\t   %d\t\t\t",deposit_ID_EX.IR.op);
                }
                //===========
                MEM(dm);
                WB();
                //===========
                if(IF_ID.IR.op==0){
                        printf("   %s\t\t\t","---");
                }else{
                        printf("   %d\t\t\t",IF_ID.IR.op);
                }
                if(deposit_IF_ID.IR.op==0){
                        printf("\t   %s\t\t\t","---");
                }else{
                        printf("\t   %d\t\t\t",deposit_IF_ID.IR.op);
                }
                if(deposit_ID_EX.IR.op==0){
                        printf("\t   %s\t\t\t","---");
                }else{
                        printf("\t   %d\t\t\t",deposit_ID_EX.IR.op);
                }
                if(deposit_EX_MEM.IR.op==0){
                        printf("\t   %s\t\t\t","---");
                }else{
                        printf("\t   %d\t\t\t",deposit_EX_MEM.IR.op);
                }
                WB();
                cycle=cycle+1;
	
                deposit_EX_MEM.pc= -1;
                //deposit_EX_MEM.IR.op=ADDI;
                deposit_EX_MEM.IR.rt=-1;
                deposit_EX_MEM.IR.rs=-1;
                deposit_EX_MEM.IR.rt=-1;
                deposit_EX_MEM.IR.imm=-1;
	
	        return;
	}
       // printf("%s\n","===============================================================================================================");
	
// stall and flushing cause by branch
	if(stall_branch==1){
       
	deposit_IF_ID.pc=-1;
	deposit_IF_ID.IR.op=0;
	deposit_IF_ID.IR.rt=-1;
	deposit_IF_ID.IR.rs=-1;
	deposit_IF_ID.IR.imm=-1;
	deposit_ID_EX.pc=-1;
	deposit_ID_EX.IR.op=0;
	deposit_ID_EX.IR.rt=-1;
	deposit_ID_EX.IR.rs=-1;
	deposit_ID_EX.IR.imm=-1;
	stall_branch=0;
        
	}
	
        IF(im);
        ID();
        EXE(dm);
        MEM(dm);
        WB();
       // pc++;
        return;
        }

}
void load_instruct_mem(struct inst_mem*im,int mem_pos,int*instruct){
      //  printf("%s\n","load_inst_mem");
        int j=0;
        for(j=0;j<5;j++){
                (im->mem[mem_pos].code[j]=instruct[j]);
                
        }
       // printf("%d\n",mem_pos);
        // for(int i=0;i<4;i++){
        //         printf("%d ",im->mem[mem_pos].code[i]);
        // }
        // printf("\n");
        return;
}
void print_register(){
        printf("[zero %d] ", register_file[0].val);
        printf("[at %d] ", register_file[1].val);
        printf("[v0 %d] ", register_file[2].val);
        printf("[v1 %d] ", register_file[3].val);
        printf("[a0 %d] ", register_file[4].val);
        printf("[a1 %d] ", register_file[5].val);
        printf("[a2 %d] ", register_file[6].val);
        printf("[a3 %d] ", register_file[7].val);
        printf("[t0 %d] ", register_file[8].val);
        printf("[t1 %d] ", register_file[9].val);
        printf("[t2 %d] ", register_file[10].val);
        printf("[t3 %d] ", register_file[11].val);
        printf("[t4 %d] ", register_file[12].val);
        printf("[t5 %d] ", register_file[13].val);
        printf("[t6 %d] ", register_file[14].val);
        printf("[t7 %d] ", register_file[15].val);
        printf("[s0 %d] ", register_file[16].val);
        printf("[s1 %d] ", register_file[17].val);
        printf("[s2 %d] ", register_file[18].val);
        printf("[s3 %d] ", register_file[19].val);
        printf("[s4 %d] ", register_file[20].val);
        printf("[s5 %d] ", register_file[21].val);
        printf("[s6 %d] ", register_file[22].val);
        printf("[s7 %d] ", register_file[23].val);
        printf("[t8 %d] ", register_file[24].val);
        printf("[t9 %d] ", register_file[25].val);
        printf("[k0 %d] ", register_file[26].val);
        printf("[k1 %d] ", register_file[27].val);
        printf("[gp %d] ", register_file[28].val);
        printf("[sp %d] ", register_file[29].val);
        printf("[fp %d] ", register_file[30].val);
        printf("[ra %d] ", register_file[31].val);
        printf("\n");
}
void execute(struct inst_mem *im, int k, struct data_memory *dm){
        pc=0;
        cycle=0;
        print_register();
        // int flag= 1;
        // int i=0;
        // int size = sizeof (im->mem) / sizeof im->mem[0];
        // printf("%s\n","PPPPPPPPPPPPPPPPPPPP");

        // printf("%d\n", size);
       // int temp=0;
        while(deposit_MEM_WB.pc!=global_pc && deposit_MEM_WB.IR.op!=END){
              //  printf("%s %d %s %d \n", "global_pc ", global_pc, ", pc",pc);
                //printf("PC:= %d\n",pc);
                if(stall_branch==1){
                        printf("%s\n","branch stalll--------------");
                        //printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t\n","IF_stage","ID_stage","EXE_stage","MEM_stage","WB_stage");
                }
                printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t\n","IF_stage","ID_stage","EXE_stage","MEM_stage","WB_stage");
                
               
                decode(im,dm);
                pc=npc;
                cycle=cycle+1;
              //  printf("%d\n",npc);
               
                //im->mem[pc].code
               
        }
        print_register();
        printf("%s\n","%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
        printf("%s %d\n","Cycle ---------->",cycle);
        float temp=(global_pc/cycle);
       // printf("%s %f\n","global_pc",global_pc);
        printf("%s%7.4f\n", "Instructions per cycle ---------->",temp);
        
}
