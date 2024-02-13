#include "pthread.h"
#include "stdio.h"


void *factorial(void * ans) {

    pthread_detach(pthread_self());
    long int  * tans = ans;
    long int  res=1;
    for (int i = 2; i <= (*tans) ; i++){
        res *= i;
    }

    *tans = res;
    pthread_exit(NULL);
}


int main() {
    pthread_t pid1,pid2;
    long int f1 = 4;
    long int f2 = 5;

    printf("The sum of %d! and %d! is ",f1,f2);
    pthread_create(&pid1, NULL, factorial, &f1);
    pthread_create(&pid2, NULL, factorial, &f2);
    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    printf(" %d\n", f1+f2);
    return 0;
}