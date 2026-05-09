#include <stdio.h>

#define LETTERS 26

int main(void)
{
    int count[LETTERS] = {0};
    int max_count = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            int idx = c - 'a';

            ++count[idx];
            if (count[idx] > max_count) {
                max_count = count[idx];
            }
        }
    }

    /*
     * Draw from the highest level down. Each letter occupies one column,
     * and blanks are real space characters.
     */
    for (int level = max_count; level >= 1; --level) {
        for (int i = 0; i < LETTERS; ++i) {
            putchar(count[i] >= level ? '*' : ' ');
        }
        putchar('\n');
    }

    for (int i = 0; i < LETTERS; ++i) {
        putchar((char)('a' + i));
    }
    putchar('\n');

    return 0;
}
