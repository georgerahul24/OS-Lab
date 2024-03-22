#include "pthread.h"
#include "stdlib.h"
#include "stdio.h"

#define MAXELEMENTS 10

int mainArray[MAXELEMENTS] = {1, 3, 2, 4, 5, 6, 8, 7, 10, 9};

typedef struct {
    int startIndex;
    int endIndex;
    int *resultArray;
} ThreadData;

void *sortArray(void *varg) {
    ThreadData *td = (ThreadData *) varg;
    int *resultantArray = (int *) calloc(MAXELEMENTS / 2, sizeof(int));
    td->resultArray = resultantArray;
    for (int i = td->startIndex; i < td->endIndex; i++) {
        resultantArray[i - td->startIndex] = mainArray[i];
    }
    for (int i = 0; i < MAXELEMENTS / 2; i++) {
        for (int j = 0; j < MAXELEMENTS / 2; j++) {
            if (resultantArray[i] < resultantArray[j]) {
                int temp = resultantArray[j];
                resultantArray[j] = resultantArray[i];
                resultantArray[i] = temp;
            }
        }
    }

}

int main() {
    ThreadData td1, td2;
    pthread_t thread1, thread2;
    td1.startIndex = 0;
    td1.endIndex = MAXELEMENTS / 2;

    td2.startIndex = MAXELEMENTS / 2;
    td2.endIndex = MAXELEMENTS;

    pthread_create(&thread1, NULL, sortArray, &td1);
    pthread_create(&thread2, NULL, sortArray, &td2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("The original array is : [ ");
    for (int i = 0; i < MAXELEMENTS; i++) {
        printf("%d, ", mainArray[i]);
    }
    printf("]\n");

    printf("The resultant array from the first thread is : [ ");
    for (int i = 0; i < MAXELEMENTS / 2; i++) {
        printf("%d, ", td1.resultArray[i]);
    }
    printf("]\n");

    printf("The resultant array from the second thread is : [ ");
    for (int i = 0; i < MAXELEMENTS / 2; i++) {
        printf("%d, ", td2.resultArray[i]);
    }
    printf("]\n");


    int i = 0, j = 0, k = 0;

    while (i < MAXELEMENTS / 2 && j < MAXELEMENTS / 2) {
        if (td1.resultArray[i] < td2.resultArray[j]) {
            mainArray[k++] = td1.resultArray[i++];
        }
        else{
            mainArray[k++] = td2.resultArray[j++];
        }
    }

    while (i<MAXELEMENTS/2){
        mainArray[k++] = td1.resultArray[i++];
    }
    while (j<MAXELEMENTS/2){
        mainArray[k++] = td2.resultArray[j++];
    }


    printf("The sorted array is : [ ");
    for (int i = 0; i < MAXELEMENTS; i++) {
        printf("%d, ", mainArray[i]);
    }
    printf("]\n");

}