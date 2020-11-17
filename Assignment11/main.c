#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
bool flag = false;
bool is_neg= false;

int binarytodecimal(int exponent);
char* shift(char input[], int shift, int right,int len);
void readfile(FILE *file);
int checking(char input1[], char input2[]);
char* decimaltobinary(int input);
char* addition(char *input1, char *input2);
char* subtraction(char *input1, char *input2);
int Normalization(char *input, int exp, int k);
int cycle=0;

int binarytodecimal(int exponent){
        int dec=0;
        int base=1;
        int temp=exponent;
       // printf("%s\n","binarytodecimal");
      // printf("%s\n", input[0]);
       //int a= atoi(input[0]);
        while(temp>0){
                int last_digit= temp%10;
                temp=temp/10;
                dec= dec + last_digit*base;
                base = base * 2;
        }
        return dec;
}
char* decimaltobinay(int input){
       // char result[9];
        char *result= malloc(9 * sizeof(char));
        for(int i=0;i<8;i++){
                result[i]='0';
        }
        int k=7;
        for(int i=0;input>0;i++){
                char c=  '0'+ input%2;
                input= input/2;
                result[k]=c;
                k--;
        }
        result[8]='\x0';
        return result;
        //printf("%s\n", result);
}

// shift input's length 24 ..clear so
char*  shift(char input[], int shift, int right,int len){
       // printf("%s\n","shift-------------");
        flag= false;
       // printf("%s\n",input);
        //char output[24];
        char *output =malloc(25 * sizeof(char));
        if(right){
                int i;
                for(i=0;(i<shift && i<len);i++){
                        output[i]='0';
                }
                if(i==len){
                        flag= true;
                }
                int k=i;
                while((i-k)<len && i<len){
                        output[i]=input[i-k];
                        i++;
                }
        }else{
                int i;
                int k=23;
                for(i=0;(i<shift && i<len);i++){
                        output[k]='0';
                        k--;
                }
                if(i==len){
                        flag= true;
                }
                int temp=23;
                while(k>=0){
                      output[k]=input[temp];
                      k--;
                      temp--;
                }


        }
        output[24]='\x0';
        for(int i=0;i<25;i++){
              //  printf("%c ", output[i]);
        }
        // printf("%s\n", output);
        // printf("%d\n", flag);
        return output;

}



int main(int argc, char *argv[]){

        FILE *file= fopen(argv[1], "r");

        // char* k="0000000000000000000011111";
        // char* str= shift(k, 21,0,25);

       // printf("%s\n", str);
        // free(str);
       readfile(file);
       
       
       
        
}

void readfile(FILE *file){
      // printf("%s\n","reading file");

       while(!feof(file)){
                char line[70];
                char input1[33];
                char input2[33];
                fgets(line, 69, file);
                int i;
                for(i=0;i<32;i++){
                        input1[i]=line[i];
                }
                input1[32]='\x0';
                int k=i+1;
                for(;k<65;k++){
                        input2[k-33]=line[k];
                }
                input2[32]='\x0';
               // printf("%s %s \n", input1, input2);
                checking(input1, input2);
                cycle=0;
                


       }
}

