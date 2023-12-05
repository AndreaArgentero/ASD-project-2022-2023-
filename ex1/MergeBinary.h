#ifndef MERGE_BINARY_H_HAHAHAHAHAHAHAHAH
#define MERGE_BINARY_H_HAHAHAHAHAHAHAHAH

#define INITIAL_CAPACITY 2
#define BUF_SIZE 1024

//binary_call based on mean value calls binary_serach on a given sub array
int binary_call(void * X, void ** ARRAY, int START, int END, int MEDIUM, int (*COMPARE)(const void *, const void*));

//binary_search returns the position where the element to be sorted should be inserted
int binary_search(void * X, void ** ARRAY, int START, int END, int (*COMPARE)(const void *, const void*));

//binary_insertion_sort_ric applies the binary insertion sort algorithm recursively
void binary_insertion_sort_ric(void ** ARRAY, int END, int (*COMPARE)(const void *, const void*));

//binary_insertion_sort is the wrapper method of binary_insertion_sort_ric
void binary_insertion_sort(void ** ARRAY, int END, int (*COMPARE)(const void *, const void*));

//merge joins two arrays by choosing between two different sorts
void merge(void ** A, int START, int M, int END, int W, int SIZE, int O_SIZE, int (*COMPARE)(const void *, const void*));

//merge_sort applies the merge sort algorithm recursively
void merge_sort(void ** A, int START, int END, int K, int SIZE, int (*COMPARE)(const void *, const void*));

//merge_binary_insertion_sort is the wrapper method of merge_sort
void merge_binary_insertion_sort(void ** BASE, size_t NITEMS, size_t K, int (*COMPARE)(const void *, const void*));

#endif