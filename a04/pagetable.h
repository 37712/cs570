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

#include "level.h"

struct page_table
{
    unsigned int levelCount;        // number of levels
    unsigned int * BitmaskArray;    // bit mask for each level
    unsigned int * ShiftArray;      // number of bits to shift each level page bits
    unsigned int * entryCountArray; //
};

// this enables us to just say "pagetable" instead of "struct page_table"
typedef struct page_table * pagetable; // this is pointer type

// funtion declarations
bool insert(char * str); // insert word


#endif // PAGETABLE_H_INCLUDED