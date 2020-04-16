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

#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "belt.h"
#include <time.h>     // needed for nanosleep
#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores

// void * because it is a thread
void *consumer(void * ptr);

#endif // CONSUMER_H