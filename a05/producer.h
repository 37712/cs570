/*
 * CS570, spring 2020
 *
 * main.c
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#ifndef PRODUCER_H_INCLUDED
#define PRODUCER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "belt.h"
#include <time.h>     // needed for nanosleep
#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores

// void * because it is a thread
void * producer(void * ptr);

#endif // PAGETABLE_H_INCLUDED
