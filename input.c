#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "input.h"

bytebuf *getbuf(void)
{
    bytebuf *bbuf = (bytebuf *)mymalloc(sizeof(bytebuf));
    memset(bbuf, 0, sizeof(*bbuf));
    return bbuf;
}

int atobuf(bytebuf *bbuf)
{
    if (bbuf == NULL)
        return false;

    int ch;
    void *tp;
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (bbuf->size >= bbuf->capacity - 1)
        {
            if (bbuf->capacity == 0)
                bbuf->capacity = DEFAULT_BUFFER_SIZE;
            else
                bbuf->capacity *= 2;
            bbuf->buf = (char*) myrealloc(bbuf->buf, bbuf->capacity);
        }
        bbuf->buf[bbuf->size++] = ch;
    }
    if (bbuf->size != 0)
    {
        bbuf->buf[bbuf->size] = 0;
        return true;
    }

    if (feof(stdin))
    {
        fprintf(stderr, "EOF\n");
        fflush(stderr);
        exit(0);
    }

    return false;
}

int clrbuf(bytebuf *bbuf)
{
    if (bbuf == NULL)
        return false;

    void *tp;

    bbuf->capacity = DEFAULT_BUFFER_SIZE;
    bbuf->size = 0;
    bbuf->buf = (char*) myrealloc(bbuf->buf, bbuf->capacity);

    return true;
}

void delbuf(bytebuf *bbuf)
{
    if (bbuf == NULL)
        return;
    free(bbuf->buf);
    free(bbuf);
}