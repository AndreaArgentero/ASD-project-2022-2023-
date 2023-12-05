#include "Skiplist.h"
#define BUF_SIZE 1024

//The record_string method allows you to compare two records
int record_string(void* RECORD1,void* RECORD2){

  if(RECORD1 == NULL){
    fprintf(stderr,"precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(RECORD2 == NULL){
    fprintf(stderr,"precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }

  return strcmp(((char *)RECORD1), ((char *)RECORD2));
}

//Time structure definition
typedef struct timespec Time;
static Time start_t(){
  Time BEGIN;
  clock_gettime(CLOCK_REALTIME, &BEGIN);

  return BEGIN;
}

//stop_t is the method that generates the running time
static double stop_t(Time BEGIN){
  Time END;
  clock_gettime(CLOCK_REALTIME, &END);

  long SECONDS = END.tv_sec - BEGIN.tv_sec;
  long NANOSECONDS = END.tv_nsec - BEGIN.tv_nsec;
  double ELAPSED = (double) SECONDS + (double) NANOSECONDS*1e-9;

  return ELAPSED;
}

int main(int ARGC, char const *ARGV[]){
    Time START;
    double TIME_TOT;
    int MAX_HEIGHT = atoi(ARGV[3]);
    TIME_TOT = 0;

    START = start_t(START);

    SkipList * DICTIONARY=create_list(record_string, MAX_HEIGHT);

    DICTIONARY=load_dictionary((const char *)ARGV[1],DICTIONARY, MAX_HEIGHT);

    load_to_correct((const char *)ARGV[2], DICTIONARY);
    TIME_TOT += (stop_t(START));

    printf("FINITO IN TOT: %0.3f SEC\n", TIME_TOT);
    remove_list(DICTIONARY);
}