int checking(char input1[], char input2[]){
        char pos1[2];
        char exp1[9];
        char mant1[25];
        char pos2[2];
        char exp2[9];
        char mant2[25];
        ////===============
        pos1[0]=input1[0];
        pos1[1]='\x0';
        pos2[0]=input2[0];
        pos2[1]='\x0';
        ////===============

        for (int i=0;i<8;i++){
                exp1[i]=input1[i+1];
                exp2[i]=input2[i+1];
        }
        exp1[8]='\x0';
        exp2[9]='\x0';
        int int_exp1= binarytodecimal(atoi(exp1));
        int int_exp2= binarytodecimal(atoi(exp2));
        //===========
        mant1[0]='1';
        mant2[0]='1';
        for(int j=0;j<23;j++){
                mant1[j+1]=input1[j+9];
                mant2[j+1]=input2[j+9];
        }
        mant1[24]='\x0';
        mant2[24]='\x0';
        // printf("%s\n",mant1);
        // printf("%s\n",mant2);
        //==========
        bool neg1=false;
        bool neg2= false;
        if(pos1[0]=='1'){
                neg1=true;
               // printf("%s\n", "neg1");
        }
        if (pos2[0]=='1'){
                neg2=true;
                // printf("%s\n", "neg2");
        }
       // if(strcmp())
        //================
       // printf("%d %d \n", int_exp1, int_exp2);
        if(int_exp1>int_exp2){
                //printf("%s %d\n","-----------------" , int_exp1);
                int temp= (int_exp1-int_exp2);
                char* str=shift(mant2,temp,1,24);

                cycle++; // for shifting the number;==============
                if(neg1 && neg2){
                        is_neg=true;

                        char* str1=addition(mant1,str);
                        cycle++;
                        Normalization(str1, int_exp1, 1);
                }else if(neg1==true && neg2==false){
                        is_neg=true;
                        char* str1= subtraction(mant1, str);
                        cycle++;
                        Normalization(str1, int_exp1, 0);
                }else if(neg1==false && neg2==true){
                        //printf("%s\n",str);
                       // printf("%s %s \n",mant1,str);
                        char* str1=subtraction(mant1, str);
                       // printf("%s\n", str1);
                         cycle++;
                           if(str1[0]=='1'){
                                       
                                        is_neg=true;
                                        str1=subtraction(str,mant1);
                                       // printf("%s\n",str1);
                                        Normalization(str1, int_exp1, 0);
                                }else{
                                         Normalization(str1, int_exp1,0);
                                }
                       // Normalization(str1, int_exp1, 0);
                }else{
                        //printf("%s\n","]]]]]]");
                        //printf("%s %s\n",mant1,str);
                        char* str1=addition(mant1,str);
                         cycle++;
                       // printf("%s\n",str); 
                        Normalization(str1, int_exp1, 1);  
                }
                //printf("%d\n",strlen(str));
                //addition(mant1, str);
                free(str);
        }else{
                
                if(int_exp1==int_exp2){   // what is they are equal
                cycle++;
                       // printf("%s\n", "kpaif");
                        if(neg1 && neg2){
                               // printf("%s\n", "both are negative --");
                                is_neg= true;
                                // printf("%s\n", mant1);
                                // printf("%s\n",mant2);
                                char* str1=addition(mant1, mant2);
                                 cycle++;
                                Normalization(str1, int_exp1, 1);
                                
                        }else if(neg1==true && neg2==false){
                                
                                char* str1=subtraction(mant1, mant2);
                                 cycle++;
                                if(str1[0]=='1'){
                                       
                                        is_neg=true;
                                        str1=subtraction(mant2,mant1);
                                        Normalization(str1, int_exp1, 0);
                                }else{
                                         Normalization(str1, int_exp1,0);
                                }

                        }else if(neg1==false && neg2== true){
                                //printf("%s\n","====");
                                char* str1=subtraction(mant1, mant2);
                                 cycle++;
                                if(str1[0]=='1'){
                                        //printf("%s\n","=========");
                                        is_neg=true;
                                        str1=subtraction(mant2,mant1);
                                        Normalization(str1, int_exp1, 0);
                                }else{
                                         Normalization(str1, int_exp1,0);
                                }
                               
                        }else{
                                //printf("%s\n", "both are positive --");
                                char* str1=addition(mant1,mant2);
                                 cycle++;
                                Normalization(str1, int_exp1,1);
                        }
                        
                        
                }else{
                        
                        int temp= int_exp2-int_exp1;
                        char* str=shift(mant1,temp, 1, 24);
                         cycle++;
                        if(neg1 && neg2){
                                is_neg=true;
                                char* str1=addition(str,mant2);
                                 cycle++;
                                Normalization(str1, int_exp2, 1);
                        }else if(neg1==true && neg2==false){
                                char* str1=subtraction(mant2,str);
                                 cycle++;
                                 Normalization(str1, int_exp2, 0);
                        }else if(neg1==false && neg2==true){
                                is_neg=true;
                                char* str1=subtraction(mant2,str);
                                 cycle++;
                                 Normalization(str1, int_exp2, 0);

                        }else{
                                char* str1=addition(mant2,str);
                                cycle++;
                                // printf("%s\n", mant2);
                                // printf("%s\n", str); 
                               // printf("%s %d\n", "============", cycle);
                                Normalization(str1, int_exp2, 1);  
                        }
                        free(str);
                       // addition(str, mant2);
                }
        }
        
        //==========




}


