#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
// #include "data_mem.h"
// #include "file_function.h"
// #include "instruction.h"
// #include "operation.h"
// #include "registers.h"
// #include "pc.h"
#include "all.h"

void add(int rd,int reg1, int reg2)
{
        printf("%s\n","ADD");
        int a,b;
        if(reg1<32 && reg2<32 && rd<32){
                a=register_file[reg1].val;
                b=register_file[reg2].val;
                register_file[rd].val=(a+b);
        }
       pc++;
       return ;
}
void sub(int rd,int reg1, int reg2){
        int a,b;
          printf("%s\n","SUB");
        if(reg1<32 && reg2<32 && rd<32){
                a=register_file[reg1].val;
                b=register_file[reg2].val;
                register_file[rd].val=(a-b);
        }
       pc++;
       return;
}
void and_(int rd,int reg1, int reg2){
        int a,b;
        if(reg1<32 && reg2<32 && rd<32){
                a=register_file[reg1].val;
                b=register_file[reg2].val;
                register_file[rd].val=(a&b);
        }
       pc++;
       return ;
}
void or_(int rd,int reg1, int reg2){
        int a,b;
        if(reg1<32 && reg2<32 && rd<32){
                a=register_file[reg1].val;
                b=register_file[reg2].val;
                register_file[rd].val=(a|b);
        }
       pc++;
       return;
}
void slt(int rd,int reg1, int reg2){
        int a,b;
          printf("%s\n","SLT");
        if(reg1<32 && reg2<32 && rd<32){
                a=register_file[reg1].val;
                b=register_file[reg2].val;
                if(a<b){
                        register_file[rd].val=1;
                }else{
                        register_file[rd].val=0;
                }
        }
        pc++;
        return;
}
void li(int dest,int val)
{
        register_file[dest].val=val;
        pc++;
       return ;
}
//LW or SW
void lw(int dest,int base, int addr,struct data_memory *dm ){
        addr=addr+base;
          printf("%s\n","LW");
        register_file[dest].val=(dm->mem[addr].val);
        pc++;
        return;
}
void sw(int dest,int base, int addr ,struct data_memory *dm){
       printf("%s\n","SW");
        addr=addr+base;
       

        dm->mem[addr].val=register_file[dest].val;
       pc++;
       return;

}
void beq(int reg1,int reg2,int pc_dest){
        if(register_file[reg1].val==register_file[reg2].val){
                pc=labels.label[pc_dest].inst_num;
        }else{
                pc++;
        }
        return;
}
void bne(int reg1,int reg2,int pc_dest){
        if(register_file[reg1].val!=register_file[reg2].val){
                pc=labels.label[pc_dest].inst_num;
        }else{
                pc++;
        }
        return;
}
void bgtz(int reg1,int pc_dest){
        printf("%s\n","BGTZ");
        if(register_file[reg1].val>0){
                pc=labels.label[pc_dest].inst_num;
        }else{
                pc++;
        }
        return;
}
void bltz(int reg1,int pc_dest){
        if(register_file[reg1].val<0){
                pc=labels.label[pc_dest].inst_num;
        }else{
                pc++;
        }
        return;
}
// branch instruction 
void jump(int num){
        printf("%s\n","jump");
        pc=labels.label[num].inst_num;
        return;
}
//syscall
void syscall(){
        if(register_file[2].val==1){
                printf("%d\n",register_file[4].val);
        }else if(register_file[2].val==5){
               

               
        }else if(register_file[2].val==10){
                exit(0);

        }
      pc++;
        return ;

}
//move instruction
void move(int dest, int src){
        register_file[dest].val=register_file[src].val;
      pc++;
      return;
}
