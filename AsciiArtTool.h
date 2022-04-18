//
// Created by נדב on 16/04/2022.
//

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"


/**
 * asciiArtRead: reads a file and compresses it as RLE list
 * @param in_stream - file that contains a picture in which we want to compress
 * @return - RLE list that contains all the chars in the given file
 */

RLEList asciiArtRead(FILE* in_stream);

/**
 * asciiArtPrint: writes into file the picture using the RLE list
 * @param list - RLE list that contains all the chars we want to write as a picture
 * @param out_stream - a file to write into
 * @return - A suitable message whether it succeeded or not
 */

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 * asciiArtPrintEncoded: writes the picture into the file in a compressed way
 * @param list - RLE list that contains the chars in the picture
 * @param out_stream - a file to write into
 * @return - suitable message if it succeeded or not
 */

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //HW1_ASCIIARTTOOL_H
