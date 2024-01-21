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
            int readSize = read(readfd, buff, BUFFER_SIZE);
            printf("The file's read size is %d", readSize);


            int p1[2], p2[2];
            if (pipe(p1) < 0) {
                fprintf(stderr, "Pipe had some errors");
                exit(1);
            }
            if (pipe(p2) < 0) {
                fprintf(stderr, "Pipe had some errors");
                exit(1);
            }
            write(p1[1], buff, BUFFER_SIZE); // Writing the buffer into the write end
            write(p2[1], buff, BUFFER_SIZE); // Writing the buffer into the write end

            int oldstdin = dup(0);
            int oldstdout = dup(1);

            int pid1 = fork();
            int pid2 = fork();
            if (pid1 > 0 && pid2 > 0) {
                //This is the parent process

                wait(NULL);
                wait(NULL); // wait for both the children to finish

                int readSize1 = read(p1[0], buff, BUFFER_SIZE);
                write(writefd, buff, readSize1);
                int readSize2 = read(p2[0], buff, BUFFER_SIZE);
                write(writefd, buff, readSize2);


                close(p1[0]);
                close(p2[0]); //Closing the read ends of the pipe since it won't be  used anymore
                close(readfd);
                close(writefd);
                printf("The main parent process has terminated\n");

            } else if (pid1 == 0 && pid2 > 0) {
                //This is the first child
                dup2(p1[0], 0); // stdin as the read file
                dup2(p1[1], 1);// writing to the pipe

                execl("count.o", (char *) NULL);

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
                printf("The process ID of grandchild is %d and %d",pid1,pid2);
                printf("GrandChild Terminated\n");
            }


        } else {
            fprintf(stderr, "File could not be opened");
        }

    }

    return 0;
}