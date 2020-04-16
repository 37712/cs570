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

#include "belt.h"


// void * because it is a thread
void *consumer(void * ptr);

#endif // CONSUMER_H