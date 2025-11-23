#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
struct hashTable
{
    int key;
    int val;
    UT_hash_handle hh;
};