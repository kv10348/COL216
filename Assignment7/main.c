#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "all.h"

int main(int argc, char *argv[]){
        init_reg_file();
         label_num=0;
   

        FILE *f;
        f=fopen(argv[1],"r");
        int a=reg_num("a0");
    
       struct inst_mem *im=calloc(sizeof(struct inst_mem),1);
	struct data_memory *dm=calloc(sizeof(struct data_memory),1);
        int len=reading(f, im,dm);
        fclose(f);
        execute(im, len, dm);
        return 0;
}