#include "process.h"

#define RRTIME 2

void RR() {
    int currentTime = 0,completed_process = 0;
    ProcessArray *pa = readProcessesFromFile("/Users/georgerahul/Desktop/OS-Lab/Scheduling Algorithms/processes.txt");

    while (completed_process < pa->numberOfProcesses) {
        int no_active_process = 1; //inorder there is no active process, we need to run the clock
        for (int i = 0; i < pa->numberOfProcesses; i++) {
            Process *cp = pa->processes[i];
            if (cp->arrival <= currentTime && cp->finished == 0) {
                no_active_process=0;
                if(cp->wait==-1){
                    cp->wait=currentTime;
                }
                int time_left = cp->cpu_burst - cp->time_received;
                if (time_left <= RRTIME) {
                    currentTime += time_left;
                    cp->finished = 1;
                    cp->turnaround = currentTime - cp->arrival;
                    cp->time_received += RRTIME;
                    cp->timeCompleted=currentTime;
                    printf("[%d - %d] ", currentTime - time_left, currentTime);
                    completed_process+=1;

                } else {
                    currentTime += RRTIME;
                    cp->time_received += RRTIME;
                    printf("[%d - %d] ", currentTime - RRTIME, currentTime);
                }
                printf("%s running currently\n", cp->name);

            }
        }
        if(no_active_process){
            currentTime+=1;
            printf("[%d] No active process\n",currentTime-1);
        }

    }
    printProcessTable(pa);
}

int main() {
    RR();


    return 0;
}