int Normalization(char *input, int exp, int k){
        //  printf("%s %d \n", "Normalization------------->", cycle);
        //  printf("%s %d %d \n", input, exp, k);
        //char* str= shift(input,1, 1, 25);
        //printf("%s \n",str);
        cycle+=2;
        // if((input[0]=='1' && input[1]=='0') || (input[0]=='1' && input[1]=='1') || (input[0]=='0' && input[1]=='0') ){
        //         cycle+=2;
        // }
        char* result= malloc(24 * sizeof(char));
        int final_exp=exp;
        if(k==1){
                if(input[0]=='1'){
                      
                        if(exp==255){
                                if(strcmp(input,"0000000000000000000000000")==0 || strcmp(input,"1000000000000000000000000")==0){
                                        if(is_neg==true){
                                                 printf("%s\n", "Negative Infinite Number");
                                        }else{
                                                 printf("%s\n", "Infinite Number");
                                        }
                                       
                                }else{
                                        printf("%s\n", "NaN");
                                }
                                is_neg=false;
                                free(input);
                                return 0;
                       }



                        if (exp==254){
                                printf("%s\n", "Overflow");
                                is_neg=false;
                                free(input);
                                return 0;
                        }
                        
                        else{
                                final_exp=final_exp+1;
                                if(input[24]=='0'){
                                       // printf("%s\n", "Normalization------------->");
                                        for(int i=0;i<23;i++){
                                        result[i]=input[i+1];
                                        }
                                        result[23]='\x0';
                                        char* binary_final_exp= decimaltobinay(final_exp);
                                        // printf("%s %s \n", "exponent -->",binary_final_exp );
                                        // printf("%s\n", result);
                                        if(is_neg==true){
                                               // printf("%s\n","0000000000");
                                                printf("%s%s%s %d\n", "1",binary_final_exp,result, cycle);
                                        }else{
                                                printf("%s%s%s %d\n", "0",binary_final_exp,result, cycle);
                                        }
                                        is_neg=false;
                                       // free(binary_final_exp);
                                         // printf("%s\n", "Normalization------------->");
                                }else{
                                       // printf("%s\n","=====");
                                        char* str1= malloc(25 * sizeof(char));
                                        char* str2= malloc(25 * sizeof(char));
                                        for(int i=0;i<24;i++){
                                                str1[i]=input[i];
                                                str2[i]=0+'0';
                                        }
                                        str2[23]=1+'0';
                                        str1[24]='\x0';
                                        str2[24]='\x0';
                                        char* a= addition(str1,str2);
                                        if(a[0]=='0' && a[1]=='1' ){
                                                cycle-=2;
                                        }
                                        Normalization(a,final_exp,1);
                                        free(str1);
                                        free(str2); 
                                }
                                

                        }
                        
                        free(input);

                }else{
                       // printf("%s\n","====-----");
                       if(exp==255){
                                if(strcmp(input,"0000000000000000000000000" )==0 || strcmp(input,"1000000000000000000000000")==0){
                                        if(is_neg==true){
                                                 printf("%s\n", "Negative Infinite Number");
                                        }else{
                                                 printf("%s\n", "Infinite Number");
                                        }
                                }else{
                                        printf("%s\n", "NaN");
                                }
                                is_neg=false;
                                free(input);
                                return 0;
                       }
                       
                        for(int i=0;i<23;i++){
                                result[i]=input[i+2];
                        }
                        result[24]='\x0';
                        char* binary_final_exp= decimaltobinay(final_exp);
                        // printf("%s %s \n", "exponent -->",binary_final_exp );
                        // printf("%s\n", result);
                        if(is_neg==true){
                                printf("%s%s%s %d\n", "1",binary_final_exp,result,cycle);
                        }else{
                                printf("%s%s%s %d\n", "0",binary_final_exp,result,cycle);
                        }
                        free(binary_final_exp);
                        is_neg=false;
                        free(input);


                }
        }else{
                        if(exp==255){
                                if(strcmp(input,"0000000000000000000000000")==0 || strcmp(input,"1000000000000000000000000")==0){
                                        if(is_neg==true){
                                                 printf("%s\n", "Negative Infinite Number");
                                        }else{
                                                 printf("%s\n", "Infinite Number");
                                        }
                                }else{
                                        printf("%s\n", "NaN");
                                }
                                is_neg=false;
                                free(input);
                                return 0;
                       }

                int temp=0;
                if(strcmp(input,"0000000000000000000000000")==0){
                        printf("%s\n", "00000000000000000000000000000000");
                        is_neg=false;
                        free(input);
                        return 0;
                }
                for(int i=0;i<25;i++){
                        if(input[i]=='0'){
                                temp++;
                              //  printf("%d %d \n", temp, i);
                        }else{
                                break;
                        }
                }
                // temp=temp;
                
                char* str=shift(input,temp,0,25);
              //  printf("%s\n",str);
                for(int i=0;i<23;i++){
                        result[i]=str[i+1];
                }
                free(str);
                final_exp= final_exp-temp+1;
               // printf("%d\n",final_exp);
                if(final_exp<0){
                        printf("%s\n","Underflow");
                        is_neg=false;
                        free(input);
                        return 0;
                }
                char* binary_final_exp=decimaltobinay(final_exp);
                if(is_neg==true){
                        printf("%s%s%s %d\n","1",binary_final_exp, result, cycle);
                }else{
                        printf("%s%s%s %d\n","0",binary_final_exp, result, cycle);
                }
                free(binary_final_exp);
                is_neg=false;
                free(input);


        }
       
}




