
#include <string.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
#include <map>
#include <iterator>
#include <cmath>
#include <fstream>
#include <algorithm> 
#include "all.h"
using namespace std;
int associativity;
int cache_size;
int block_size;
int lines;
int sets;
int T;
int bitforsets;
int bitforblock;
int bitfortag;
int access=0;
int Total_access=0;
int READ=0;
int WRITE=0;
int READ_MISS=0;
int READ_HIT=0;
int WRITE_MISS=0;
int WRITE_HIT=0;
vector<map<int, struct Node* >> put(int key, int value, int set,int offset,vector<map<int, struct Node* >> &sets);
void add(struct Node* node, int set,vector<map<int, struct Node* >> &responseArray);
void remove1(struct Node* node);
void print(vector<map<int, struct Node* >> responseArray);
void indexing(int associativity, int block_size);






void indexing(int associativity, int block_size){
        


        bitforsets=log2((cache_size/associativity)/block_size);
        bitforblock= log2(block_size);
        bitfortag= (32- bitforsets-bitforblock);
      

}

void add(struct Node* node, int set,vector<map<int, struct Node* >> &responseArray){     // high periority
        struct Node* head= responseArray[set].find(-10)->second;
        struct Node* nodenext= head->next;
        head->next= node;
        node->prev= head;
        node->next= nodenext;
        nodenext->prev= node;
        node->periority=1;

}
 void remove1(vector<map<int, struct Node* >> &responseArray, int set){
         
        struct Node* head= responseArray[set].find(-10)->second;
        int min=INT32_MAX;
        int key=INT32_MAX;
        int min1=INT32_MAX;
        int key1=INT32_MAX;
        // cout << responseArray[set].size() <<endl;
        // struct Node* root=head;
        // while(root!=nullptr){
        //         cout << root->val << endl;
        //         root= root->next;
        // }
        // cout << set << endl;
        // print(responseArray);
        while(head!=nullptr ){
            
                if(head->periority==0 && head->access<min){
                        min= head->access;
                        key= head->key;
                }
                if(head->periority==1 && head->access<min1){
                        min1= head->access;
                        key1= head->key;
                }
             //   cout << "remove  " << min<<endl;
                head=head->next;
        }
        ///  cout << "remove" << endl;
        if(min!=INT32_MAX){
                struct Node* remove= responseArray[set].find(key)->second;
                struct Node* pre= remove->prev;
                pre->next= remove->next;
                remove->next->prev= pre;
                responseArray[set].erase(key);
                return;
        }
        if(min1!=INT32_MAX){
                struct Node* remove= responseArray[set].find(key1)->second;
                struct Node* pre= remove->prev;
                pre->next= remove->next;
                remove->next->prev= pre;
                 responseArray[set].erase(key1);
                return;
        }







        // struct Node* nextnode= node->next;
        // struct Node* prenode= node->prev;
        // prenode->next= nextnode;
        // nextnode->prev= prenode;
}
void add1(struct Node* node, int set, int associativity,vector<map<int, struct Node* >> &responseArray){  // low periority
               
        // struct Node* head= responseArray[set].find(-10)->second;
        // struct Node* head1= responseArray[set].find(-10)->second;
        // int len= responseArray[set].size();
        // int k=0;
        // bool flag= false;
        //  cout<< "add1" << endl;
        struct Node* tail= responseArray[set].find(-11)->second;
          //  cout<< "add1" << endl;
        struct Node* tail_prev= tail->prev;
     
        tail_prev->next=node;
        node->prev= tail_prev;
        node->next= tail;
        tail->prev= node;





        // int t=(associativity/2);
        // while(k<t){
        //         head= head->next;
        //         k++;
        // }
        // cout << "add1 " << flag << " " << associativity << " " << len-2 << endl;
        // if(len-2<(associativity/2)){
        //         head=head1;
        //         struct Node* t1= head->next;
        //         head->next=node;
        //         node->prev=head;
        //         node->next=t1;
        //         t1->prev=node;
        //         node->periority=1;
              
        // }else{
                
        //         node->periority=0;
        //         struct Node* nodenext= head->next;
        //         nodenext->prev= node;
        //         node->next= nodenext;
        //         node->prev= head;
        //         head->next= node;
               
        //         cout << "else --- " << node->periority << " "<< endl;
                
        // }
        /// print();
       // cout << "add1 completed " << node->periority << endl;
}
vector<map<int, struct Node* >> put(int key, int value, int set,int offset,vector<map<int, struct Node* >> &sets){
                struct Node* node= sets[set].find(key)->second;
               // cout << "put" << endl;
              
                if(sets[set].find(key)!=sets[set].end()){
                       // cout << "not null" <<endl;
                        
                        WRITE_HIT++;
                        node->dirty=1;
                        node->vect[offset]=value;
                        node->access=access;
                        if(node->first==false){
                                node->periority=1;
                        }

                }else{
                        
                        if(sets[set].size()==associativity+2){
                              //  cout << "response size is equal to associativity" << endl;
                                struct Node* tail= sets[set].find(-11)->second;
                              //  sets[set].erase(tail->prev->key);
                                remove1(sets, set);

                        }
                        // cout << "====" << endl;
                       // cout << "response size is not equal to associativity" <<endl;
                        WRITE_MISS++;
                        Node* newnode= new Node;
                        //newnode->val=value;
                        vector<int> v(block_size,-1);
                        v[offset]=value;
                        newnode->vect=v;
                        newnode->key=key;
                        newnode->periority=0;
                        newnode->access=access;
                        newnode->first=false;
                        newnode->valid=1;
                      
                        add1(newnode, set, associativity,sets);
                       //   cout<< "----" << endl;
                        sets[set].insert(pair<int, struct Node*>(key, newnode));
                       //   cout<< "----" << endl;
                       

                }
                return sets;


        }
