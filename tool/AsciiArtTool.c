#include "AsciiArtTool.h"

RLEList asciiArtRead(FILE* in_stream)
{
    char one_char;
    RLEList head = RLEListCreate();
    if (head == NULL)
    {
        return NULL;
    }

    one_char = fgetc(in_stream);
    while (one_char != EOF)
    {
        RLEListAppend(head, one_char);
        one_char = fgetc(in_stream);
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
        fputc(c, out_stream);
    }
    return res;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    RLEListResult res = RLE_LIST_SUCCESS;
    if ((list == NULL) || (out_stream == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    char *ans = RLEListExportToString(list, &res);
    if (ans == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    int length = strlen(ans);
    for (int i=0; i < length; i++)
    {
        fputc(ans[i], out_stream);
    }
    free(ans);
    return res;
}
