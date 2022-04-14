#include "RLEList.h"
#include <stdio.h>
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
    if ((list == NULL) || (value == NULL_CHAR)){    //Checks if one of parameter is null
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList nextNode = list;
    while (nextNode->next)                    //Gets to the last node in the list
    {
        nextNode = nextNode->next;
    }

    if (nextNode->letter == value)            //If the value is as the value of the last node in the list
    {
        nextNode->numOfReps += 1;
        return RLE_LIST_SUCCESS;
    }

    RLEList newNode = RLEListCreate();        //Create new node with the new value
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
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index > RLEListSize(list) || index < 1)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int counter = 0;
    RLEList prevNode = list;
    RLEList currNode = list->next;
    while (counter < index)
    {
        counter += currNode->numOfReps;
        if (counter >= index)
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
    if (list == NULL)                       //if null is given as an argument
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }

    int length = RLEListSize(list);
    if ((length < index) || (index < 1))           //if the index is out of bounds
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    RLEList ptr = list;
    ptr = ptr->next;
    while (ptr != NULL)
    {
        if (index <= ptr->numOfReps)         //if the index is within the appearences of a specific letter
        {
            *result = RLE_LIST_SUCCESS;
            return ptr->letter;
        }
        index = index - ptr->numOfReps;     //else, we'll check the index in the next node
        ptr = ptr->next;
    }
    return 0;             //won't get here anyway
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if ((list == NULL) || (map_function == NULL))    //if one of the arguments are null
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    RLEList ptr = list->next;
    while (ptr != NULL)
    {
        ptr->letter = map_function(ptr->letter);              //every node will change its letter according to the given function
        ptr = ptr->next;
    }
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
        counter += 2;                          //char and new line
        counter += NumberOfCharsFromInt(temp); //number of digit
        ptr = ptr->next;
    }
    return counter;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL)                           //if the argument list is null
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    int length = LengthOfWholeString(list);        //calculating the length of the dynamic array
    char* str_of_rle = (char*) malloc(length);     //allocating an array of chars which would be the answer
    if (str_of_rle == NULL)
    {
        *result = RLE_LIST_OUT_OF_MEMORY;        //Null if the allocation failed
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
    *result = RLE_LIST_SUCCESS;
    return str_of_rle;
}

char PlusOne(char c)
{
    return c + 1;
}

int main()
{
    //my test
    RLEList head = RLEListCreate();
    RLEListAppend(head,'c');                  //test append
    RLEListAppend(head,'f');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'e');
    RLEListAppend(head,'z');
    RLEListAppend(head,'s');
    RLEListAppend(head,'s');
    RLEListAppend(head,'a');
    RLEListAppend(head,'a');
    RLEListAppend(head,'s');
    printf("Testing printing:\n");
    for (RLEList ptr = head; ptr != NULL; ptr=ptr->next){      //test print
        printf("%c ", ptr->letter);
    }
    printf("\n");
    printf("Testing removing single char\n");
     RLEListRemove(head, 19);                            //test remove
     for (RLEList ptr = head; ptr != NULL; ptr=ptr->next){
        printf("%c ", ptr->letter);
    }
    printf("\n");
    RLEListResult res = RLE_LIST_SUCCESS;
    printf("Testing Get char from index\n");
    printf("%c\n\n", RLEListGet(head, 1, &res));     //test get
    printf("Testing mapping\n");
    RLEListMap(head, PlusOne);                                  //test mapping
    for (RLEList ptr = head; ptr != NULL; ptr=ptr->next){
        printf("%c ", ptr->letter);
    }
    printf("\n");
    printf("Testing export to string\n");
    char* ans = RLEListExportToString(head, &res);           //test export to string
    for (int i = 0; i < LengthOfWholeString(head); i++)
    {
        printf("%c", ans[i]);
    }
    printf("\n");
    free(ans);
    RLEListDestroy(head);                         //test destroy
    return 0;
}

//implement the functions here