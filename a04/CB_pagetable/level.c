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

#include "level.h"

//  LogicalAddress to page number
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift;
}

// traverse levels to reach the map and insert frame
bool insertLVL(unsigned int LogicalAddress, int frame)
{
    // allocates memory and sets variables for root level
    if(pagetable->RootLevelPtr == NULL)
    {
        pagetable->RootLevelPtr = malloc(sizeof(struct LEVEL));
        pagetable->RootLevelPtr->depth = 0;
        pagetable->RootLevelPtr->NextLevelPtr = NULL;
        pagetable->RootLevelPtr->MapPtr = NULL;
    }

    Level ptr = pagetable->RootLevelPtr; // never mess around with root, use pointer

    unsigned int pageIndex;
    int levelCount = pagetable->levelCount -1; // -1 so we don't go out of bounds
    unsigned int * Mask = pagetable->BitmaskArray;
    unsigned int * Shift = pagetable->ShiftArray;
    // traversing and creating levels until map is reached
    for(int i = 0; i < levelCount; i++)
    {
        //printf("depth = %d\n", ptr->depth);

        // allocate memory for NextLevelPtr
        if(ptr->NextLevelPtr == NULL) // if level is NULL allocate memory
        {
            ptr->NextLevelPtr = malloc(sizeof(struct LEVEL) * pagetable->EntryCount[i]);
            // make all NextLevelPtr entries NULL at start
            for(int j = 0; j < pagetable->EntryCount[i]; j++)
                ptr->NextLevelPtr[j] = NULL;
        }

        // get page index from logicaladdress for level array
        pageIndex = LogicalToPage(LogicalAddress, Mask[i], Shift[i]);

        // allocate memroy for next level
        if(ptr->NextLevelPtr[pageIndex] == NULL)
        {
            ptr->NextLevelPtr[pageIndex] = malloc(sizeof(struct LEVEL));
            ptr->NextLevelPtr[pageIndex]->depth = ptr->depth + 1;
            ptr->NextLevelPtr[pageIndex]->NextLevelPtr = NULL;
            ptr->NextLevelPtr[pageIndex]->MapPtr = NULL;
        }

        // move pointer to next level
        ptr = ptr->NextLevelPtr[pageIndex];
    }

    // this is leaf level now
    //printf("depth = %d\n", ptr->depth);

    // create map and allocate memory
    if(ptr->MapPtr == NULL)
    {
        ptr->MapPtr = malloc(sizeof(struct MAP));
        ptr->MapPtr->frameArray = malloc(sizeof(int) * pagetable->EntryCount[levelCount]);
        for(int i = 0; i < pagetable->EntryCount[levelCount]; i++)
            ptr->MapPtr->frameArray[i] = -1; // -1 means invalid
    }

    // get leaf level index
    pageIndex = LogicalToPage(LogicalAddress, Mask[levelCount], Shift[levelCount]); // levelcount is already -1 of itself

    return insertframe(ptr->MapPtr, pageIndex, frame);
}

