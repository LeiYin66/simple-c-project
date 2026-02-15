#ifndef DAOSTR_H
#define DAOSTR_H

#include <stdio.h>
#include "input.h"
#include "myalloc.h"

typedef struct
{
    int len;
    char str[0];
} daostr;

daostr *getdaostr(bytebuf *);

void wrtdaostr(daostr *ds, FILE *fp);

daostr *rdaostr(FILE *fp);

#endif
