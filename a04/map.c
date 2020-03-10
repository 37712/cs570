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

bool insertframe(struct MAP * map, int pageindex, int frame)
{
    // allocate memory if NULL
    if(map == NULL)
    {
        map = malloc(sizeof(struct MAP));
        for(int i = 0; i < map->size; i++)
            map->frameArray[i] = NULL;
    }
    map->frameArray[pageindex] = frame;
    return true;
}

int getframe(struct MAP * map, int pageindex)
{
    return map->frameArray[pageindex];
}

