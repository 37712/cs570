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
    struct LEVEL * RootLevelPtr;    // pointer to level 0 page table
    int pagesize;
    unsigned int levelCount;        // number of levels
    unsigned int * BitmaskArray;    // mask for each level {0xFF000000, 0x00FF0000, 0x0000FF00}
    unsigned int * ShiftArray;      // number of bits to shift each level page bits {24, 16, 8}
    unsigned int * EntryCount;      //size of each array {2^8, 2^8, 2^8}
};

// this enables us to just say "PageTable" instead of "struct PAGETABLE"
typedef struct PAGETABLE * PageTable; // this is pointer type

// Yes, this is a global pointer variable... in a header.
PageTable pagetable; // yes, I like to live dangerously.

// function declarations

bool PageInsert(unsigned int LogicalAddress, int frame);

void createPageTable(int argc, char ** argv, int optind);

int PageLookup(unsigned int LogicalAddress);

int sizeofpagetable();

#endif // PAGETABLE_H_INCLUDED
