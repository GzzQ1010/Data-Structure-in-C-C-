#include "chtbl.h"
#include <stdio.h>

// Simple hash function: modulus by number of buckets
int hash(const void *key) {
    return (*(int *)key);
}

// Matching function
int match(const void *key1, const void *key2) {
    return (*(int *)key1 == *(int *)key2);
}

int main() {
    CHTbl table;

    chtbl_init(&table, 5, hash, match, free, 0.5, 2);  // initial size: 5, maxLoadFactor: 0.5, resizeMultiplier: 2

    int i = 0;
    while (1) {
        int *data = (int*) malloc(sizeof(int));
        if (!data) {
            printf("Memory allocation error\n");
            return -1;
        }
        *data = i;

        if (chtbl_insert(&table, data) != 0) {
            free(data);
        }

        printf("Number of buckets in the table: %d\n", table.buckets);
        printf("Number of elements in the table: %d\n", table.size);
        printf("Table's load factor: %f\n", (double)table.size / table.buckets);
        printf("Table's max load factor: %f\n", table.maxLoadFactor);
        printf("Table's resize multiplier: %f\n\n", table.resizeMultiplier);

        if (table.size > 50) {  // arbitrary stopping condition
            break;
        }
        i++;
    }

    chtbl_destroy(&table);
    return 0;
}
