#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("\nQ1......\n");
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] != '-')
            printf("%s ", argv[i]);
    }
    printf("\nQ2..........\nType Something in the terminal: ");
    char ch;
    int count = 1; //To include "\n" since EOF is considered as "\n"
    while ((ch = getchar()) != '\n') {

        if (!((65 <= ch && ch <= 90) || (97 <= ch && ch <= 122))) {
            count++;
        }
    }
    printf("The number of non alphabetic characters are: %d", count);

    printf("\nQ3..........\nType Something in the terminal: ");
    while ((ch = getchar()) != '\n') {

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
