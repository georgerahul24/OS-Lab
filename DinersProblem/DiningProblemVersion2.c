
/*
 * According to the textbook, this code should not have deadlock.
 * This is because the left chopstick is taken by odd numbered first
 * And the right is taken by the even numbered first.
 * But, it might have starvation in this.
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS 5
#define EATING_TIME 1
#define THINKING_TIME 1
#define LEFT 0
#define RIGHT 1

pthread_mutex_t mutexArray[NUMBER_OF_PHILOSOPHERS]; // One mutex for one chopstick

void *diningProblemThread(void *vindex) {
    int index = *((int *) vindex);
    printf("Philospher[%d] is alive\n", index);
    fflush(stdout);

    while (1) {
        printf("Philosopher[%d] is Thinking.....\n", index);
        fflush(stdout);
        sleep(THINKING_TIME);


        printf("Philosopher[%d] is Hungry.....\n", index);
        while (1) { //This is to do this till we can eat

            if (index % 2 == 0) {
                //Even numbered will take the left one first
                pthread_mutex_lock(&mutexArray[index]);
                pthread_mutex_lock(&mutexArray[(index + 1) % NUMBER_OF_PHILOSOPHERS]);
            } else {
                //odd numbered will take the right one first
                pthread_mutex_lock(&mutexArray[(index + 1) % NUMBER_OF_PHILOSOPHERS]);
                pthread_mutex_lock(&mutexArray[index]);

            }

            //Wait till the chopstick mutexes  are free



            //This means we have both the chopsticks. So, we can eat
            printf("Philosopher[%d] is Eating.....\n", index);
            fflush(stdout);
            sleep(EATING_TIME);

            pthread_mutex_unlock(&mutexArray[index]);
            pthread_mutex_unlock(&mutexArray[(index + 1) % NUMBER_OF_PHILOSOPHERS]);
            break;//Break out of the eating loop

        }

    }


    pthread_exit(NULL);
}


int main() {
    pthread_t pidArray[NUMBER_OF_PHILOSOPHERS]; //used to store the processes

    //Initialising the mutexes
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_mutex_init(&mutexArray[i], NULL);
    }


    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        int *index = malloc(sizeof(int));
        *index = i;
        pthread_create(&pidArray[i], NULL, diningProblemThread, index);

    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_join(pidArray[i], NULL); // Wait for all processes to exit
    }

    return 0;
}