#include "semaphore.h"
#include "pthread.h"
#include "stdio.h"

#define MAX_NUMBER_OF_ITEMS 10

sem_t full, empty;
pthread_mutex_t mutex;


int buffer[MAX_NUMBER_OF_ITEMS];
int in = 0, out = 0;
int itemnumber = 0;

void *Producer(void *vProducerNumber) {
    int producerNumber = *((int *) vProducerNumber);

    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = itemnumber++;
        in = (in + 1) % MAX_NUMBER_OF_ITEMS;
        printf("Item number %d has been produced by producer %d\n", itemnumber, producerNumber);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }


}

void *Consumer(void *vConsumerNumber) {
    int consumerNumber = *((int *) vConsumerNumber);

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int itemNumber = buffer[out];
        out = (out + 1) % MAX_NUMBER_OF_ITEMS;
        printf("Item number %d has been consumed by %d\n", itemNumber, consumerNumber);
        fflush(stdout);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }


}


int main() {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX_NUMBER_OF_ITEMS);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[4];
    int t1 = 1, t2 = 2, t3 = 3, t4 = 4;
    pthread_create(&threads[0], NULL, Producer, (void *) &t1);
    pthread_create(&threads[1], NULL, Producer, (void *) &t2);
    pthread_create(&threads[2], NULL, Consumer, (void *) &t3);
    pthread_create(&threads[3], NULL, Consumer, (void *) &t4);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);


}