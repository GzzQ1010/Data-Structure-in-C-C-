/*
 * chtbl.c
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "list.h"
#include "chtbl.h"

int chtbl_init(CHTbl *htbl, 
                int buckets, 
                int (*h)(const void *key), 
                int (*match)(const void *key1, const void *key2), 
                void (*destroy)(void *data), 
                double maxLoadFactor, 
                double resizeMultiplier) {
    if (resizeMultiplier<=1.0) //resizeMultiplier must bigger than 1
        return -1;

    int i;

    /* Allocate space for the hash table. */
    if ((htbl->table = (List *) malloc(buckets * sizeof(List))) == NULL)
        return -1;

    /* Initialize the buckets. */
    htbl->buckets = buckets;

    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Encapsulate the functions. */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    /* Initialize the number of elements in the table. */
    htbl->size = 0;

    /*The maxLoadFactor and resizeMultiplier values should be stored in 
    new fields in the CHTbl struct*/
    htbl->maxLoadFactor=maxLoadFactor;
    htbl->resizeMultiplier=resizeMultiplier;

    return 0;
}

void chtbl_destroy(CHTbl *htbl) {

    int i;

    /* Destroy each bucket. */
    for (i = 0; i < htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    /* Free the storage allocated for the hash table. */
    free(htbl->table);

    /* No operations are allowed now, but clear the structure as a
     * precaution. */
    memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl, const void *data) {

    void *temp;
    int bucket, retval;

    /* Do nothing if the data is already in the table. */
    temp = (void *) data;

    if (chtbl_lookup(htbl, &temp) == 0)
        return 1;
    
    double loadFactor=(double)htbl->size/htbl->buckets;
    //create a new table
    if (loadFactor>htbl->maxLoadFactor){
        int newBuckets=(int)(htbl->buckets*htbl->resizeMultiplier);
        List *newTable= (List*)malloc(newBuckets*sizeof(List));
        if(newTable == NULL)
            return -1;
        for (int i=0;i<newBuckets;i++){
            list_init(&newTable[i],htbl->destroy);
        }

    //Rehashing the existing elements to the new table
    for (int i = 0; i < htbl->buckets; i++) {
            ListElmt *element;
            for (element = list_head(&htbl->table[i]); element != NULL; element = list_next(element)) {
                bucket = (int)(newBuckets * (((sqrt(5) - 1) / 2) * htbl->h(list_data(element)) - (int)(((sqrt(5) - 1) / 2) * htbl->h(list_data(element)))));
                list_ins_next(&newTable[bucket], NULL, list_data(element));
            }
            list_destroy(&htbl->table[i]);
        }

        free(htbl->table);
        htbl->table = newTable;
        htbl->buckets = newBuckets;
    }

    /* Hash the key. */
     bucket = (int)(htbl->buckets * (((sqrt(5) - 1) / 2) * htbl->h(data) - (int)(((sqrt(5) - 1) / 2) * htbl->h(data))));

    /* Insert the data into the bucket. */
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

    return retval;
}

int chtbl_remove(CHTbl *htbl, void **data) {

    ListElmt *element, *prev;
    int bucket;

    /* Hash the key. */
    bucket = htbl->h(*data) % htbl->buckets;

    /* Search for the data in the bucket. */
    prev = NULL;

    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Remove the data from the bucket. */
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            }
            else {
                return -1;
            }
        }

        prev = element;
    }

    /* Return that the data was not found. */

    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {

    ListElmt *element;
    int bucket;

    /* Hash the key. */
    bucket = htbl->h(*data) % htbl->buckets;

    /* Search for the data in the bucket. */
    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Pass back the data from the table. */
            *data = list_data(element);
            return 0;
        }
    }

    /* Return that the data was not found. */

    return -1;
}

