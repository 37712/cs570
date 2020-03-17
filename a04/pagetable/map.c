/*
 * CS570, spring 2020
 *
 * map.c
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#include "map.h"

// insert frame in to frame array
bool insertframe(struct MAP * map, int pageindex, int frame)
{
    if(map->frameArray[pageindex] == -1) // if invalid
    {
        map->frameArray[pageindex] = frame;
        return true;
    }
    return false; // else, page already holds a frame, insertion failed
}

int getframe(struct MAP * map, int pageindex)
{
    return map->frameArray[pageindex];
}

