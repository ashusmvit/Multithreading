#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>

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
void primePrint()
{
    long i = 0;
    long limit = pow(10,7);
    while (i<=limit) 
    {
       if(isPrime(i))
           printf("%ld\n",i);
    i = i+1;
    }
}

int main()
{
    //Code running only on a single main thread
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    //calling function to printing primes
    primePrint();
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution Time: %f", elapsed);
    return 0;
}