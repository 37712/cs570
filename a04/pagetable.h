/*
 * CS570, spring 2020
 * 
 * pagetable.h
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#ifndef PAGETABLE_H_INCLUDED
#define PAGETABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "level.h"

// page table contains information about the tree, but is not part of tree itself

struct PAGETABLE
{
    struct PAGETABLE * RootLevelPtr;   // pointer to level 0 page table
    
    unsigned int levelCount;        // number of levels
    unsigned int * BitmaskArray;    // size of each level and map array
    unsigned int * ShiftArray;      // number of bits to shift each level page bits
    unsigned int * entryCountArray; // number of possible pages for level i
};

// this enables us to just say "PageTable" instead of "struct PAGETABLE"
typedef struct PAGETABLE * PageTable; // this is pointer type

PageTable rootPageTable = NULL; // this is a pointer

// funtion declarations
bool insertPT(unsigned int LogicalAddress, unsigned int Frame);


#endif // PAGETABLE_H_INCLUDED