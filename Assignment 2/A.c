#include "stdio.h"

int main() {
    printf("\nQ2..........\n");
    char ch;
    int count = 0;
    while ((ch = getchar()) != '\0') {

        if (!((65 <= ch && ch <= 90) || (97 <= ch && ch <= 122))) {
            count++;
            printf("%c", ch);
        }
    }
    printf("The number of non alphabetic characters are: %d\n", count);

    return 0;
}