char* addition(char *input1, char *input2){
        // printf("%s\n", "kapil------------------> addition");
        // printf("%s\n", input1);
        // printf("%s\n", input2);
        char *str= malloc(26 * sizeof(char));

        for(int i=0;i<25;i++){
                str[i]='0';
        }
        str[25]='\x0';
        int k=25;
        int j;
        int carry=0;
        for(j=23;j>=0;j--){
               int temp= carry+ (input1[j]-'0')+(input2[j]-'0');
               //printf("%c %c \n",input1[j], input2[j]);
              //printf("%d ",carry);
               if(temp==0){
                       carry=0;
                       str[j+1]=0+'0';
               }else if(temp==2){
                       carry=1;
                       str[j+1]=0+'0';
               }else if(temp==1){
                      // printf("%s\n","l");
                       carry=0;
                       str[j+1]=1+'0';
               }else{
                       carry=1;
                       str[j+1]=1+'0';
               }
               //printf("%s\n", str);
        }
        if(carry==1){
                str[0]=1+'0';
        }

        //printf("%s\n",str);
        subtraction(input1,input2);
        return str;

}

// char* subtraction(char *input1, char *input2){
//         printf("%s\n", "kapil------------------> subtraction");
//         printf("%s\n", input1);
//         printf("%s\n", input2);
//         char *str= malloc(26 * sizeof(char));

//         for(int i=0;i<25;i++){
//                 str[i]='0';
//         }
//         str[25]='\x0';
//         int k=25;
//         int j;
//         int carry=0;
//         for(j=23;j>=0;j--){
//                int temp= carry+ (input1[j]-'0')-(input2[j]-'0');
             
//               // printf("%c %c \n",input1[j], input2[j]);
//                if(temp==0){
//                        if(input1[j]=='0' && input2[j]=='1'){
//                                 carry=-1;
//                                 str[j+1]=0+'0';
//                        }else if(input1[j]=='0' &&  input2[j]=='0') {
//                                 carry=0;
//                                 str[j+1]=0+'0';
//                        }else{
//                                carry=0;
//                                 str[j+1]=0+'0';
//                        }
                      
//                }else if(temp==1){
//                        carry=0;
//                        str[j+1]=1+'0';
//                }else if(temp==-1){
//                        carry=-1;
//                        str[j+1]=0+'0';
//                }else if (temp==-2){
//                        carry=-1;
//                        str[j+1]=1+'0';
//                }else{
//                        carry=1;
//                        str[j+1]=1+'0';
//                }
//                 printf("%d%d ",carry,temp);
//                //printf("%s\n", str);
//         }
//        // printf("\n%d \n", carry);
//         if(carry==-1){
//                 str[0]='1';
//         }
//         //  if(carry==1){
//         //         str[0]=1+'0';
//         // }

//         //         printf("%s\n","-----------------");
//         //   printf("%s\n",str);
//         //   if(str[0]=='1'){
//         //           printf("%c \n ",str[0]);
//         //   }
          
//           return str;
// }

char* subtraction(char* a,char* b){
    int borrow = 0;
//     printf("%s\n", "kapil------------------> subtraction");
//         printf("%s\n", a);
//         printf("%s\n", a);
   // int *temp=new int[length];
    char *temp= malloc(26 * sizeof(char));
       for(int i=0;i<25;i++){
                temp[i]='0';
        }
        temp[25]='\x0';
    int p=25;
    for(int i=23;i>=0;i--){  
            
        int nh = borrow+(a[i]-'0')-(b[i]-'0') ;  
        
        if((borrow+(a[i]-'0')-(b[i]-'0'))==0){           
           
                if(borrow==0){
                    temp[i+1] = '0';
                }else{
                    borrow=1;
                    temp[i+1]='0';
                }
        }else if((borrow+(a[i]-'0')-(b[i]-'0'))==-1){
                borrow=1;
                temp[i+1]='1';
        }else if((borrow+(a[i]-'0')-(b[i]-'0'))==1){
                 if(borrow==1){
                    borrow=1;
                    temp[i+1]='1';
                }else{
                    temp[i+1]='1';
                }
        }else if((borrow+(a[i]-'0')-(b[i]-'0'))==2){
                temp[i+1]='0';
                borrow=0;
        }
       /// printf("%d %s\n", nh, temp); 
       // cout<<temp[i];
    }
    if(borrow!=0){
            temp[0]='1';
    }
   // printf("%s\n",temp);
    return temp;
}




