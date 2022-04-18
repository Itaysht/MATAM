#include <stdio.h>
#include <string.h>
#include "AsciiArtTool.h"

int main(int argc, char **argv) {
    if (argc != 4)
    {
        printf("Usage: ./AsciiArtTool -i or -e <source> <target>\n");
        return 0;
    }

    FILE* input = fopen(argv[2], "r");
    if (input == NULL)
    {
        printf("Can't open %s", argv[2]);
        return 0;
    }

    FILE* output = fopen(argv[3], "w");
    if (output == NULL)
    {
        printf("Can't open %s", argv[3]);
        fclose(input);
        return 0;
    }

    RLEList head = asciiArtRead(input);
    char* encoded = "-e";
    char* inverted = "-i";
    if (!strcmp(argv[1], inverted))
    {
        asciiArtPrint(head, output);
    }
    else
    {
        if (!strcmp(argv[1], encoded))
        {
            asciiArtPrintEncoded(head, output);
        }
        else
        {
            printf("Use the right flag");
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
