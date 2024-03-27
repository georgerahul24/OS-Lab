#include <stdio.h>
#include <malloc/_malloc.h>

typedef struct {
    int numberOfProcesses;
    int numberOfDistinctResources;

    int *availableResources;
    int numberOfCompletedProcesses;
    int numberOfTerminatedProcesses;
    int *terminatedProcesses;
    int *completedProcesses;
    int **allocatedResources;
    int **requiredResources;

} Info;

Info *readFile(char *filename) {
    FILE *input_file = fopen(filename, "r");
    char input_buffer[255];

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    Info *info = malloc(sizeof(Info));


    int numberOfDistinctResources;
    fscanf(input_file, "%d ", &numberOfDistinctResources);
    info->numberOfDistinctResources = numberOfDistinctResources;
    printf("%d\n", numberOfDistinctResources);

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->availableResources = malloc(sizeof(int) * info->numberOfDistinctResources);
    for (int i = 0; i < info->numberOfDistinctResources; i++) {
        int temp;
        fscanf(input_file, "%d ", &temp);
        info->availableResources[i] = temp;
        printf("%d ", temp);
    }
    printf("\n");

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    int numberOfProcesses;
    fscanf(input_file, "%d ", &numberOfProcesses);
    info->numberOfProcesses = numberOfProcesses;
    info->numberOfTerminatedProcesses = 0;
    info->terminatedProcesses = malloc(sizeof(int) * numberOfProcesses);
    info->numberOfCompletedProcesses = 0;
    info->completedProcesses = malloc(sizeof(int) * numberOfProcesses);
    printf("%d\n", numberOfProcesses);

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->allocatedResources = malloc(sizeof(int *) * numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->allocatedResources[i] = malloc(sizeof(int) * numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            int temp;
            fscanf(input_file, "%d ", &temp);
            info->allocatedResources[i][j] = temp;
            printf("%d ", temp);
        }
        printf("\n");
    }

    fscanf(input_file, "%[^\n]", input_buffer);
    printf("%s\n", input_buffer);

    info->requiredResources = malloc(sizeof(int *) * numberOfProcesses);

    for (int i = 0; i < info->numberOfProcesses; i++) {
        info->requiredResources[i] = malloc(sizeof(int) * numberOfDistinctResources);
        for (int j = 0; j < info->numberOfDistinctResources; j++) {
            int temp;
            fscanf(input_file, "%d ", &temp);
            info->requiredResources[i][j] = temp;
            printf("%d ", temp);
        }
        printf("\n");
    }


    return info;

}

void destroy(Info *info) {
    free(info->allocatedResources);
    free(info->requiredResources);

    free(info->completedProcesses);
    free(info->terminatedProcesses);
}

int finishedProcessIndex(Info *info, int processIndex) {
    for (int i = 0; i < info->numberOfCompletedProcesses; i++) {
        if (processIndex == info->completedProcesses[i]) {
            return 1;
        }
    }

    for (int i = 0; i < info->numberOfTerminatedProcesses; i++) {
        if (processIndex == info->terminatedProcesses[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Info *info = readFile("/Users/georgerahul/Desktop/OS-Lab/Assignment 4/input.txt");
    int prevNumberOfFinishedProcesses = 0;
    int deadlockMode = 0;
    while (1) {
        if (info->numberOfCompletedProcesses + info->numberOfTerminatedProcesses == info->numberOfProcesses) break;


        for (int processIndex = 0; processIndex < info->numberOfProcesses; processIndex++) {

            if (finishedProcessIndex(info, processIndex)) continue;


            int satisfies = 1;
            for (int resourceNumber = 0; resourceNumber < info->numberOfDistinctResources; resourceNumber++) {
                if (info->availableResources[resourceNumber] < info->requiredResources[processIndex][resourceNumber]) {
                    satisfies = 0;
                    break;
                }
            }
            if (satisfies) {
                printf("Process Number %d will get executed\n", processIndex);
                info->completedProcesses[info->numberOfCompletedProcesses++] = processIndex;
                for (int resourceNumber = 0; resourceNumber < info->numberOfDistinctResources; resourceNumber++) {
                    info->availableResources[resourceNumber] += info->allocatedResources[processIndex][resourceNumber];
                }
            } else if (deadlockMode) {
                deadlockMode = 0;
                printf("Process Number %d terminated\n", processIndex);
                info->terminatedProcesses[info->numberOfTerminatedProcesses++] = processIndex;
                for (int resourceNumber = 0; resourceNumber < info->numberOfDistinctResources; resourceNumber++) {
                    info->availableResources[resourceNumber] += info->allocatedResources[processIndex][resourceNumber];
                }


            }


        }
        if (prevNumberOfFinishedProcesses == info->numberOfTerminatedProcesses + info->numberOfCompletedProcesses) {
            printf("DeadLock Detected\n");
            deadlockMode = 1;
        }
        prevNumberOfFinishedProcesses = info->numberOfTerminatedProcesses + info->numberOfCompletedProcesses;
    }

    destroy(info);


}