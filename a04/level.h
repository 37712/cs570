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

#include "pagetable.h" // needed to be able to point back
#include "map.h" // needed to be able to initialize the map structure

// level table

struct LEVEL
{
    PageTable pagetablepointer; // points back to the pagetable

    int depth;

    // next level is aither level or map type
    struct LEVEL ** NextLevelPtr; // pointer to an array
    struct MAP * MapPtr; // pointer to the map structure
};

// this enables us to just say "PageTable" instead of "struct PAGETABLE"
typedef struct LEVEL * Level; // this is pointer type

Level rootLevel = NULL; // this is a pointer

// insert next level
bool insertLVL(unsigned int LogicalAddress, unsigned int Frame);


#endif // LEVEL_H_INCLUDED

