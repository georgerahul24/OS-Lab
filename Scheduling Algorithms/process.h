#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#pragma once
#define maximum_processes 1000
typedef struct {
    char *name;
    int arrival;
    int cpu_burst;
    int turnaround;
    int wait;
    int time_received;
    int finished;
    int timeCompleted;
    int lastWaitQueueEntryTime;


} Process;

typedef struct {
    Process **processes;
    int numberOfProcesses;
} ProcessArray;

ProcessArray *readProcessesFromFile(char *filename) {
    //Opening the file to read
    FILE *file = fopen(filename, "r");

    //Initialising the Processes Array
    ProcessArray *pa = malloc(sizeof(ProcessArray));
    pa->processes = calloc(maximum_processes, sizeof(Process));
    pa->numberOfProcesses = 0;


    char input[25];

    while (fgets(input, 25, file)) {
        char *processName = malloc(5 * sizeof(char));
        int arrival, cpuBurst;
        sscanf(input, "%s %d %d\n", processName, &arrival, &cpuBurst);
        printf("%s %d %d\n", processName, arrival, cpuBurst);
        Process *p = malloc(sizeof(Process));
        p->name = processName;
        p->arrival = arrival;
        p->cpu_burst = cpuBurst;
        p->wait = 0;
        p->turnaround = -1;
        p->time_received = 0;
        p->finished = 0;
        p->timeCompleted = -1;
        p->lastWaitQueueEntryTime = p->arrival;
        pa->processes[pa->numberOfProcesses++] = p; // Adding the process to the array
    }
    return pa;


};

void printProcessTable(ProcessArray *pa) {
    for (int i = 0; i < pa->numberOfProcesses; i++) {
        printf("Process Name: %s\n", pa->processes[i]->name);
        printf("Arrival: %d || ", pa->processes[i]->arrival);
        printf("CPU Burst: %d || ", pa->processes[i]->cpu_burst);
        printf("Turnaround: %d || ", pa->processes[i]->turnaround);
        printf("Wait: %d || ", pa->processes[i]->wait);
        printf("Time Completed: %d \n", pa->processes[i]->timeCompleted);

    }
}

void printStatistics(ProcessArray *pa) {
    int statistics[2]; // Turnaround time is in index 0 and wait is in 1
    statistics[0]=0;
    statistics[1]=0;
    for (int i = 0; i < pa->numberOfProcesses; i++) {
        statistics[0] += pa->processes[i]->turnaround;
        statistics[1] += pa->processes[i]->wait;
    }

    printf("Avg. Turn around time is %d\nAvg. Wait Time is %d", statistics[0] / pa->numberOfProcesses,
           statistics[1] / pa->numberOfProcesses);
}

/*
int main() {
    ProcessArray *pa = readProcessesFromFile("/Users/georgerahul/Desktop/OS-Lab/Scheduling Algorithms/processes.txt");
    printProcessTable(pa);

    return 0;
}
 */