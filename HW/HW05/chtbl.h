/*
 * chtbl.h
 */
#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

/* Define a structure for chained hash tables. */
typedef struct CHTbl_ {

    int buckets;

    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    int size;
    List *table;
    /* the maximum load factor the hash table should be 
    allowed to reach before being auto-resized*/
    double maxLoadFactor;
    /*the number of buckets should be multiplied when a resize occurs*/
    double resizeMultiplier;

} CHTbl;

/* Public Interface */
//Modified chtbl_init prototype.
int chtbl_init(CHTbl *htbl, 
            int buckets, 
            int (*h)(const void *key), 
            int (*match)(const void *key1, const void *key2), 
            void (*destroy)(void *data), 
            double maxLoadFactor, 
            double resizeMultiplier);

void chtbl_destroy(CHTbl *htbl);

int chtbl_insert(CHTbl *htbl, const void *data);

int chtbl_remove(CHTbl *htbl, void **data);

int chtbl_lookup(const CHTbl *htbl, void **data);

#define chtbl_size(htbl) ((htbl)->size)

#endif
