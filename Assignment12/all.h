
#include <string>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>

// struct block
// {
// 	int key;
//         // int val;
//         // int dirty=0;
//         // int valid;
//         // int periority=0;
//         struct Node* val;
        
// };
struct Node
{
        int key;           // tag and key are same
        int val;
        int dirty=0;
        int valid=0;
        int periority=0; 
        int access=1;
        bool first=true;
        std::vector<int> vect; 
        struct Node* next;
        struct Node* prev;  
       // std::string tag="null";
};







