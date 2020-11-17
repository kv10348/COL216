#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "all.h"

struct reg register_file[32];

void init_reg_file(){
                // cout << "init_reg_file";
                // cout << "\n";
                strcpy(register_file[0].first_name,"zero");
                strcpy(register_file[1].first_name,"at");
                strcpy(register_file[2].first_name,"v0");
                strcpy(register_file[3].first_name,"v1");
                strcpy(register_file[4].first_name,"a0");
                strcpy(register_file[5].first_name,"a1");
                strcpy(register_file[6].first_name,"a2");
                strcpy(register_file[7].first_name,"a3");
                strcpy(register_file[8].first_name,"t0");
                strcpy(register_file[9].first_name,"t1");
                strcpy(register_file[10].first_name,"t2");
                strcpy(register_file[11].first_name,"t3");
                strcpy(register_file[12].first_name,"t4");
                strcpy(register_file[13].first_name,"t5");
                strcpy(register_file[14].first_name,"t6");
                strcpy(register_file[15].first_name,"t7");
                strcpy(register_file[16].first_name,"s0");
                strcpy(register_file[17].first_name,"s1");
                strcpy(register_file[18].first_name,"s2");
                strcpy(register_file[19].first_name,"s3");
                strcpy(register_file[20].first_name,"s4");
                strcpy(register_file[21].first_name,"s5");
                 strcpy(register_file[22].first_name,"s6");
                strcpy(register_file[23].first_name,"s7");
                strcpy(register_file[24].first_name,"t8");
                 strcpy(register_file[25].first_name,"t9");
                strcpy(register_file[26].first_name,"k0");
                strcpy(register_file[27].first_name,"k1");
                 strcpy(register_file[28].first_name,"gp");
                strcpy(register_file[29].first_name,"sp");
                strcpy(register_file[30].first_name,"fp");
                 strcpy(register_file[31].first_name,"ra");
                 register_file[11].val=12;
                 register_file[9].val=23;
                return ;
}
int reg_num(char* first_name){
        int i;
        i=strlen(first_name);
        for(int i=0;i<32;i++){
                //  cout << "init_reg_file "<<i ;
                if(!strcmp(register_file[i].first_name,first_name)){
                        return i;
                }
              
        }
        if(!strcmp(first_name,"s8")){
                return 30;
        }else{
                printf("No such register %s exit", first_name);
                exit(0);
        }
}
// int main(){
//         char*  age;
//        // cin >> age;
//         init_reg_file();
//         char* a="s8";
//        int b=reg_num(a);
//        cout <<"input:"<<b;
//         cout <<"\n";
// }
