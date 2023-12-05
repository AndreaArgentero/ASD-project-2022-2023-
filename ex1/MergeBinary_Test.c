#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "MergeBinary.h"

static int compare_int(const void* COMP1, const void* COMP2){
  if(COMP1 == NULL){
    fprintf(stderr,"compare_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(COMP2 == NULL){
    fprintf(stderr,"compare_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  long int C1 = (long int)COMP1;
  long int C2 = (long int)COMP2;
  if(C1 <= C2){
    return(1);
  }
  return(0);
}

void ARRAY_ADD(void ** ARRAY, void * ELEM, int I){
    ARRAY[I] = ELEM;
}

static void** TEST;
static void** ARRAYEXP;
static int I0, I1, I2;
void setUp(void){
  TEST = malloc(10*sizeof(int*));
  ARRAYEXP = malloc(10*sizeof(int*));
  I0 = 1;
  I1 = 10;
  I2 = 22;
}

void tearDown(void){
  free(TEST);
  free(ARRAYEXP);
}

static void test_merge_add(void){
  merge_sort(TEST,0,0,1,0,compare_int);
  TEST_ASSERT_EQUAL(sizeof(ARRAYEXP)/sizeof(ARRAYEXP[0]), sizeof(TEST)/sizeof(TEST[0]));
}

static void test_binary_add(void){
  binary_insertion_sort(TEST,0,compare_int);
  TEST_ASSERT_EQUAL(sizeof(ARRAYEXP)/sizeof(ARRAYEXP[0]), sizeof(TEST)/sizeof(TEST[0]));
}

static void test_mergebinary_add(void){
  merge_binary_insertion_sort(TEST,0,1,compare_int);
  TEST_ASSERT_EQUAL(sizeof(ARRAYEXP)/sizeof(ARRAYEXP[0]), sizeof(TEST)/sizeof(TEST[0]));
}

static void test_merge_elem(void){
  ARRAY_ADD(TEST, &I0, 0);

  merge_sort(TEST,0,0,1,1,compare_int);
  TEST_ASSERT_EQUAL_PTR(&I0,TEST[0]);
}

static void test_binary_elem(void){
  ARRAY_ADD(TEST, &I0, 0);

  binary_insertion_sort(TEST,0,compare_int);
  TEST_ASSERT_EQUAL_PTR(&I0,TEST[0]);
}

static void test_mergebinary_elem(void){
  ARRAY_ADD(TEST, &I0, 0);

  merge_binary_insertion_sort(TEST,1,1,compare_int);
  TEST_ASSERT_EQUAL_PTR(&I0,TEST[0]);
}

static void test_merge_two_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);

  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 0);

  merge_sort(TEST,0,1,1,2,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,2);
}

static void test_binary_two_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);

  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 0);

  binary_insertion_sort(TEST,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,2);
}

static void test_mergebinary_two_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);

  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 0);

  merge_binary_insertion_sort(TEST,2,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,2);
}

static void test_merge_three_cres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 0);
  ARRAY_ADD(TEST, &I1, 1);

  merge_sort(TEST,0,2,1,3,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_binary_three_cres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);


  ARRAY_ADD(TEST, &I0, 0);
  ARRAY_ADD(TEST, &I1, 1);
  ARRAY_ADD(TEST, &I2, 2);
  
  binary_insertion_sort(TEST,2,compare_int);

  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_mergebinary_cres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 0);
  ARRAY_ADD(TEST, &I1, 1);
  ARRAY_ADD(TEST, &I2, 2);

  merge_binary_insertion_sort(TEST,3,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_merge_three_decres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 1);
  ARRAY_ADD(TEST, &I2, 0);

  merge_sort(TEST,0,2,1,3,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_binary_three_decres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 1);
  ARRAY_ADD(TEST, &I2, 0);

  binary_insertion_sort(TEST,2,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_mergebinary_decres_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 1);
  ARRAY_ADD(TEST, &I2, 0);

  merge_binary_insertion_sort(TEST,3,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_merge_three_random_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I2, 1);

  merge_sort(TEST,0,2,1,3,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_binary_three_random_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I2, 1);

  binary_insertion_sort(TEST,2,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);

}

static void test_mergebinary_random_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I2, 2);

  ARRAY_ADD(TEST, &I0, 2);
  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I2, 1);

  merge_binary_insertion_sort(TEST,3,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_merge_three_with_two_equal_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I1, 2);

  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 2);

  merge_sort(TEST,0,2,1,3,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_binary_three_with_two_equal_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I1, 2);

  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 2);

  binary_insertion_sort(TEST,2,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

static void test_mergebinary_three_with_two_equal_elem(void){
  ARRAY_ADD(ARRAYEXP, &I0, 0);
  ARRAY_ADD(ARRAYEXP, &I1, 1);
  ARRAY_ADD(ARRAYEXP, &I1, 2);

  ARRAY_ADD(TEST, &I1, 0);
  ARRAY_ADD(TEST, &I0, 1);
  ARRAY_ADD(TEST, &I1, 2);

  merge_binary_insertion_sort(TEST,3,1,compare_int);
  TEST_ASSERT_EQUAL_PTR_ARRAY(ARRAYEXP,TEST,3);
}

int main(void){

  UNITY_BEGIN();

  printf("Tests su inserimento di elementi: \n");
  printf("- Merge: "); 
  RUN_TEST(test_merge_add);
  printf("- Binary: "); 
  RUN_TEST(test_binary_add);
  printf("- Merge Binary: "); 
  RUN_TEST(test_mergebinary_add);

  printf("Tests su array con un elemento: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_elem);

  printf("Tests su array con 2 elementi: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_two_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_two_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_two_elem);

  printf("Tests su array con 3 elementi in ordine crescente: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_three_cres_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_three_cres_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_cres_elem);

  printf("Tests su array con 3 elementi in ordine decrescente: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_three_decres_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_three_decres_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_decres_elem); 

  printf("Tests su array con 3 elementi in ordine casuale: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_three_random_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_three_random_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_random_elem);

  printf("Tests su array con 3 elementi, di cui 2 uguali: \n");
  printf("- Merge: ");
  RUN_TEST(test_merge_three_with_two_equal_elem);
  printf("- Binary: ");
  RUN_TEST(test_binary_three_with_two_equal_elem);
  printf("- Merge Binary: ");
  RUN_TEST(test_mergebinary_three_with_two_equal_elem);

  return UNITY_END();
}