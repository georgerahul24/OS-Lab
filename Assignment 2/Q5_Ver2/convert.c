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


int main() {

    signal(SIGTERM, sigtermHandler);
    signal(SIGPIPE, sigpipeHandler);
    char ch;

    while ((ch = getchar()) != EOF) {

        if ((65 <= ch && ch <= 90)) {
            putchar(ch + ('a' - 'A'));
        } else if (97 <= ch && ch <= 122) {
            putchar(ch - ('a' - 'A'));
        } else {
            putchar(ch);
        }

    }
    return 0;
}