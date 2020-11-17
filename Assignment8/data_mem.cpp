#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

#include "all.h"



void store(int position,struct data_memory *dm,char* val_name,int val){
        if(position>=4096){
                printf("%s\n","Not sufficient space.");
                exit(8);
        }
        strcpy(dm->mem[position].name,val_name);
        dm->mem[position].val=val;
        return ;
}
int get_location(char* var_name, struct data_memory *dm){
        for(int i=0;i<4096;i++){
                if(!strcmp(dm->mem[i].name,var_name)){
                        return i;
                }
        }
       printf("Undefined refrence %s\n",var_name);
}




