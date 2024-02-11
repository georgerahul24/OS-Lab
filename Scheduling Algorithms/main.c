#include "FCFS.h"
#include "RR.h"
#include "SRBF.h"


int main() {
    char *filename = "processes.txt";

    int choice = -1;
    do {
        printf("\n\n1. FCFS\n");
        printf("2. SRBF\n");
        printf("3. RR\n");
        printf("4. EXIT\n");
        scanf("%d", &choice);
        int tq;
        switch (choice) {
            case 1:
                FCFS(filename);
                break;
            case 2:
                SRBF(filename);
                break;
            case 3:

                printf("Enter the Time Quantum: ");
                scanf("%d", &tq);
                RR(filename, tq);
                break;


        }


    } while (choice != 4);
}