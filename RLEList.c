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
    newNode->next = NULL;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list == NULL)
    {
        return -1;
    }

    int counter = 0;
    while (list->next)
    {
        counter += list->numOfReps;
        list = list->next;
    }
    counter += list->numOfReps;
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

int main()
{
    //my test
    RLEList head = RLEListCreate();
    RLEListAppend(head,'c');
    RLEListAppend(head,'f');
    RLEListAppend(head,'e');
    RLEListAppend(head,'z');
    RLEListAppend(head,'s');
    RLEListAppend(head,'s');
    RLEListAppend(head,'a');
    RLEListAppend(head,'a');
    RLEListAppend(head,'s');
    for (RLEList ptr = head; ptr != NULL; ptr=ptr->next){
        printf("%c", ptr->letter);
    }
    printf("\n");
    RLEListRemove(head, 9);
     for (RLEList ptr = head; ptr != NULL; ptr=ptr->next){
        printf("%c", ptr->letter);
    }
    RLEListDestroy(head);
    return 0;
}

//implement the functions here