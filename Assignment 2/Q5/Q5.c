#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>
#include "fcntl.h"
#include "stdio.h"
#include "setjmp.h"

#define BUFFER_SIZE 1024

jmp_buf env;

void killChildren(int pid) {
    kill(pid, SIGINT);
}

void handler() {
    fprintf(stderr, "Handler is running\n");
    longjmp(env, 1);
}


int main(int argc, char *argv[]) {

    bool overlay = false;
    bool readFile = false;
    bool writeFile = false;

    int overlayIndex = -1;
    int readFileIndex = -1;
    int writeFileIndex = -1;

    argc -= 1; // This is to remove the filename of the executable passed

    if (argc == 3) {
        //Only one condition
        overlay = true;
        readFile = true;
        writeFile = true;

        overlayIndex = 1;
        readFileIndex = 2;
        writeFileIndex = 3;

    } else if (argc == 2) {
        //Two Conditions
        if (argv[1][0] != '-') {
            readFile = true;
            readFileIndex = 1;

            writeFile = true;
            writeFileIndex = 2;
        } else {
            overlay = true;
            overlayIndex = 1;

            readFile = true;
            readFileIndex = 2;
        }


    } else if (argc == 1) {
        //Two conditions

        if (argv[1][0] != '-') {
            readFile = true;
            readFileIndex = 1;
        } else {
            overlay = true;
            overlayIndex = 1;
        }
    } else {
        // No conditions
        //Nothing to write
    }

    printf("Overlay Status: %d || Overlay Index: %d\n", overlay, overlayIndex);

    printf("ReadFile Status: %d ||ReadFile Index: %d \n", readFile, readFileIndex);

    printf("WriteFile Status: %d || WriteFile Index: %d\n", writeFile, writeFileIndex);

    int readfd = 0;
    if (readFile) {
        readfd = open(argv[readFileIndex], O_RDONLY, 0644);
    }

    int writefd = 0;

    if (writeFile) {
        writefd = creat(argv[writeFileIndex], 0644);
    }

    if (readfd != -1 && writefd != -1) {
        char buff[BUFFER_SIZE];
        int readSize = read(readfd, buff, BUFFER_SIZE);
        printf("The file's read size is %d\n", readSize);


        int p1[2], p2[2];
        if (pipe(p1) < 0) {
            fprintf(stderr, "Pipe had some errors\n");
            exit(1);
        }
        if (pipe(p2) < 0) {
            fprintf(stderr, "Pipe had some errors\n");
            exit(1);
        }
        write(p1[1], buff, BUFFER_SIZE); // Writing the buffer into the write end
        write(p2[1], buff, BUFFER_SIZE); // Writing the buffer into the write end

        int oldstdin = dup(0);
        int oldstdout = dup(1);
        signal(SIGALRM, handler);

        alarm(3);
        int pid1 = fork();
        int pid2 = fork();


        if (pid1 > 0 && pid2 > 0) {
            //This is the parent process
            int status[2], killed = 0, statusIndex = 0;
            if (setjmp(env) != 0) {
                // This means that the setjmp is not working properly
                //printf("SetJMP")
                killChildren(pid1);
                killChildren(pid2);

                killed = 1;

            }
            int pid, _status;
            //Status 2 means it errored out. Status 0 means normal
            while ((pid = wait(&_status)) > 0) {
                // Wait = -1 means there is no more child process to exit
                status[statusIndex++]=_status;
                if (pid == pid1 && _status == 2) {
                    //This means that the count had some problem. So we must kill change.o also
                    killChildren(pid2);
                    killed = 1;
                }

            }

            if (killed == 0) {
                //If the process was killed, then the pipe not have been written to at all
                int readSize1 = read(p1[0], buff, BUFFER_SIZE);
                write(writefd, buff, readSize1);
                int readSize2 = read(p2[0], buff, BUFFER_SIZE);
                write(writefd, buff, readSize2);
            }


            close(p1[0]);
            close(p2[0]); //Closing the read ends of the pipe since it won't be  used anymore
            close(readfd);
            close(writefd);
            printf("The statuses of the proccessess are %d and %d\n", status[0], status[1]);
            printf("The main parent process has terminated\n");

        } else if (pid1 == 0 && pid2 > 0) {
            //This is the first child
            dup2(p1[0], 0); // stdin as the read file
            dup2(p1[1], 1);// writing to the pipe

            if (overlay) {
                execl("count.o", argv[overlayIndex], (char *) NULL);
            } else {
                execl("count.o", (char *) NULL);
            }

            wait(NULL); // Wait for the grandchild process to end
            close(p1[1]); //Closing the write end of the pipe since it won't be used anymore
            //Closing the assigned stdin and stdout
            printf("First Child Terminated\n");


        } else if (pid1 > 0 && pid2 == 0) {
            //This is the second child
            dup2(p2[0], 0); // stdin as the read file
            dup2(p2[1], 1);// writing to the pipe


            execl("change.o", (char *) NULL);
            close(p2[1]); //Closing the write end of the pipe since it won't be used anymore
            printf("Second Child Terminated\n");
        } else {
            //This is the grandchild;
            printf("GrandChild Terminated\n");
        }


    } else {
        fprintf(stderr, "File could not be opened\n");
    }

    alarm(0);
    return 0;
}