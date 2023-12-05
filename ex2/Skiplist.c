#include "Skiplist.h"
#define BUF_SIZE 1024
int CASUAL = 1;

//Skiplist structure definition
struct SkipList {
  Node *HEAD;
  unsigned int MAX_LEVEL;
  int (*COMPARE)(void*, void*);
};

//Node structure definition
struct Node {
  struct Node **NEXT;
  unsigned int SIZE;
  void *ITEM;
};

//create_node is a method that creates the skiplist node
Node *create_node(void* ELEMENT, int SIZE){
    Node *NEW_NODE = (Node*)malloc(sizeof(Node));
    NEW_NODE->NEXT=(Node **)malloc(sizeof(Node**)*SIZE);
    void *STRING= (void *)malloc(sizeof(void)*BUF_SIZE);
    strcpy(STRING,ELEMENT);
    if(NEW_NODE!=NULL){
        NEW_NODE->SIZE=SIZE;
        NEW_NODE->ITEM=STRING;
        for(int I=0;I<NEW_NODE->SIZE;I++){
            NEW_NODE->NEXT[I]=NULL;
        }
    }
    else{
        printf("Error: create_node\n");
    }
    return NEW_NODE;
}

//create_list is the method that creates the Skiplist
SkipList *create_list(int (*COMPARE)(void*, void*), int MAX_HEIGHT){
    SkipList *NEW_LIST = (SkipList*)malloc(sizeof(SkipList));
    NEW_LIST->HEAD=(Node *)malloc(sizeof(Node));
    NEW_LIST->HEAD->NEXT=(Node**)malloc(sizeof(Node*)*MAX_HEIGHT);
    if(NEW_LIST!=NULL){
        NEW_LIST->HEAD->SIZE=MAX_HEIGHT;
        for(int I=0;I<NEW_LIST->HEAD->SIZE;I++){
            NEW_LIST->HEAD->NEXT[I]=NEW_LIST->HEAD;
        }
        NEW_LIST->MAX_LEVEL=0;
        NEW_LIST->COMPARE=COMPARE;
    }
    else{
        printf("Error: create_list\n");
    }
    return NEW_LIST;
}

//remove_list deallocates the section of memory reserved for the skiplist
void remove_list(SkipList *LIST){
    Node *X=LIST->HEAD->NEXT[0];
    Node *Y;
    while(X!=LIST->HEAD){
        Y=X->NEXT[0];
        free(X);
        X=Y;
    }
    free(X);
    free(LIST);
}

//print_node prints a given node to the screen
void print_node(Node *NODE){
    printf("|%ls|%d|", (int*)NODE->ITEM, NODE->SIZE);
}

//print_list prints the skiplist to the screen
void print_list(SkipList *LIST){
    Node *NODE = LIST->HEAD->NEXT[0];
    while(NODE!=LIST->HEAD){
        print_node(NODE);
        printf("-->");
        NODE=NODE->NEXT[0];
    }
    printf("NULL\n");
}

//random_level randomly chooses the number of pointers
int random_level(int MAX_HEIGHT){
    int LEVEL = 1;
    float CASUAL = (float)rand()/RAND_MAX;
    while(CASUAL < 0.5 && LEVEL < MAX_HEIGHT){
        LEVEL++;
        CASUAL = (float)rand()/RAND_MAX;
    }
    return LEVEL;
}

//insert_skiplist inserts an item into the skiplist
int insert_skiplist(SkipList *LIST, void *ELEMENT, int MAX_HEIGHT){
    int BOOLE = 0;

    Node *NEW_NODE = create_node(ELEMENT, random_level(MAX_HEIGHT));
    if (NEW_NODE->SIZE > LIST->MAX_LEVEL){
        LIST->MAX_LEVEL = NEW_NODE->SIZE;
    }
    Node *X = LIST->HEAD;
    for(int I = LIST->MAX_LEVEL-1; I>=0; I--){
        if (X->NEXT[I] == LIST->HEAD || LIST->COMPARE(X->NEXT[I]->ITEM, ELEMENT)>0){
            if (I < NEW_NODE->SIZE) {
            	NEW_NODE->NEXT[I] = X->NEXT[I];
            	X->NEXT[I] = NEW_NODE;

                BOOLE = 1;
            }
        }
        else{
            X = X->NEXT[I];
            I++;
        }
    }

    return BOOLE;
}

