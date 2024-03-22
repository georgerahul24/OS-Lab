#include <unistd.h>
#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"

#define ReaderTime 1
#define WriterTime 2
pthread_mutex_t wrt;
pthread_mutex_t mutex;

int readcount = 0;

void *Reader(void *vreaderNumber) {
    int readerNumber = *((int *) vreaderNumber);
    printf("The Reader %d is waiting to read\n", readerNumber);
    fflush(stdout);
    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1) {
            pthread_mutex_lock(&wrt);
            printf("Access given to readers\n");
            fflush(stdout);
        }

        pthread_mutex_unlock(&mutex);
        /*Simulating reading being performed*/
        printf("The Reader %d is reading\n", readerNumber);
        fflush(stdout);

        sleep(ReaderTime);

        pthread_mutex_lock(&mutex);
        readcount--;
        printf("The Reader %d has finished reading\n", readerNumber);
        fflush(stdout);

        if (readcount == 0) {
            pthread_mutex_unlock(&wrt);
            printf("Access given to writers\n");
            fflush(stdout);
        }
        pthread_mutex_unlock(&mutex);
    }

}

void *Writer(void *vwriterNumber) {
    int writerNumber = *((int *) vwriterNumber);
    while (1) {
        printf("Writer %d is waiting for 'wrt' Mutex\n", writerNumber);
        fflush(stdout);
        pthread_mutex_lock(&wrt); //Waiting for the readers to exit
        printf("Writer %d has entered the critical section\n", writerNumber);
        fflush(stdout);
        /*Simulating writing being performed*/
        sleep(WriterTime);

        pthread_mutex_unlock(&wrt); // Unlocking the mutex for the readers
        printf("Writer %d has exited the critical section\n", writerNumber);
        fflush(stdout);
    }
}


int main() {


    pthread_t threads[4];
    int t1 = 1, t2 = 2, t3 = 3, t4 = 4;

    pthread_mutex_init(&wrt, NULL);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&threads[0], NULL, Writer, (void *) &t1);
    pthread_create(&threads[1], NULL, Writer, (void *) &t2);
    pthread_create(&threads[2], NULL, Reader, (void *) &t3);
    pthread_create(&threads[3], NULL, Reader, (void *) &t4);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

}