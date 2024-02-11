#include "process.h"


Process *findMinNonCompleted(ProcessArray *pa, int currentTime) {
    int minBurstTime = INT32_MAX;
    Process *minProcess = NULL;
    for (int i = 0; i < pa->numberOfProcesses; i++) {
        Process *temp = pa->processes[i];
        int remainingBurstTime = temp->cpu_burst - temp->time_received;

        if (remainingBurstTime < minBurstTime && temp->finished == 0 && temp->arrival <= currentTime) {
            minProcess = temp;
            minBurstTime = remainingBurstTime;
        }

    }
    return minProcess;

}


void SRBF(char *filename) {
    int currentTime = 0, completed_process = 0;
    ProcessArray *pa = readProcessesFromFile(filename);
    printProcessTable(pa);

    while (completed_process < pa->numberOfProcesses) {
        Process *p = findMinNonCompleted(pa, currentTime);
        if (p != NULL) {
            p->time_received += 1;
            printf("%s is executing at time %d\n", p->name, currentTime);
            if ((p->cpu_burst - p->time_received) == 0) {
                p->finished = 1;
                p->timeCompleted = currentTime + 1;
                p->turnaround = p->timeCompleted - p->arrival;
                p->wait = p->turnaround - p->cpu_burst;
                completed_process += 1;

            }
        }
        currentTime += 1;
    }
    printProcessTable(pa);
    printStatistics(pa);

}