//load_dictionary is the method that loads the dictionary into a skiplist
SkipList *load_dictionary(const char *FILE_NAME, SkipList *LIST, int MAX_HEIGHT){
    FILE *FILE_PATH;
    char BUFFER[BUF_SIZE];
    char * TOKEN;
    FILE_PATH = fopen(FILE_NAME,"r");
    if(FILE_PATH==NULL){
        printf("Error print\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(BUFFER,BUF_SIZE,FILE_PATH)!=NULL){
        TOKEN=strtok(BUFFER,"\n");
        insert_skiplist(LIST, TOKEN, MAX_HEIGHT);
    }
    fclose(FILE_PATH);
    return LIST;
}

//search_skiplist searches for an input item within the skiplist
int search_skiplist(SkipList *LIST, void* ELEMENT){
    Node *NODE=LIST->HEAD;
    for(int I=(LIST->MAX_LEVEL)-1; I>=0; I--){
        while((NODE->NEXT[I]!=LIST->HEAD)&&(LIST->COMPARE(NODE->NEXT[I]->ITEM, ELEMENT)<0)){
            NODE=NODE->NEXT[I];
        }
    }
    NODE=NODE->NEXT[0];
    if(LIST->COMPARE(NODE->ITEM, ELEMENT)==0){
        return 1;
    }
    else{
        return 0;
    }
}

//is_dot splits into tokens also splitting the string based on punctuation
void is_dot(SkipList *DICTIONARY, void * TOKEN){
    char DOTS[7] = {'.',',',';',':','?','!','\n'};
    void *SUBTOKEN=(void*)calloc(BUF_SIZE,sizeof(void));
    int SHIFT=0, NUMBERLETTERS=0, SHIFTLETTERS=32;
    int FLAGDOT=0, FLAGNOTDOT=0;
    while(*((char*)TOKEN+SHIFT)!='\0'){
        for(int J=0; J<7; J++){
            if(*((char*)TOKEN+SHIFT)==DOTS[J]){
                FLAGDOT=1;
                FLAGNOTDOT=1;
            }
        }
        if(FLAGDOT==1){
            if(NUMBERLETTERS>0 && search_skiplist(DICTIONARY, SUBTOKEN)==0){
                printf("%s\n",(char*)SUBTOKEN);
            }
            FLAGDOT=0;
            SHIFT++;
            NUMBERLETTERS=0;
        }
        else{
            if(*((char*)TOKEN+SHIFT)>='A'&&*((char*)TOKEN+SHIFT)<='Z'){
                *((char*)SUBTOKEN+SHIFT)=*((char*)TOKEN+SHIFT)+SHIFTLETTERS;
            }
            else{
                *((char*)SUBTOKEN+SHIFT)=*((char*)TOKEN+SHIFT);
            }
            SHIFT++;
            NUMBERLETTERS++;
        }
    }
    if(FLAGNOTDOT==0){
        if(search_skiplist(DICTIONARY, SUBTOKEN)==0){
            printf("%s\n",(char*)SUBTOKEN);
        }
    }
    free((char*)SUBTOKEN);
}

//load_to_correct takes as input a file to correct and compares it with the items in the skiplist
void load_to_correct(const char *FILENAME, SkipList *DICTIONARY){
    FILE *FILEPATH;
    char BUFFER[BUF_SIZE];
    void * TOKEN;
    FILEPATH = fopen(FILENAME,"r");
    if(FILEPATH==NULL){
        printf("Error print\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(BUFFER,BUF_SIZE,FILEPATH)!=NULL){
        TOKEN=strtok(BUFFER," ");
        while(TOKEN!=NULL){
            is_dot(DICTIONARY, TOKEN);
            TOKEN=strtok(NULL," ");
        }
    }
    fclose(FILEPATH);
}