int get(int key, int set,int offset,vector<map<int, struct Node* >> &responseArray){
             //   cout << "get--" << endl;
                int ans=-1;
                
                struct Node* node= responseArray[set].find(key)->second;
                if(node!=nullptr){
                        READ_HIT++;
                        node->access= access;
                        ans= node->vect[offset];
                        if(node->first==false){
                                node->periority=1;
                        }
                        

                }else{
                        READ_MISS++;
                        WRITE_MISS--;
                        put(key, -1, set,offset, responseArray);
                }
                
                return ans;
}

void swap(vector<map<int, struct Node* >> &responseArray){
        int size= responseArray.size();
       for(int i=0;i<size;i++){
                map<int , struct Node*> m= responseArray[i];
                map<int, struct Node*>::iterator itr; 
                for (itr = m.begin(); itr != m.end(); ++itr) { 
                        if(itr->second->periority==1 && (access-itr->second->access)>=T){
                                itr->second->periority=0; 
                                itr->second->first=false;
                        }
                } 

       }
}

void print(vector<map<int, struct Node* >> responseArray){
        //
        int len=responseArray.size();
        for(int i=0;i<len;i++){
                cout << "set-> " <<i << endl;
                struct Node* head= responseArray[i].find(-10)->second;
                head= head->next;
                
                int temp=responseArray[i].size()-2;
                // cout << temp <<endl;
                // cout << block_size << endl;
                while(temp>0){
                        cout <<" key--->" << head->key << " value--->"<<  " periority --->"<<head->periority << " access --->"<< head->access << "    [";
                        for(int i=0;i<block_size;i++){
                                cout << head->vect[i] <<  " ,";
                        }
                        cout << "]" << endl;
                       // cout << "key--->" << head->key << " value--->"<< head->val <<  " periority --->"<<head->periority <<endl;
                        temp--;
                        head= head->next;
                }
                
                
        }
}

