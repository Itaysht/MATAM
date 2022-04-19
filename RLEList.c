#include "RLEList.h"
#include <stdlib.h>
#define NULL_CHAR '\0'

struct RLEList_t {
    char letter;
    int numOfReps;
    struct RLEList_t* next;
};

RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if (!ptr)
    {
        return NULL;
    }
    ptr->letter = ' ';
    ptr->numOfReps = 0;
    ptr->next = NULL;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if ((list == NULL) || (value == NULL_CHAR)){
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList nextNode = list;
    while (nextNode->next)
    {
        nextNode = nextNode->next;
    }

    if (nextNode->letter == value)
    {
        nextNode->numOfReps += 1;
        return RLE_LIST_SUCCESS;
    }

    RLEList newNode = RLEListCreate();
    if (newNode == NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }

    newNode->letter = value;
    newNode->numOfReps = 1;
    nextNode->next = newNode;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }

    int counter = 0;
    RLEList ptr = list;
    while (ptr->next)
    {
        counter += ptr->numOfReps;
        ptr = ptr->next;
    }
    counter += ptr->numOfReps;
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    int updated_idx = index + 1;
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index >= RLEListSize(list) || updated_idx < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int counter = 0;
    RLEList prevNode = list;
    RLEList currNode = list->next;
    while (counter <= updated_idx)
    {
        counter += currNode->numOfReps;
        if (counter > updated_idx)
        {
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;

    }
    if (currNode->numOfReps > 1)
    {
        currNode->numOfReps -= 1;
    }
    else
    {
        prevNode->next = currNode->next;
        free(currNode);
    }
    return RLE_LIST_SUCCESS;

}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }

    int length = RLEListSize(list);
    if ((length <= index) || (index < 0))
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    RLEList ptr = list;
    ptr = ptr->next;
    while (ptr != NULL)
    {
        if (index < ptr->numOfReps)
        {
            if (result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return ptr->letter;
        }
        index = index - ptr->numOfReps;
        ptr = ptr->next;
    }
    return 0;             //won't get here anyway
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if ((list == NULL) || (map_function == NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int length = RLEListSize(list);
    char* convert_to_string = (char*) malloc(length);
    if (convert_to_string == NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }

    RLEList ptr = list->next;
    int i = 0;
    while (ptr != NULL)
    {
        for (int j = 0; j < ptr->numOfReps; j++)
        {
            convert_to_string[i+j] = map_function(ptr->letter);
        }
        i = i + ptr->numOfReps;
        ptr = ptr->next;
    }

    RLEList ptr_to_destroy = list->next;
    list->next = NULL;
    RLEListDestroy(ptr_to_destroy);

    for (int j = 0; j < length; j++)
    {
        RLEListAppend(list, convert_to_string[j]);
    }
    free(convert_to_string);
    return RLE_LIST_SUCCESS;
}

/**
 * NumberOfCharsFromInt: return the number of digit of an int number
 * @param num - integer number which is the number of appearences in a row of a character
 * @return
 *      Number of digit of a integer number
*/
static int NumberOfCharsFromInt(int num)
{
    int counter = 0;
    while (num > 0)
    {
        counter += 1;
        num = num / 10;
    }
    return counter;
}

/**
 *
 * @param list - The RLE list to retrieve the characters from
 * @return
 *      The number of the exported string which includes the char of a node, the number of
 *      digit of the number of appearences of this char, and the new lines between every node
 */

static int LengthOfWholeString(RLEList list)
{
    if (list == NULL)
    {
        return 0;
    }

    int counter = 0, temp;
    RLEList ptr = list->next;
    while (ptr != NULL)
    {
        temp = ptr->numOfReps;
        counter += 2;
        counter += NumberOfCharsFromInt(temp);
        ptr = ptr->next;
    }
    return counter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }


    int length = LengthOfWholeString(list);        //calculating the length of the dynamic array
    char* str_of_rle = (char*) malloc(length);     //allocating an array of chars which would be the answer
    if (str_of_rle == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_OUT_OF_MEMORY;        //Null if the allocation failed
        }
        return NULL;
    }


    int i = 0, temp, num_of_chars;
    RLEList ptr = list->next;
    while (ptr != NULL)                 //each node will split to three parts: letter, chars of int
    {                                   //according to its length, and new line
        str_of_rle[i] = ptr->letter;
        i++;
        temp = ptr->numOfReps;
        num_of_chars = NumberOfCharsFromInt(temp);  //calculating the number of digits
        for (int j = 1; j <= num_of_chars; j++)
        {
            str_of_rle[i + num_of_chars - j] = (temp % 10) + '0';   //assigning respectively, '0' converting int to its char symbol
            temp = temp / 10;
        }
        str_of_rle[i+num_of_chars] = '\n';
        i = i + num_of_chars + 1;                 //moving on to the next node, index-wise
        ptr = ptr->next;
    }
    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return str_of_rle;
}
