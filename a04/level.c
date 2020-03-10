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

bool insertLVL(unsigned int logicalAddress, unsigned int frame)
{
    // if rootLevel is NULL create rootLevel and allocate memory
    if(rootLevel == NULL)
    {
        rootLevel = malloc(sizeof(struct LEVEL));
        rootPageTable->RootLevelPtr = rootLevel;
    }
        

    

    unsigned int bitMask = rootPageTable->BitmaskArray[depth];
    unsigned int shift = rootPageTable->ShiftArray[depth];
    unsigned int location = (logicalAddress & bitMask) >> shift;
    rootPageTable->RootLevelPtr
    return false;
}