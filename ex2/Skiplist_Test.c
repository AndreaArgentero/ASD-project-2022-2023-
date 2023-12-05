#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "Skiplist.h"
#define MAX_HEIGHT 3

//The compare_int method allows you to compare two int
static int compare_int(void* COMP1, void* COMP2){
  if(COMP1 == NULL){
    fprintf(stderr,"compare_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(COMP2 == NULL){
    fprintf(stderr,"compareint_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  COMP1 = (int*)COMP1;
  COMP2 = (int*)COMP2;
  if(COMP1 <= COMP2){
    return(1);
  }
  return(0);
}

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

static SkipList* TEST;
static Node* TNODE;
int I0, I1, I2;

//setUp is the method that initializes the structures and variables that will be used in the tests
void setUp(void){
  TEST = create_list(compare_int,MAX_HEIGHT);
  I0 = 1;
  I1 = 10;
  I2 = 22;
}

//tearDown is the method that frees up resources at each end of the test
void tearDown(void){
  free(TEST);
}

//test_create_node checks if the creation of the node is successful
static void test_create_node(){
  TNODE = create_node(&I1,MAX_HEIGHT);
  TEST_ASSERT_NOT_NULL(TNODE);
  free(TNODE);
}

//test_create_list checks if the creation of the list is successful
static void test_create_list(){
  TEST_ASSERT_NOT_NULL(TEST);
}

//test_add_elem checks if the insertion of an element in the list is successful
static void test_add_elem(){
  TEST_ASSERT_TRUE(insert_skiplist(TEST,&I0,MAX_HEIGHT));
}

//test_search_successfully the method searches for an element in the list
static void test_search_successfully(){
  insert_skiplist(TEST,&I0,MAX_HEIGHT);
  insert_skiplist(TEST,&I1,MAX_HEIGHT);
  insert_skiplist(TEST,&I2,MAX_HEIGHT);
  TEST_ASSERT_TRUE(search_skiplist(TEST,&I1));
}

//test_search_unsuccessfully the method searches for an element not in the list
static void test_search_unsuccessfully(){
  int I3 = 3;
  insert_skiplist(TEST,&I0,MAX_HEIGHT);
  insert_skiplist(TEST,&I1,MAX_HEIGHT);
  insert_skiplist(TEST,&I2,MAX_HEIGHT);
  TEST_ASSERT_FALSE(search_skiplist(TEST,&I3));
}

int main() {
  UNITY_BEGIN();
  printf("- Test creazione nodo: \n");
  RUN_TEST(test_create_node);
  printf("- Test creazione lista: \n");
  RUN_TEST(test_create_list);
  printf("- Test inserimento un elem nell lista: \n");
  RUN_TEST(test_add_elem);
  printf("- Test ricerca di un elemento inserito nella lista: \n");
  RUN_TEST(test_search_successfully);
  printf("- Test ricerca di un elemento non inserito nella lista: \n");
  RUN_TEST(test_search_unsuccessfully);
  return UNITY_END();
}