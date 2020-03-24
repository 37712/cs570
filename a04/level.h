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

struct LEVEL
{
    int depth;

    // next level is level or map type
    struct LEVEL ** NextLevelPtr; // pointer to an array
    struct MAP * MapPtr; // pointer to the map structure
    // pagetable pointer is global varaibale
};

// this enables us to just say "Level" instead of "struct LEVEL"
typedef struct LEVEL * Level; // this is pointer

// insert next level
bool insertLVL(unsigned int LogicalAddress, int frame);

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift);

#endif // LEVEL_H_INCLUDED

