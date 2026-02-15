#ifndef DARRAY_H
#define DARRAY_H

#ifndef ARRAY_ITEM_TYPE
#define ARRAY_ITEM_TYPE int
#endif

#include "myalloc.h"

typedef struct
{
    ARRAY_ITEM_TYPE *items;
    int count;
    int capacity;
} DArray; 

#define da_append(arr, x) do { \
        if (arr.count >= arr.capacity) { \
            if (arr.capacity == 0) arr.capacity = 256; \
            else arr.capacity *= 2; \
            arr.items = (ARRAY_ITEM_TYPE *) myrealloc(arr.items, arr.capacity * sizeof(*arr.items)); \
        } \
        arr.items[arr.count++] = x; \
    } while(0)

#endif

