/*
 * CS570, spring 2020
 *
 * pagetable.c
 * 
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#include "pagetable.h"
#include "level.h"




bool insertPT(unsigned int LogicalAddress, unsigned int Frame)
{
    // if root is NULL create root and allocate memory
    if(rootPageTable == NULL)
        rootPageTable = malloc(sizeof(struct PAGETABLE));
    return insertLVL(LogicalAddress, Frame); // sent to sinrt in level file and return value
}

int getframenumber(unsigned int )
