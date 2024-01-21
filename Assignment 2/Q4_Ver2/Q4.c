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
            //dup the stdin and stdout
            int oldstdin = dup(0);
            int oldstdout = dup(1);
            dup2(readfd, STDIN_FILENO);
            dup2(writefd, STDOUT_FILENO);


            int p[2];
            if (pipe(p) < 0) {
                fprintf(stderr, "Pipe had some errors");
                exit(1);
            }


            if (fork() != 0) {
                //This is for the parent

                if (fork() != 0) {
                    //This is for the parent
                    close(p[1]);// This is to close the write end to indicate the EOF
                    wait(NULL);
                    wait(NULL);
                    exit(0);
                } else {
                    // This is for the convert
                    dup2(p[1], STDOUT_FILENO); // Convert should write to pipe
                    dup2(readfd,STDIN_FILENO); // Convert should read from file
                    execl("convert.o", (char *) NULL);
                    perror("Error when running convert.o ");
                    exit(1);
                }


            } else {
                // This is for the count
                //The program that reads from pipe must be called first


                close(p[1]);// This is to close the write end to indicate the EOF

                dup2(p[0], STDIN_FILENO); //Count should read from  pipe 0
                dup2(writefd,STDOUT_FILENO); //Count should write to write file

                execl("count.o", (char *) NULL);
                perror("Error when running count.o");
                exit(1);


            }
        }
    }
    return 0;

}