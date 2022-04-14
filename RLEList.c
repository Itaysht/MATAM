#include "RLEList.h"
#include <stdlib.h>


struct RLEList_t {
    char letter;
    int numOfReps;
    struct list* next;
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
    if ((list == NULL) || (value == NULL)){    //Checks if one of parameter is null
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (list->numOfReps == 0)                  //When it's the first char in the list
    {
        list->letter = value;
        list->numOfReps = 1;
        return RLE_LIST_SUCCESS;
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
    if (list == NULL || index == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index > RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int counter = 0;
    RLEList prevNode = NULL;
    RLEList currNode = list;
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
        if (prevNode == NULL)
        {
            list = list->next;
        }
        else
        {
            prevNode->next = currNode->next;
        }
    }
    return RLE_LIST_SUCCESS;

}

int main()
{
    RLEList list = RLEListCreate();
    RLEListAppend(list,'a');
    RLEListAppend(list,'a');
    RLEListAppend(list,'b');
    RLEListAppend(list,'c');
    RLEList nextNode = list;
    while (!nextNode)
    {
        printf("%d", nextNode->numOfReps);
        nextNode = nextNode->next;
    }
    RLEListRemove(list, 2);
    nextNode = list;
    while (!nextNode)
    {
        printf("%d", nextNode->numOfReps);
        nextNode = nextNode->next;
    }

    return 0;
}

//implement the functions here