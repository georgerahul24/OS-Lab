#include "process.h"


void FCFS(char * filename) {
    int currentTime = 0, current_process_number = 0;
    ProcessArray *process_table = readProcessesFromFile(filename);

    while (current_process_number < process_table->numberOfProcesses) {
        Process *current_process = process_table->processes[current_process_number];
        if (currentTime > current_process->arrival) {
            //This means that the process has already arrived
            current_process->wait = currentTime - current_process->arrival;
            current_process->turnaround = current_process->wait + current_process->cpu_burst;


        } else {
            // This means that we have to increase the current time to match the next arrival time.
            //This is because process arrive in order
            currentTime=current_process->arrival;
            current_process->wait = 0;
            current_process->turnaround = current_process->cpu_burst;
        }
        current_process_number++;
        currentTime += current_process->cpu_burst;
        current_process->timeCompleted=currentTime;
    }
    printProcessTable(process_table);
    printStatistics(process_table);


}
