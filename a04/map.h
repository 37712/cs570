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

// structure of leaf table, not a level itself

struct MAP
{
    int depth;
    int * frameArray;
};

int getframe(int pagenumber);

bool insertpage(int pagenumber, int framenumber);


#endif // MAP_H_INCLUDED