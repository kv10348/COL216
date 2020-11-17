#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "all.h"

extern const char func[][8]={"add","sub","slt","and","or","syscall","beq","lw","sw","li","move","j","bne","bgtz","bltz"};
extern const int opcode[]={ADD, SUB, SLT, AND, OR,SYSCALL, BEQ, LW, SW, LI, MOVE, J,BNE,BGTZ,BLTZ};


int* encode(char* input,int* coded, struct data_memory *dm, int num){
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
        for(j=0;j<15;j++){
                if(!strcmp(inst,func[j])){
                        break;
                }
        }
        if(j<15){
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
                        coded[1]=reg_num(reg);



                }
                 for(;input[i]==',' || input[i]==32;i++);		
		
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';				// Add NULL character to terminate string
		
		coded[2]=label_pos(var_name);
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
                for(;input[i]==',' || input[i]==32;i++);		
		
		
		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';				// Add NULL character to terminate string
		
		coded[3]=label_pos(var_name);



        }else if(coded[0]==J){ 
                char var_name[20];
                int j;
                for(;input[i]==32 ;i++);

		for(j=0;input[i]!=32 && input[i]!=10 && input[i]!='\x0' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++)
		{
			var_name[j]=input[i];
			
		}	
		var_name[j]='\x0';
                coded[1]=label_pos(var_name);

        }
        else if(coded[0]==LI){
                char reg[3];
                int j;
        // LW and SW
        }else if(coded[0]==LW || coded[0]==SW){
                char reg[3];
                char var_name[20];
                int j;
                for(;input[i]==','|| input[i]=='$'|| input[i]==32 ;i++);//igoring the , whitespace and $ before the value of register one
                for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=',' && j<2 && input[i]!='#' && input[i]!=9;i++,j++){
                       reg[j]=input[i];
                }
                reg[j]='\x0';
                coded[1]=reg_num(reg);
            //    printf("%s %d \n","coded[1] ",coded[1]);
                for(; input[i]==32 ||input[i]==',';i++);
                for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!='(' && input[i]!=',' && input[i]!='#' && input[i]!=9;i++,j++){
                       var_name[j]=input[i];
                }
               
                var_name[j]='\x0';
             //   printf("varname %s\n",var_name);
                int a=atoi(var_name);
                coded[2]=a;
                if(input[i+1]=='$'){
                        i=i+2;
                        for(j=0;input[i]!=32 && input[i]!='\x0' && input[i]!=10 && input[i]!=','&& input[i]!=')' && input[i]!='#' && input[i]!=9;i++,j++){
                       reg[j]=input[i];
                        }
                        reg[j]='\x0';
                        coded[3]=reg_num(reg);
                      //    printf("%s %d \n","coded[3] ",coded[3]);
                }else{
                       printf("%s\n","Syntax error");
                }

        }else {

        }

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
void decode(int *encoded_inst, struct data_memory *dm){
       
        if(encoded_inst[0]==ADD)
	{	
                // printf("%s\n","add");
				add(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        }else if(encoded_inst[0]==J){
                                jump(encoded_inst[1]);
        }else if(encoded_inst[0]==BNE){
                bne(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        }else if(encoded_inst[0]==BEQ){
                 beq(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
        }else if(encoded_inst[0]==BGTZ){
                 bgtz(encoded_inst[1],encoded_inst[2]);
        }else if(encoded_inst[0]==BLTZ){
                 bltz(encoded_inst[1],encoded_inst[2]);
        }
		else if(encoded_inst[0]== SUB){
				sub(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
                }else if (encoded_inst[0]==AND){
		
				and_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
                }else if(encoded_inst[0]==OR){
		
				or_(encoded_inst[1],encoded_inst[2],encoded_inst[3]);
		}else if(encoded_inst[0]==SLT){
				slt(encoded_inst[1],encoded_inst[2],encoded_inst[3]);	
                }else if(encoded_inst[0]==LW){
		
				lw(encoded_inst[1],encoded_inst[2],encoded_inst[3],dm);
		}else if(encoded_inst[0]==SW){
		
				sw(encoded_inst[1],encoded_inst[2],encoded_inst[3],dm);
                }else{ 
			printf("Unknown instruction\n");
				pc++;
        }
        return;

}
void load_instruct_mem(struct inst_mem*im,int mem_pos,int*instruct){
      //  printf("%s\n","load_inst_mem");
        int j=0;
        for(j=0;j<4;j++){
                (im->mem[mem_pos].code[j]=instruct[j]);
                
        }
       // printf("%d\n",mem_pos);
        // for(int i=0;i<4;i++){
        //         printf("%d ",im->mem[mem_pos].code[i]);
        // }
        // printf("\n");
        return;
}
void execute(struct inst_mem *im, int k, struct data_memory *dm){
        pc=0;
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
        while(pc<k){
                printf("PC:= %d\n",pc);
                decode(im->mem[pc].code,dm);
             
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
}