void initialisation(vector<map<int, struct Node* >> &set, int s){
       // cout<< "----" << endl;
        set.resize(s);
        int size= set.size();
        for(int i=0;i<size;i++){
                map<int, struct Node*> m;
                Node* head= new Node;
                head->key=-10;
                head->val=-10; 
                
                Node* tail= new Node;
                tail->key=-11;
                tail->val=-11; 
                tail->periority=10;
                head->periority=10;
                head->access= INT32_MAX;
                tail->access=INT32_MAX;
                head->next= tail;
                tail->prev=head;
                m.insert(pair<int, struct Node*>(-11,tail));
                m.insert(pair<int, struct Node*>(-10,head));
                set[i]=m;
        }

         //cout<< "----" << endl;
}

string decToBinary(int n) 
{ 
    // Size of an integer is assumed to be 32 bits
    string arr=""; 
    for (int i = 31; i >= 0; i--) { 
        int k = n >> i; 
        if (k & 1) 
                arr.append("1");
        else
               arr.append("0");
    }
    //cout << arr << endl; 
    //reverse(arr.begin(), arr.end()); 
    //cout<< arr << endl;
    return arr;
}       
int BinaryToDec(int n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}




void execution(string filename){
        string myText;


        ifstream File;
        File.open(filename);
        int i=1;
        // int associativity=0;
        // int cache_size=0;
        // int block_size=0;
        // int T=0;
        
        

        vector<map<int, struct Node* >> set;
        while (getline(File, myText)) {
        
              //  cout << myText<<endl;
             // File >> myText;
                if(i==1){
                        try{
                                cache_size= stoi(myText);
                        }catch(...){
                                cout<< "You must enter whole number for cache size!!" << endl;
                                return ;
                        }
                       
                }else if(i==2){
                        try{
                                block_size= stoi(myText);
                                //cache_size= stoi(myText);
                        }catch(...){
                                cout<< "You must enter whole number for block/line size!!" << endl;
                                return ;
                        } 
                       
                }else if(i==3){
                        try{
                               associativity= stoi(myText);
                        }catch(...){
                                cout<< "You must enter whole number for associativity!!" << endl;
                                return ;
                        }
                        
                }else if(i==4){
                        try{
                                T= stoi(myText);
                        }catch(...){
                                cout<< "You must enter whole number for T!!" << endl;
                                return ;
                        }
                        
                       
                        initialisation(set,(cache_size/associativity)/block_size );
                        
                        // cout << "initialization: " << endl;
                        // cout << set[0].find(-11)->second->prev->key << "-----" << endl;
                        indexing(associativity, block_size);
                        
                        //
                }else{
                        //cout<< myText<< endl;
                        string word = ""; 
                        vector<string> arr(3);
                        int j=0;
                        for (auto x : myText) 
                        { 
                                if (x == ' ') 
                                { 
                                        arr[j] = word;
                                        word = "";
                                        j++; 
                                } 
                                else
                                { 
                                        word = word + x; 
                                } 
                               
                        }  
                        arr[j]=word;
                      
                        // cout << "bit for blocks " << bitforblock << endl;
                        // cout << "bit for set" << bitforsets << endl;
                        // cout << "bit for tag " << bitfortag << endl;
                        
                        int memory_address=0;
                        try{
                                memory_address=stoi(arr[0]);
                        }catch(...){
                                cout<< "= Instruction at "<< access+4 <<" is Invalid Argument !!" << endl;

                                continue;
                        }
                       
                        string temp= decToBinary(memory_address);
                      //  cout << temp << endl;
                        int tag=0;// stoi(temp.substr(0, bitfortag));
                        try{
                               tag= stoi(temp.substr(0, bitfortag));
                        }catch(...){
                                cout<< "= Instruction at "<< access+5 <<" is Invalid Argument !!" << endl;
                                continue;
                        }
                       // cout << tag << endl;
                        int block_index=0; //stoi((temp.substr(32-bitforblock,bitforblock)));
                         try{
                                block_index=stoi((temp.substr(32-bitforblock,bitforblock)));
                        }catch(...){
                                cout<< "= Instruction at "<< access+5 <<" is Invalid Argument !!" << endl;
                                continue;
                        }
                        int set_index=0;
                        if(bitforsets==0){
                                set_index=0; 
                        }else{
                                try{
                                        set_index = stoi(temp.substr(32-bitforblock-bitforsets,bitforsets));
                                }catch(...){
                                        cout<< " Instruction at "<< access+5 <<" is Invalid Argument !!" << endl;
                                        continue;
                                }
                               
                        }
                       
                        
                        //  cout << "set_index "<< set_index << endl;
                        // cout << "block_index " << block_index << endl;
                        tag= BinaryToDec(tag);
                        set_index= BinaryToDec(set_index);
                        block_index= BinaryToDec(block_index);
                        // cout << "=============" << endl;
                        // cout << "memory address  "<<temp << endl;
                        // cout << "tag" << tag << endl;
                        // cout << "set_index "<< set_index << endl;
                        // cout << "block_index " << block_index << endl;
                        // cout << "============" << endl;



                       
                        if(arr[1].compare("R")==0){
                                READ++;
                                access++;
                                Total_access++;
                                get(tag, set_index ,block_index,set);
                               swap(set);
                        }else if(arr[1].compare("W")==0){
                               
                                WRITE++;
                                access++;
                                Total_access++;
                                put(tag, stoi(arr[2]), set_index,block_index,set);
                                
                                swap(set);
                        }else{
                                cout<< " Instruction at "<< access <<" is Invalid Argument !!" << endl;
                                continue;
                        }





                                               
                
                
                }

               



                i++;
        }
        File.close();
        print(set);
        cout<< ""<< endl;
        cout << "------------------------------------------------------------------" << endl;
        cout<< ""<< endl;
        cout<< "cache statistics " << endl;
        cout << "Number of accesses ->" << Total_access << endl;
        cout << "Number of Reads ->" << READ << endl;
        cout << "Number of Read Hits ->" << READ_HIT << endl;
        cout << "Number of Read Misses ->" << READ_MISS << endl;
        cout << "Number of writes ->" << WRITE << endl;
        cout << "Number of writes Hits ->" << WRITE_HIT << endl;
        cout << "Number of writes Misses ->" << WRITE_MISS << endl;
        int totalhit= READ_HIT + WRITE_HIT;
        double hitratio= (double)totalhit/Total_access;
        cout << "Hit Ratio ->" << hitratio << endl;
       
        
       



     

}

