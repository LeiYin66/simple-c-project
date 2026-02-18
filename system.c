#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "conio.c"
#include "daostr.h"
#include "myalloc.h"
#include "input.h"

#define BG_FNAME ".stu"

#define MENU_HOME         \
    "a. Add Student\n"    \
    "r. Remove Student\n" \
    "l. List Student\n"   \
    "q. Quit\n"           \
    "Plase input your action:"

#define OUT_FLUSH(_str) \
    printf("%s", _str); \
    fflush(stdout)

#define CLEAR_SCREEN system("clear")

#define PRESS(msg)  \
    printf(msg);    \
    fflush(stdout); \
    getch()

#define INPUT(msg, bbuf) \
    OUT_FLUSH(msg);      \
    clrbuf(bbuf);        \
    atobuf(bbuf)

typedef struct
{
    daostr *name;
    daostr *gender;
    int age;
} Student;

#define ARRAY_ITEM_TYPE Student *
#include "darry.h"

static DArray stus;

void load()
{
    FILE *fp = fopen(BG_FNAME, "rb");
    if (fp)
    {
        // read size
        fread(&stus.count, sizeof(stus.count), 1, fp);
        // read capacity
        fread(&stus.capacity, sizeof(stus.capacity), 1, fp);
        // read stu data

        stus.items = (ARRAY_ITEM_TYPE *)mymalloc(sizeof(*stus.items) * stus.capacity);

        for (int i = 0; i < stus.count; i++)
        {
            ARRAY_ITEM_TYPE item = (ARRAY_ITEM_TYPE)mymalloc(sizeof(**stus.items));
            item->name = rdaostr(fp);
            item->gender = rdaostr(fp);
            fread(&item->age, sizeof(item->age), 1, fp);

            stus.items[i] = item;
        }

        fclose(fp);
    }

}

void save()
{
    /**
     *
     * .stu file format
     * count|capacity|stu1 name|stu1 age|stu1 gender|stu2...
     *   ^
     *   |  ....
     * write
     *
     */

    if (stus.count > 0)
    {
        FILE *fp = fopen(BG_FNAME, "wb");
        fwrite(&stus.count, sizeof(stus.count), 1, fp);
        fwrite(&stus.capacity, sizeof(stus.capacity), 1, fp);
        for (int i = 0; i < stus.count; i++)
        {
            ARRAY_ITEM_TYPE item = stus.items[i];
            wrtdaostr(item->name, fp);
            wrtdaostr(item->gender, fp);
            fwrite(&item->age, sizeof(item->age), 1, fp);

            free(item->name);
            free(item->gender);
            free(item);
        }

        free(stus.items);
        fclose(fp);
    }
}

int main(void)
{
    load();
    bytebuf *bbuf = getbuf();
    while (1)
    {
        CLEAR_SCREEN;

        INPUT(MENU_HOME, bbuf);

        CLEAR_SCREEN;

        if (!strcmp(bbuf->buf, "q"))
            goto end;
        else if (!strcmp(bbuf->buf, "a"))
        {
            Student *stu = (Student *)mymalloc(sizeof(Student));

            INPUT("Student name:", bbuf);
            stu->name = getdaostr(bbuf);

            INPUT("Student age:", bbuf);
            stu->age = atoi(bbuf->buf);

            INPUT("Student gender:", bbuf);
            stu->gender = getdaostr(bbuf);

            CLEAR_SCREEN;

            da_append(stus, stu);

            printf("Student{name=%s, gender=%s, age=%d}\n", stu->name->str, stu->gender->str, stu->age);
            PRESS("Successful! press any key to return...");
        }
        else if (!strcmp(bbuf->buf, "r"))
        {
        }
        else if (!strcmp(bbuf->buf, "l"))
        {
            if (stus.count == 0)
            {
                PRESS("nothing. press any key to return...");
                continue;
            }
            else
            {
                printf("Student Tables:\n");
                for (int i = 0; i < stus.count; i++)
                {
                    printf("Student{name=%s, gender=%s, age=%d}\n",
                           stus.items[i]->name->str,
                           stus.items[i]->gender->str,
                           stus.items[i]->age);
                }
            }
            PRESS("done. press any key to return...");
        }
        else
        {
            PRESS("Input error, value must be a serial number!\npress any key to return...");
        }
    }

eof:
    delbuf(bbuf);
    return EOF;

end:
    printf("The system is exiting and saving your data, bye...\n");

    delbuf(bbuf);
    save();
    sleep(1);
    return 0;
}