#ifndef INPUT_H
#define INPUT_H

#include "myalloc.h"

#ifndef DEFAULT_BUFFER_SIZE
#define DEFAULT_BUFFER_SIZE 64
#endif

typedef struct
{ 
    int capacity;
    int size;
    char *buf;
} bytebuf;

bytebuf *getbuf(void);

int clrbuf(bytebuf *);

int atobuf(bytebuf *);

void delbuf(bytebuf *);
 
#endif