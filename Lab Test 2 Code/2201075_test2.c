#include <stdlib.h>
#include <wait.h>
#include "unistd.h"
#include "setjmp.h"
#include "stdio.h"


jmp_buf env;

void handler() {
    printf("Handler Called....\n");
    longjmp(env, 1);
}


int main() {

    char x[5], y[5];
    int z;
    printf("Enter the value of X: ");
    scanf("%s", x);
    printf("Enter the value of Y: ");
    scanf("%s", y);
    printf("Enter the value of Z: ");
    scanf("%d", &z);

    printf("\nThe values of X,Y & Z are %s,%s,%d\n", x, y, z);

    signal(SIGALRM, handler);
    alarm(z); // Setting the alarm
    int pid;

    if ((pid = fork()) != 0) {
        //This is the parent
        int setjmpval;
        if ((setjmpval = setjmp(env)) == 1) {
            //longjmp from the handler function
            kill(pid, SIGTERM);
            printf("Calculation is taking too much time.\n");
            exit(0);
        } else if (setjmpval == 2) {
            //This is when longjmp is after the child has been completed
            printf("All the prime numbers are printed\n");
            exit(0);
        }

        wait(NULL);
        alarm(0); // Resetting the alarm
        longjmp(env, 2); //Question had said to longjmp even incase for success so, longjumping


    } else {
        //This is the child

        sleep(2);//To check if the alarm is working


        int _x;
        sscanf(x, "%d", &_x);

        int _y;
        sscanf(y, "%d", &_y);

        printf("Child Process -> X: %d , Y: %d\n", _x, _y);
        fflush(stdout);

        //Logic for prime number calculation
        for (int i = _x; i < _y; i++) {
            int prime = 1;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    prime = 0;
                    break;
                }
            }

            if (prime == 1) {
                printf("%d, ", i);
                fflush(stdout);
            }

        }
        printf("\n");

    }


    return 0;

}
