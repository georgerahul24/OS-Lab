#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "fcntl.h"
#include "stdio.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Invalid Commandline arguments. Received %d number fo arguments. Expected 2\n", argc);
        exit(1);
    } else {
        int readfd = open(argv[1], O_RDONLY, 0644);
        int writefd = creat(argv[2], 0644);

        if (readfd != -1 && writefd != -1) {
            char buff[BUFFER_SIZE];
            read(readfd, buff, BUFFER_SIZE);


            int p1[2], p2[2];
            if (pipe(p1) < 0) {
                fprintf(stderr, "Pipe had some errors");
                exit(1);
            }
            if (pipe(p2) < 0) {
                fprintf(stderr, "Pipe had some errors");
                exit(1);
            }
            write(p1[1], buff, BUFFER_SIZE);
            write(p2[1], buff, BUFFER_SIZE);

            int oldstdin = dup(0);
            int oldstdout = dup(1);
            int pid1 = fork();
            int pid2 = fork();
            if (pid1 > 0 && pid2 > 0) {
                //This is the parent process

                wait(NULL);
                wait(NULL); // wait for both the children to finish

                int n = read(p1[1], buff, BUFFER_SIZE);
                write(writefd, buff, n);
                n = read(p2[1], buff, BUFFER_SIZE);
                write(writefd, buff, n);

                close(readfd);
                close(writefd);
                printf("The main parent process has terminated\n");

            } else if (pid1 == 0 && pid2 > 0) {
                //This is the first child
                close(0); // closing stdin
                dup2(p1[0], 0); // stdin as the read file
                dup2(writefd, 1);// writing to the pipe

                execl("/home/btech/22/george.rahul22b/OS Lab/Assignment 2/count.o", (char *) NULL);

                wait(NULL); // Wait for the grandchild process to end
                dup2(oldstdin, 0); //TODO: Why is this not working
                dup2(oldstdout, 1);
                //Closing the assigned stdin and stdout
                printf("First Child Terminated\n");


            } else if (pid1 > 0 && pid2 == 0) {
                //This is the second child
                dup2(p2[0], 0); // stdin as the read file
                dup2(writefd, 1);// writing to the pipe


                execl("/home/btech/22/george.rahul22b/OS Lab/Assignment 2/change.o", (char *) NULL);

                close(0);
                close(1);
                dup2(oldstdin, 0);
                dup2(oldstdout, 1);
                printf("Second Child Terminated\n");
            } else {
                //This is the grandchild;
                printf("GrandChild Terminated\n");
            }


        } else {
            fprintf(stderr, "File could not be opened");
        }

    }

    return 0;
}