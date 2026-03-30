#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEN 500
#define MAX 2000
#define SIZE 95

typedef struct secret
{
    char meaning;
    struct secret *next;
} secret;

secret* input(secret **last);
char* process(secret *head, secret *last);
void transform(char being_processed[], char *encrypt);
void print(char output[]);

int main(void)
{
    secret *last = NULL;
    secret *head = input(&last);

    char *encrypt = process(head, last);

    FILE *fp = fopen("in.txt", "r");

    char buffer[MAX];
    size_t n = fread(buffer, 1, MAX - 1, fp);
    buffer[n] = '\0';
    fclose(fp);

    transform(buffer, encrypt);

    print(buffer);

    free(encrypt);

    return 0;

}

secret* input(secret **last)
{
    char ch;
    int flag[SIZE] = {0};
    secret *head = NULL, *tail = NULL, *p;

    while ((ch = getchar()) != '\n')
    {
        if (ch - ' ' >= 0 && ch - '~' <= 0 && flag[ch - ' '] == 0)
        {
            p = (secret *) malloc(sizeof(secret));
            p -> meaning = ch;
            p -> next = NULL;
            if (head == NULL)
            {
                head = p;
                tail = head;
            }
            else
            {
                tail -> next = p;
                tail = tail -> next;
            }
            flag[ch - ' '] += 1;
        }
        else
            continue;
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (flag[i] == 0)
        {
            p = (secret *) malloc (sizeof(secret));
            p -> meaning = ' ' + i;
            p -> next = NULL;
            tail -> next = p;
            tail = tail -> next;
        }
    }

    tail -> next = head;
    *last = tail;

    return head;
}

char* process(secret *head, secret *last)
{
    char *string = (char *) malloc (sizeof(char) * SIZE);
    char first = head -> meaning;

    while (head != head -> next)
    {
        char ch = head -> meaning;
        last -> next = head -> next;
        free(head);
        head = last -> next;
        for (int i = 1; i < ch; i++)
        {
            head = head -> next;
            last = last -> next;
        }
        string[ch - ' '] = head -> meaning;
    }
    string[head -> meaning - ' '] = first;
    free(head);

    return string;
}

void transform(char being_processed[], char *encrypt)
{
    int index = 0;

    while (being_processed[index] != '\0')
    {
        if (being_processed[index] <= '~' && being_processed[index] >= ' ')
            being_processed[index] = encrypt[being_processed[index] - ' '];
        index++;
    }
}

void print(char output[])
{
    FILE *fp = fopen("in_crpyt.txt", "w");

    fputs(output, fp);

    fclose(fp);
}