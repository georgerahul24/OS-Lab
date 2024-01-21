
#include "stdio.h"
#include "fcntl.h"

#define BUFFER_SIZE 1024


int main() {
    //0644 means user can read and write other users can only read
    //open()
    printf("Trying open() func\n");
    int fd = open("gr.txt", O_RDONLY | O_CREAT, 0644);
    printf("The file status is: %d\n", fd);

    //creat()
    printf("trying out creat() func\n");
    int fd1 = creat("gr1.txt", 0644);
    printf("The file status is: %d\n", fd1);

    //dup and dup2
    int newfd = dup(fd);
    printf("New fd is %d\n", newfd);

    int newfd1 = dup2(fd1,100);
    printf("New fd is %d\n",newfd1);

    //read and write

    char buff[BUFFER_SIZE];
    int readSize = read(fd,buff,BUFFER_SIZE);
    write(fd1,buff,readSize);



    //close files
    printf("Closing Files\n");
    close(fd);
    close(fd1);


    return 0;


}