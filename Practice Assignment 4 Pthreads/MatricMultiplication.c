#define m 3
#define k 2
#define n 3

#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

int matrix1[m][k] = {
        {1, 2},
        {3, 4},
        {5, 6}
};

int matrix2[k][n] = {
        {7, 8,9},
        {10, 11,12}

};

int resultantMatrix[m][n];

typedef struct {
    int i, j;
} Args;



void *calculate(void *vargs) {

    Args *args = (Args *) vargs;
    int i = args->i;
    int j = args->j;



    for (int _i = 0; _i < k; _i++) {

        resultantMatrix[i][j] += matrix1[i][_i] * matrix2[_i][j];
    }


}


int main() {
    pthread_t threads[m * n];
    int threadIndex = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            Args *args = malloc(sizeof(Args));
            args->i = i;
            args->j=j;
            pthread_create(&threads[threadIndex++], NULL, calculate, args);
        }
    }

    for (int i = 0; i < threadIndex; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads joined\n");

    printf("The matrix is: \n");
    for(int i = 0;i<m;i++){
        for(int j = 0; j<n;j++){
            printf("%d ",resultantMatrix[i][j]);
        }
        printf("\n");
    }


}