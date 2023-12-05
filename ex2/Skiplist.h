#ifndef SKIPLIST_H_HAHAHAHAHAHAHA
#define SKIPLIST_H_HAHAHAHAHAHAHA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node Node;           //node structure
typedef struct SkipList SkipList;    //list structure

/*The record_string method allows you to compare two records*/
int record_string(void *RECORD1, void *RECORD2); 

/*create_node is a method that creates the skiplist node*/
Node *create_node(void* ELEMENT, int SIZE);

/*create_list is the method that creates the Skiplist*/
SkipList *create_list(int (*COMPARE)(void*, void*), int MAX_HEIGHT);

/*remove_list deallocates the section of memory reserved for the skiplist*/
void remove_list(SkipList *LIST);

/*print_node prints a given node to the screen*/
void print_node(Node *NODE);

/*print_list prints the skiplist to the screen*/
void print_list(SkipList *LIST);

/*random_level randomly chooses the number of pointers*/
int random_level(int MAX_HEIGHT);

/*insert_skiplist inserts an item into the skiplist*/
int insert_skiplist(SkipList *LIST, void *ELEMENT, int MAX_HEIGHT);

/*load_dictionary is the method that loads the dictionary into a skiplist*/
SkipList *load_dictionary(const char *FILE_NAME, SkipList *LIST, int MAX_HEIGHT);

/*search_skiplist searches for an input item within the skiplist*/
int search_skiplist(SkipList *LIST, void* ELEMENT);

/*is_dot splits into tokens also splitting the string based on punctuation*/
void is_dot(SkipList *DICTIONARY, void * TOKEN);

/*load_to_correct takes as input a file to correct and compares it with the items in the skiplist*/
void load_to_correct(const char *FILE_NAME, SkipList *DICTIONARY);


#endif