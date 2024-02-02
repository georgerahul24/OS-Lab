#include "process.h"


int main() {
    int currentTime = 0, completed_process = 0;
    ProcessArray *pa = readProcessesFromFile("processes.txt");
    printProcessTable(pa);

}