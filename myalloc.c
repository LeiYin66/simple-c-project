#include "myalloc.h"

void *mymalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "OOM\n");
        fflush(stderr);
        abort();
    }

    return ptr;
}

void *myrealloc(void *ptr, size_t size)
{
    void *nptr = realloc(ptr, size);
    if (nptr == NULL)
    {
        free(ptr);
        fprintf(stderr, "OOM\n");
        fflush(stderr);
        abort();
    }

    return nptr;
}