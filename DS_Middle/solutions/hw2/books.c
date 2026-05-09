#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 600
#define MAX_TITLE 64
#define MAX_AUTHOR 32
#define MAX_PRESS 40
#define MAX_DATE 16

typedef struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char press[MAX_PRESS];
    char date[MAX_DATE];
} Book;

static int cmp_book(const void *a, const void *b)
{
    const Book *ba = (const Book *)a;
    const Book *bb = (const Book *)b;

    return strcmp(ba->title, bb->title);
}

static void print_book(FILE *fp, const Book *book)
{
    fprintf(fp, "%-50s%-20s%-30s%-10s\n", book->title, book->author,
            book->press, book->date);
}

int main(void)
{
    Book books[MAX_BOOKS];
    int count = 0;
    FILE *fp = fopen("books.txt", "r");
    int op;

    if (fp != NULL) {
        while (count < MAX_BOOKS &&
               fscanf(fp, "%63s%31s%39s%15s", books[count].title,
                      books[count].author, books[count].press,
                      books[count].date) == 4) {
            ++count;
        }
        fclose(fp);
    }

    qsort(books, count, sizeof(books[0]), cmp_book);

    while (scanf("%d", &op) == 1) {
        if (op == 0) {
            FILE *out = fopen("ordered.txt", "w");

            qsort(books, count, sizeof(books[0]), cmp_book);
            if (out != NULL) {
                for (int i = 0; i < count; ++i) {
                    print_book(out, &books[i]);
                }
                fclose(out);
            }
            break;
        } else if (op == 1) {
            if (count < MAX_BOOKS) {
                scanf("%63s%31s%39s%15s", books[count].title,
                      books[count].author, books[count].press,
                      books[count].date);
                ++count;
                qsort(books, count, sizeof(books[0]), cmp_book);
            }
        } else if (op == 2) {
            char key[MAX_TITLE];

            scanf("%63s", key);
            for (int i = 0; i < count; ++i) {
                if (strstr(books[i].title, key) != NULL) {
                    print_book(stdout, &books[i]);
                }
            }
        } else if (op == 3) {
            char key[MAX_TITLE];
            int write = 0;

            scanf("%63s", key);
            for (int read = 0; read < count; ++read) {
                if (strstr(books[read].title, key) == NULL) {
                    if (write != read) {
                        books[write] = books[read];
                    }
                    ++write;
                }
            }
            count = write;
        }
    }

    return 0;
}
