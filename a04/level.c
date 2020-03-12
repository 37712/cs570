/*
 * CS570, spring 2020
 *
 * level.c
 * 
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "level.h"
#include "pagetable.h" // needed to be able to point back
#include "map.h" // needed to be able to initialize the map structure

// traverse levels to reach the map and insert frame
bool insertLVL(unsigned int LogicalAddress, unsigned int frame)
{
    Level ptr = pagetable->RootLevelPtr; // never mess around with root pointer
    int levelCount = pagetable->levelCount -1;
    unsigned int page;
    unsigned int * Mask = pagetable->BitmaskArray;
    unsigned int * Shift = pagetable->ShiftArray;
    // traversing levels until map is reached
    for(int i = 1; i < levelCount; i++)
    {
        // get page number from logicaladdress for level array
        page = LogicalToPage(LogicalAddress, Mask[i], Shift[i]);

        // allocate memory and set varibales for NextLevelPtr
        if(ptr->NextLevelPtr[page] == NULL) // if level is NULL allocate memory
        {
            ptr->NextLevelPtr[page] = malloc(sizeof(struct LEVEL));
            ptr->NextLevelPtr[page]->depth = i;
            ptr->NextLevelPtr[page]->NextLevelPtr = malloc(sizeof(struct LEVEL) * pagetable->EntryCount[i]);
            ptr->MapPtr = NULL;
            // make all entries NULL at start
            for(int j = 0; j < pagetable->EntryCount[i]; j++)
                ptr->NextLevelPtr[page]->NextLevelPtr[j] = NULL;
        }

        // move pointer to next level
        ptr = ptr->NextLevelPtr[page];
    }

    // ptr is now pointing to leaf level
    // get page number from logicaladdress for level array
    page = LogicalToPage(LogicalAddress, Mask[levelCount], Shift[levelCount]);

    //free up un used NextLevelPtr memory on map level
    free(pre);
    
    if(ptr->MapPtr == NULL) // if level is NULL allocate memory and set variables
    {
        ptr->MapPtr = malloc(sizeof(struct LEVEL));
        ptr->MapPtr[page]->depth = levelCount;
        ptr->MapPtr[page]->NextLevelPtr = malloc(sizeof(struct LEVEL) * pagetable->EntryCount[levelCount]);
        ptr 
        // make all entries NULL at start
        for(int j = 0; j < pagetable->EntryCount[i]; j++)
            ptr->NextLevelPtr[page]->NextLevelPtr[j] = NULL;
    }




    

    return false;
}

//  LogicalAddress to page number
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift;
}