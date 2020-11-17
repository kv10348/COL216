#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "all.h"

// #include "operation.cpp"
// #include "reg_file.cpp"
// #include "data_mem.cpp"

int start(char *line){
        int i;
        for(i=0;(line[i]==32 || line[i]==9) && line[i]!='\x0';i++);

        if(line[i]==10){
                return -1;
        }else{
                return i;
        }
}
int reading(FILE *file,struct inst_mem*im,struct data_memory *dm){
        char line[100];
        char temp[100];
        int l_num=0;
        int text=0;
        int i=0;
        int j=0;
        int k=0;

        while(!feof(file)){
             //   printf("%s\n","+++++++");
                l_num++;
                fgets(line,99,file);
                i=start(line);
                if(i==-1 || line[i]=='#'){      /*comment line so skip*/
                        continue;
                }
                if(line[i]=='.'){
                       // printf("%s\n","{}{{}");
                        i++;
                        for(j=0;(line[i]!=9 && line[i]!=10 && line[i]!=32 && line[i]!='\x0' && line[i]!='\n');j++,i++){
                                temp[j]=line[i];
                        }
                        temp[j]='\x0';
                      //  printf("%s\n",temp);
                        if(!strcmp(temp,"text")){
                             //   printf("%s\n","Herry");
                                text=0;
                        }else if(!strcmp(temp,"data")){
                                text=1;
                        }else{
                                printf("Synatx error at %d\n", l_num);
                                exit(1);
                        }
                        continue;
                }
                if(text==0){
                        for(j=0;(line[i]!='#'&& line[i]!='\x0' && line[i]!='\n');j++,i++){
                                temp[j]=line[i];
                        }
                        temp[j]='\x0';
                       // printf("%s\n",temp);
                        int coded[5];
                        encode(temp,coded, dm,k);
                        if(coded[0]){
                              //  printf("%s\n","YES");
                                load_instruct_mem(im,k,coded);
                                k++;
                        }
                }else{

                }
        }
        return k;
}