#include "stdio.h"
#include "signal.h"
#include "stdlib.h"

void sigtermHandler() {
    fprintf(stderr, "convert.o has been terminated");
    exit(1);
}

void sigpipeHandler() {
    fprintf(stderr, "convert.o has been terminated");
    exit(1);
}

int main(int argc, char *argv[]) {
    signal(SIGTERM, sigtermHandler);
    signal(SIGPIPE, sigpipeHandler);

    if (argc == 1) {
        printf("Overlay is not there");
        char ch;
        int count = 0;
        while ((ch = getchar()) != EOF) {

            if (!((65 <= ch && ch <= 90) || (97 <= ch && ch <= 122))) {
                count++;
                printf("%c", ch);
            }
        }
        printf("The number of non alphabetic characters are: %d\n", count);

    } else if (argc == 2) {
        // This means that there is an overlay
        printf("Overlay is there");
        char ch;
        int count = 0;
        int overlay = atoi(argv[1] + 1);
        if (overlay == 0) {
            fprintf(stderr, "Incorrect overlay");
            exit(1);
        }
        printf("Value of overlay is: %d", overlay);

        while ((ch = getchar()) != EOF) {
            if(--overlay==0){
                break;
            }

            if (!((65 <= ch && ch <= 90) || (97 <= ch && ch <= 122))) {
                count++;
                printf("%c", ch);
            }
        }
        printf("The number of non alphabetic characters are: %d\n", count);


    } else {

    }


    return 0;
}