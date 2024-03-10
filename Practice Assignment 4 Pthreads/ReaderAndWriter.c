#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"

#define ReaderTime 1
#define WriterTime 2
pthread_mutex_t wrt;
pthread_mutex_t mutex;

int readcount = 0;
int writecount = 0;

void Reader() {






}

void Writer(void *vwriterNumber) {
    int writerNumber = (int) vwriterNumber;
    printf("Writer %d is waiting for 'wrt' Mutex ", writerNumber);
    fflush(stdout);
    pthread_mutex_lock(&wrt); //Waiting for the readers to exit
    printf("Writer %d has entered the critical section", writerNumber);
    fflush(stdout);
    pthread_mutex_unlock(&wrt); // Unlocking the mutex for the readers
    printf("Writer %d has exited the critical section", writerNumber);
    fflush(stdout);
}


int main() {

}