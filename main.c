#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXPAT 20

int power(int i) {
    int prod = 1;
    while (i != 0) {
        prod *= 3;
        i--;
    }
    return prod;
}

long Hash(unsigned char pattern[MAXPAT], int length) {
    long h = 0;
    for (int i = 0; i < length; i++)
        h += (pattern[i] % 3) * (power(i));
    return h;
}

int search(char *string, char pattern[MAXPAT]) {
    unsigned char substring[MAXPAT];

    FILE *f1;
    f1 = fopen(string, "r");
    fgets(substring, strlen(pattern), f1);

    int length = strlen(pattern) - 1;
    int mainHash = Hash(pattern, length);

    unsigned char letter;

    int P = power(length - 1);

    int subHash = Hash(substring, length);

    for (int i = 0; feof(f1) == 0; ++i) {
        if (mainHash == subHash) {
            int n = 0;

            for (int j = 0; j < length; j++) {

                if (pattern[j] == (substring[(i + j) % length])) {
                    n++;
                } else {
                    break;
                }

                if (n == strlen(pattern - 2))
                    printf("%d\n", i + 1);
            }
        }
        letter = fgetc(f1);
        subHash = (subHash - (substring[i % length] % 3)) / 3 + ((letter % 3) * P);
        substring[i % length] = letter;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    search(argv[1], argv[2]);

}
