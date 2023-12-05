#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MergeBinary.h"

typedef struct record
{
    int ID_FIELD;
    char * STRING_FIELD;
    int INT_FIELD;
    double DOUBLE_FIELD;
} Records;

typedef struct timespec Time;
static Time start_t(){
  Time BEGIN;
  clock_gettime(CLOCK_REALTIME, &BEGIN);

  return BEGIN;
}

static double stop_t(Time BEGIN){
  Time END;
  clock_gettime(CLOCK_REALTIME, &END);

  long SECONDS = END.tv_sec - BEGIN.tv_sec;
  long NANOSECONDS = END.tv_nsec - BEGIN.tv_nsec;
  double ELAPSED = (double) SECONDS + (double) NANOSECONDS*1e-9;

  return ELAPSED;
}

static int compare_int(const void * RECORD1, const void * RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;
  if(REC1->INT_FIELD <= REC2->INT_FIELD){
    return(1);
  }
  return(0);
}

static int compare_string(const void * RECORD1, const void * RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;

  return strcmp(REC1->STRING_FIELD,REC2->STRING_FIELD) < 0;
}

static int compare_double(const void * RECORD1, const void * RECORD2){
  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  Records *REC1 = (Records*)RECORD1;
  Records *REC2 = (Records*)RECORD2;
  if(REC1->DOUBLE_FIELD <= REC2->DOUBLE_FIELD){
    return(1);
  }
  return(0);
}

static void array_free(void ** ARRAY, int ELEM) {
  for(unsigned long I=0; I<ELEM; I++){
    Records *ARRAY_ELEMENT = (Records *)ARRAY[I];
    free(ARRAY_ELEMENT->STRING_FIELD);
    free(ARRAY_ELEMENT);
  }
  free(ARRAY);
}

static void array_print(void ** ARRAY, FILE * outfile, int ELEM){
    Records *ARRAY_ELEMENT;
    
    for(unsigned long I=0;I<ELEM;I++){
        ARRAY_ELEMENT = (Records *)ARRAY[I];
        fprintf(outfile,"%d,%s,%d,%f\n",ARRAY_ELEMENT->ID_FIELD,ARRAY_ELEMENT->STRING_FIELD,ARRAY_ELEMENT->INT_FIELD, ARRAY_ELEMENT->DOUBLE_FIELD);
    }
    fclose(outfile);
}

Records * memorization_data(Records * RECORD, char * INDEX, char * STRING, char * INTEGER, char * DOUBLE){

    RECORD->ID_FIELD = atoi(INDEX);

    RECORD->STRING_FIELD = malloc((strlen(STRING)+1) * sizeof(char));
    if (RECORD->STRING_FIELD == NULL) {
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(RECORD->STRING_FIELD, STRING);

    RECORD->INT_FIELD = atoi(INTEGER);

    RECORD->DOUBLE_FIELD = atof(DOUBLE);

    return RECORD;
}

void array_add(void ** ARRAY, void * ELEM, int I){
    ARRAY[I] = ELEM;
}

void ** array_load(void ** ARRAY, FILE * INFILE, int * ELEM){

    char BUFFER[BUF_SIZE];
    char * LINE;
    int I = 0, CAPCITY = INITIAL_CAPACITY;

    printf("\nLoading data from file...\n");
    if(INFILE == NULL){
        fprintf(stderr,"main: unable to open the file\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(BUFFER,BUF_SIZE,INFILE) != NULL){
        Records *RECORD = malloc(sizeof(Records));
        if(RECORD == NULL){
            fprintf(stderr,"main: unable to allocate memory for the read record\n");
            exit(EXIT_FAILURE);
        } 

        LINE = (char*)malloc((strlen(BUFFER)+1)*sizeof(char));

        if(LINE == NULL){
            fprintf(stderr,"main: unable to open the file\n");
            exit(EXIT_FAILURE);
        }

        strcpy(LINE, BUFFER);
        char *INDEX_FIELD = strtok(LINE, " ,");
        char *STRING_FIELD = strtok(NULL, " ,");
        char *INTEGER_FIELD = strtok(NULL, " ,");
        char *DOUBLE_FIELD = strtok(NULL, "\n");

        RECORD = memorization_data(RECORD, INDEX_FIELD, STRING_FIELD, INTEGER_FIELD, DOUBLE_FIELD);
        if(I >= CAPCITY){
            ARRAY = (void**)realloc(ARRAY, (CAPCITY*2)*sizeof(void*));
            CAPCITY = CAPCITY*2;
        }

        array_add(ARRAY, (void*)RECORD, I);
        I++;
    }

    *ELEM = I;
    fclose(INFILE);
    return ARRAY;
}

void sort_records(FILE *INFILE, FILE *OUTFILE, size_t K, size_t FIELD){
    Time START;

    int ELEM = 0;
    void ** ARRAY = (void**)malloc(INITIAL_CAPACITY*sizeof(void*));

    START = start_t(START);
    ARRAY = array_load(ARRAY, INFILE, &ELEM);
    printf("\ntime for loading %.3f seconds.\nData uploaded.\n", stop_t(START));

    switch (FIELD)
    {
    case 1:
        START = start_t(START);
        merge_binary_insertion_sort(ARRAY, ELEM, K, compare_string);
        printf("\ntime for sorting %.3f seconds.\nData sorted.\n", stop_t(START));
        break;
    case 2:
        START = start_t(START);
        merge_binary_insertion_sort(ARRAY, ELEM, K, compare_int);
        printf("\ntime for sorting %.3f seconds.\nData sorted.\n", stop_t(START));
        break;
    case 3:
        START = start_t(START);
        merge_binary_insertion_sort(ARRAY, ELEM, K, compare_double);
        printf("\ntime for sorting %.3f seconds.\nData sorted.\n", stop_t(START));
        break;
    }

    START = start_t(START);
    array_print(ARRAY, OUTFILE, ELEM);
    printf("\ntime for printing %.3f seconds.\nData wrinted.\n", stop_t(START));
    array_free(ARRAY, ELEM);
}

int main(int ARGC, char const *ARGV[]){

  FILE * IN = fopen(ARGV[1], "r");
  FILE * OUT = fopen(ARGV[2], "w");
    
  int K_ALGORITM = atoi(ARGV[3]);
  int CRITERIA = atoi(ARGV[4]);

  if(ARGC < 3){
		exit(EXIT_FAILURE);
	}  
    
  if(CRITERIA<1 || CRITERIA>3){
        exit(EXIT_FAILURE);
  }

  sort_records(IN, OUT, K_ALGORITM, CRITERIA);

  return EXIT_SUCCESS;
}