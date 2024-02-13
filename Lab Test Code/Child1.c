#include "stdio.h"
#include "stdlib.h"

int main(){
    while(1){
        char ch = getchar();
        if (ch==EOF){

            putchar(ch);
            exit(0);

        }
        else{
            putchar(ch);

        }

    }

}