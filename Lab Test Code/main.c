#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fcntl.h"
#include "signal.h"
#define READ_END 0
#define WRITE_END 1
int main()
{
    int pid1;  // For Child 1
    int pid2;  // For child 2
    int p1[2]; // Between Children
    int p2[2]; // Between Child and Parent

    //Storing old stdins and stdouts
    int oldstdin = dup(STDIN_FILENO);
    int oldstdout = dup(STDOUT_FILENO);

    //Initialised Pipes
    if (pipe(p1) == -1)
    {
        perror("Pipe Error");
        exit(1);
    }
    if (pipe(p2) == -1)
    {
        perror("Pipe Error");
        exit(1);
    }

    if ((pid1 = fork()) != 0)
    {
        if ((pid2=fork()) != 0)
        {
            close(p1[READ_END]);
            close(p1[WRITE_END]);
            close(p2[WRITE_END]);



            dup2(p2[READ_END],STDIN_FILENO);
            while (1)
            {
                char ch = getchar();
                if (ch == EOF)
                {
                    printf("\nEOF Recieved in parent. Children Terminated");
                    kill(pid1,SIGTERM);
                    kill(pid2,SIGTERM);
                    break;
                }
                else
                {

                    if (48 <= ch && ch <= 57)
                    {
                        if (ch == 48)
                        {
                            putchar(57); //Converting 0 to 9
                        }
                        else
                        {
                            putchar(ch - 1);
                        }
                    }
                }
            }
            wait(NULL);
            wait(NULL);



        }
        else
        {
            //This is for Child 1 that reads from stdin and outputs to stdout
            close(p1[READ_END]);
            close(p2[READ_END]);
            close(p2[WRITE_END]);
            dup2(p1[WRITE_END], STDOUT_FILENO);
            execl("Child1.o", "Child1", (char *)NULL);
            exit(0);
        }
    }
    else
    {
        //This is for Child 2 that reads from the Child 1

        close(p1[WRITE_END]);
        close(p2[READ_END]);
        dup2(p1[READ_END], STDIN_FILENO);
        dup2(p2[WRITE_END], STDOUT_FILENO);
        execl("Child2.o", "Child2", (char *)NULL);
        exit(0);
    }

    return 0;
}