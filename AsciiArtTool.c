#include "AsciiArtTool.h"
#define CHUNK_LINE 256

RLEList asciiArtRead(FILE* in_stream)
{
    char lst_read[CHUNK_LINE];
    RLEList head = RLEListCreate();
    while (fgets(lst_read, CHUNK_LINE, in_stream))
    {
        for (int i = 0; i < CHUNK_LINE; i++)
        {
            RLEListAppend(head, lst_read[i]);
        }
    }
    return head;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult res = RLE_LIST_SUCCESS;
    if ((list == NULL) || (out_stream == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int length = RLEListSize(list);
    char c;
    for (int i=0; i < length; i++)
    {
        c = RLEListGet(list, i, &res);
        if (c == ' ')
        {
            c = '@';
        }
        else
        {
            if (c == '@')
            {
                c = ' ';
            }
        }
        fputc(RLEListGet(list, i, &res), out_stream);
    }
    return res;
}

static int strLen(char* s)
{
    int counter = 0;
    while (*s)
    {
        counter++;
        s++;
    }
    return counter;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    RLEListResult res = RLE_LIST_SUCCESS;
    if ((list == NULL) || (out_stream == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char *ans = RLEListExportToString(list, &res);
    int length = strLen(ans);
    for (int i=0; i < length; i++)
    {
        fputc(ans[i], out_stream);
    }
    return res;
}
