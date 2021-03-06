/*
 * CS570, spring 2020
 *
 * map.h
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// array which maps from logical page to physical frame
struct MAP
{
    int * frameArray; // array
};

// insert frame in to frame array
bool insertframe(struct MAP * map, int pageindex, int frame);

int getframe(struct MAP * map, int pageindex);


#endif // MAP_H_INCLUDED
