#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include<math.h>

typedef struct {
    pthread_mutex_t * lock;
    int * number;
}Args;

bool isPrime(long num){
    bool flag=true;
    for(int i = 2; i <= sqrt(num); i++) {
       if(num % i == 0) {
          flag = false;
          break;
       }
    }
    return flag;
}

void * printPrimes(void * arg) {
  Args * a = (Args *) arg;
  int local;
  while(true)
    {
      //locking shared resource
    pthread_mutex_lock(a -> lock);
    local = * (a -> number);
    * (a -> number) = * (a -> number) + 1;
    pthread_mutex_unlock(a -> lock); //releasing shared resource

    if (local > pow(10,7))
            pthread_exit(NULL);
    if(isPrime(local))
        printf("%d\n", local);
  }
}

int main(int argc, char * argv[]) 
{
    struct timespec start, finish;
    double elapsed;
    int num_thr;
    //Get number of threads from the arguments
    if(argc > 1)
        num_thr = atoi(argv[1]);
    else
        printf("Error in command line arguments!");
    //Record start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    //Initialising threads and shared data resource
    pthread_t threads[num_thr];
    pthread_mutex_t mutex;
    pthread_mutex_init( &mutex, NULL);
    int value = 2, ret, i;
    Args arg_thr = {
        & mutex,
        & value
    }; 
    //Creating threads
  for(i = 0; i < num_thr; ++i) 
  {
    ret = pthread_create( & threads[i], NULL, & printPrimes, (void * ) & arg_thr);
    if (ret) {
      printf("Error creating thread\n");
      exit(-1);
    }
  }

  //Joining threads
  for (i = 0; i < num_thr; ++i) 
    pthread_join(threads[i], NULL);

//Recording final clock time
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution Time: %f", elapsed);

    return 0;
}