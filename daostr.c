#include <stdlib.h>
#include <string.h>

#include "daostr.h"

daostr *getdaostr(bytebuf *bbuf)
{
    daostr *ds = (daostr *)mymalloc(sizeof(daostr) + bbuf->size + 1);
    ds->len = bbuf->size;
    strcpy(ds->str, bbuf->buf);

    return ds;
}

void wrtdaostr(daostr *ds, FILE *fp)
{
    if (fp)
        fwrite(ds, sizeof(*ds) + ds->len + 1, 1, fp);
}

daostr *rdaostr(FILE *fp)
{
    if (fp)
    {
        size_t size = sizeof(daostr);

        daostr *ds = (daostr *)mymalloc(size);
        fread(&ds->len, sizeof(ds->len), 1, fp);

        ds = myrealloc(ds, size + ds->len + 1);
        fread(ds->str, ds->len + 1, 1, fp);

        return ds;
    }

    return NULL;
}