int main(int argc, char *argv[]) {
       // std::cout << "Hello World!\n";
        associativity=4;
        block_size=2;

        lines=16;
        cache_size=32;
        sets= 4;
       // vector<int> v=indexing(4,2);
      //  cout<<v[0]<< " "<<v[1]<<endl;
        if(argc<2){
                cout << " To few arguments !! (should be two arguments )  FORMAT:-" << endl;
                cout <<" a.exe/a.out input.txt" << endl;
                return 0;
        }
        if(argc>2){
                cout << " To many arguments !! (should be two arguments )  FORMAT:-" << endl;
                cout <<" a.exe/a.out input.txt" << endl;
                return 0;
        }
       /// cout << stoi("la") << endl;
       for(int i=1;i<argc;i++){

                cout << "executating -> " << argv[i] << endl;
                execution(argv[i]);
                cout<< " " << endl;

       }

//        srand (time(NULL));
// 	int n=50;
// 	cout << "32\n" << "4\n" << "4\n" << "4\n" ;
// 	while(n-->0){
// 		int type = rand()%2;
// 		// int type = 1;
// 		if(type==0){
// 			cout << rand()%100 << " R " << endl;
// 		}
// 		else{
// 			cout << rand()%100 << " W " << rand()%100 << endl;
// 		}
// 	}
     
    return 0;
 }