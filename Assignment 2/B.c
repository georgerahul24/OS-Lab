#include "stdio.h"

int main() {
    char ch;
    printf("\nQ3..........\nOpposite Case: ");

    while ((ch = getchar()) != '\0') {

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