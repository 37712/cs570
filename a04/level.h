/*
 * CS570, spring 2020
 *
 * level.h
 * 
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "pagetable.h"
#include "map.h"

// level table

struct LEVEL
{
    PageTable pagetablepointer; // points back to the pagetable
    int depth;

    // next level is aither level or map type
    struct LEVEL * nextlevel;
    struct MAP * maplevel;
};

// insert next level
bool insertLVL(unsigned int LogicalAddress, unsigned int Frame);


#endif // LEVEL_H_INCLUDED

