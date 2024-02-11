#include "process.h"


void RR(char * filename,int time_quantum) {
    int RRTIME = time_quantum;
    int currentTime = 0, completed_process = 0;
    ProcessArray *pa = readProcessesFromFile(filename);

    while (completed_process < pa->numberOfProcesses) {
        int no_active_process = 1; //inorder there is no active process, we need to run the clock
        for (int i = 0; i < pa->numberOfProcesses; i++) {
            Process *cp = pa->processes[i];
            if (cp->arrival <= currentTime && cp->finished == 0) {
                no_active_process = 0;

                int time_left = cp->cpu_burst - cp->time_received;
                if (time_left <= RRTIME) {
                    cp->wait += (currentTime - cp->lastWaitQueueEntryTime);
                    currentTime += time_left;
                    cp->finished = 1;
                    cp->turnaround = currentTime - cp->arrival;
                    cp->time_received += RRTIME;
                    cp->timeCompleted = currentTime;
                    printf("[%d - %d] ", currentTime - time_left, currentTime);
                    completed_process += 1;
                    cp->lastWaitQueueEntryTime = currentTime;

                } else {
                    cp->wait += (currentTime - cp->lastWaitQueueEntryTime);
                    currentTime += RRTIME;
                    cp->time_received += RRTIME;
                    printf("[%d - %d] ", currentTime - RRTIME, currentTime);
                    cp->lastWaitQueueEntryTime = currentTime;
                }
                printf("%s running currently\n", cp->name);

            }
        }
        if (no_active_process) {
            currentTime += 1;
            printf("[%d] No active process\n", currentTime - 1);
        }

    }
    printProcessTable(pa);
    printStatistics(pa);
}

