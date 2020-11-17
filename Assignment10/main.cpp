#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <fstream>
#include <vector>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#include "all.h"
int label_num;

int main(int argc, char *argv[]){
        init_reg_file();
         label_num=0;
         ifstream file(argv[2]);
        string str;
        while (getline(file, str)) {
        vector <string> tokens;
        stringstream check1(str); 
        string intermediate;
        while(getline(check1, intermediate, ' ')) 
        { 
                tokens.push_back(intermediate); 
        }
        string name=tokens[0];
        string val=tokens[1];
        stringstream geek(val);
        int x = 0; 
        geek >> x; 
        char *num=new char[2];
        num[0]=name[1];
        num[1]=name[2];
        int reg_n=reg_num(num);
        register_file[reg_n].val=x;
        }

        FILE *f;
        f=fopen(argv[1],"r");
       // int a=reg_num("a0");
    
        struct inst_mem *im=(inst_mem *)calloc(sizeof(struct inst_mem),1);
	struct data_memory *dm=(data_memory *)calloc(sizeof(struct data_memory),1);
        int len=reading(f, im,dm);
        fclose(f);
        execute(im, len, dm);
        return 0;
}