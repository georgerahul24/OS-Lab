#include "stdio.h"

int main() {
    printf("\nQ2..........\n");
    char ch;
    int count = 1; //To include "\n" since EOF is considered as "\n" in terminal
    while ((ch = getchar()) != EOF) {

        if (!((65 <= ch && ch <= 90) || (97 <= ch && ch <= 122))) {
            count++;
            printf("%c", ch);
        }
    }
    printf("The number of non alphabetic characters are: %d\n", count);

    return 0;
}