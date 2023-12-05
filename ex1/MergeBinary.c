#include <stdio.h>
#include <stdlib.h>
#include "MergeBinary.h"

//swap exchange two values with each other
void swap(void ** A, int FIRST, int SECOND){
	void * TEMP;
	TEMP = A[FIRST];
	A[FIRST] = A[SECOND];
	A[SECOND] = TEMP;
}

//binary_call based on mean value calls binary_serach on a given sub array
int binary_call(void * X, void ** ARRAY, int START, int END, int MEDIUM, int (*COMPARE)(const void *, const void*)){
    switch (MEDIUM)
        {
        case 0:
            switch (COMPARE(ARRAY[MEDIUM],X))
            {
            case 1:
                return binary_search(X, ARRAY, MEDIUM+1, END, COMPARE);
                break;

            default:
                return MEDIUM;
                break;
            }
            break;
        default:
            switch (COMPARE(ARRAY[MEDIUM],X))
            {
            case 1:
                return binary_search(X, ARRAY, MEDIUM+1, END, COMPARE);
                break;
            default:
                if(START>(MEDIUM-1)){
                    return MEDIUM;
                }
                else{
                return binary_search(X, ARRAY, START, MEDIUM-1, COMPARE);
                }
                break;
            }
            break;
        }
}

//binary_search returns the position where the element to be sorted should be inserted
int binary_search(void * X, void ** ARRAY, int START, int END, int (*COMPARE)(const void *, const void*)){
	int MEDIUM;
	if(START==END){
		switch (COMPARE(ARRAY[START], X))
		{
		case 1:
			return START+1;
			break;
		default:
			return START;
			break;
		}
	}
	else if(START<END){
		MEDIUM=(START+END)/2;
		if(COMPARE(ARRAY[MEDIUM],X)==0){
			return MEDIUM;
		}

		return binary_call(X, ARRAY, START,END, MEDIUM, COMPARE);
	}
	else{
		return -1;
	}
}

//binary_insertion_sort_ric applies the binary insertion sort algorithm recursively
void binary_insertion_sort_ric(void ** ARRAY, int END, int (*COMPARE)(const void *, const void*)){
	int BINARY, START=0, END2;
	switch (END){
	case 0:
		printf("Vettore vuoto.\n");
		break;
	default:
		for(int i=1; i<=END; i++){
			END2=i-1;
			BINARY=binary_search(ARRAY[i], ARRAY, START, END2, COMPARE);
			switch (BINARY){
			case -1:
				printf("errore\n");
				break;
			
			default:
				for(int j=i; j>BINARY; j--){
					swap(ARRAY, (j-1), j);
				}
				break;
			}
		}
		break;
	}
}

//binary_insertion_sort is the wrapper method of binary_insertion_sort_ric
void binary_insertion_sort(void ** ARRAY, int END, int (*compare)(const void *, const void*)){
	binary_insertion_sort_ric(ARRAY, END, compare);
}

//merge joins two arrays by choosing between two different sorts
void merge(void ** A, int START, int M, int END, int W, int SIZE, int O_SIZE, int (*COMPARE)(const void *, const void*)) {
    int I = START;
    int J = M+1;
    int K = 0;
    void ** B = (void**)malloc(O_SIZE*sizeof(void*));

        while(I<=M && J<=END){
            if(COMPARE(A[I],A[J])){
                B[K] = A[I];
                I++;
            }
            else{
                B[K] = A[J];
                J++;
            }
            K++; 
        }

        if (I <= M) {
            for (int X = I; X <= M; X++, K++) {
                B[K] = A[X];
            }
        }
        else {
            for (int Y = J; Y <= END; Y++, K++) {
                B[K] = A[Y];
            }
        }

        for (int Z = 0; Z < K; Z++) {
            A[START + Z] = B[Z];
        }

        free(B);
}

//merge_sort applies the merge sort algorithm recursively
void merge_sort(void ** A, int START, int END, int K, int SIZE, int (*COMPARE)(const void *, const void*)){

    if(START < END){            
        int MID = (START+END)/2; //2
        if(END <= K){
            binary_insertion_sort(A, END, COMPARE);
        } else {
            merge_sort(A, START, MID, K, MID-START+1, COMPARE);
            merge_sort(A, MID+1, END, K, END-MID+1, COMPARE);
            merge(A, START, MID, END, K, END-MID+1, SIZE, COMPARE);
        }
    }
    
        
}

//merge_binary_insertion_sort is the wrapper method of merge_sort
void merge_binary_insertion_sort(void ** BASE, size_t NITEMS, size_t K, int (*COMPARE)(const void *, const void*)){
    merge_sort(BASE, 0, NITEMS-1, K, NITEMS, COMPARE);
}