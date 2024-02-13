#include "stdio.h"

int main(){
    while(1){
        char ch = getchar();
        if (ch==EOF){
            putchar(ch);



        }
        else{

            if(48<=ch && ch<=57)
            {if(ch==57){
                    putchar(48); //Converting 10 to zero

                }
                else{
                    putchar(ch+1);
                }}

        }

    }


}