//
// Created by Assaf on 07/03/2022.
//

#ifndef HW1_RLELIST_H
#define HW1_RLELIST_H

#include <stdio.h>
#include <stdbool.h>

/**
* Run Length Encoding List
*
* Implements an RLE list containing characters and their count.
* The RLE list has an internal iterator for external use. For all functions
* where the state of the iterator after calling that function is not stated,
* it is undefined. That means that you cannot assume anything about it.
*
* The following functions are available:
*   RLEListCreate	        - Creates a new empty RLE list.
*   RLEListDestroy		    - Deletes an existing RLE list and frees all resources.
*   RLEListAppend           - Appends a character to the end of the list.
*   RLEListSize		        - Returns the total number of characters a given RLE list holds.
*   RLEListNumOfNodes       - Returns the number of nodes in a given RLE list.
*   RLEListRemove	        - Removes a character at a given index in the list.
*   RLEListGet              - Returns the character found at a given index.
*   RLEListExportToString   - Returns a string of all the characters in the RLE list.
*   RLEListMap              - Transforms the list by applying a given function to each character in the list.
*/


/** 
* Type for defining the RLE list.
* The implementation of struct RLEList_t needs to be defined in RLEList.c
*/
typedef struct RLEList_t *RLEList;

/** Type used for returning error codes from RLE list functions */
typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} ListResult;


/** 
 * Type of function for converting a character.
 * This function should return the transformed character
 */
typedef char (*mapFunction)(char);


/**
* RLEListCreate: Allocates a new empty RLE list.
*
* @return
* 	NULL if allocations failed.
* 	A new RLEList in case of success.
*/
RLEList RLEListCreate();


/**
* RLEListDestroy: Deallocates an existing RLE list.
*
* @param list - Target RLE list to be deallocated. If RLE list is NULL nothing will be done
*/
void RLEListDestroy(RLEList list);


/**
*   RLEListAppend: add a specified character at the end of the list.
*   Iterator's value is undefined after this operation.
*
* @param list - The RLE list for which to add the character
* @param value - The character which needs to be added.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_OUT_OF_MEMORY if an allocation failed
* 	RLE_LIST_SUCCESS if the character has been inserted successfully
*/
ListResult RLEListAppend(RLEList list, char value);


/**
* RLEListSize: Returns the total number of characters in an RLE list.
* @param list - The RLE list whose size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the total number of characters in the list.
*/
int RLEListSize(RLEList list);


/**
* RLEListNumOfNodes: Returns the number of nodes in an RLE List.
* @param list - The RLE list whose node count is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the number of nodes in the list.
*/
int RLEListNumOfNodes(RLEList list);


/**
*   RLEListRemove: Removes a character found at a specified index in an RLE list.
*   Iterator's value is undefined after this operation.
*
* @param list - The RLE list to remove the character from.
* @param index - The index at which the character to be removed is found.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	RLE_LIST_SUCCESS the character found at index has been removed successfully.
*/
ListResult RLEListRemove(RLEList list, int index);


/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	-1 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.   
*/
char RLEListGet(RLEList list, int index, ListResult *result);

char *RLEListExportToString(RLEList list);


ListResult RLEListMap(RLEList list, mapFunction map_function);


#endif // HW1_RLELIST_H
