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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pagetable.h>
#include <level.h>


pagetable rootpagetable = NULL; // this is a pointer

bool insert()
{
    // if root is NULL create root and allocate memory
    if(rootpagetable == NULL)
    {
        rootpagetable = malloc(sizeof(struct page_table));
    }
    return false;
}

int getframenumber(unsigned int )
