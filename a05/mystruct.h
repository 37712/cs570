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

#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>       // needed to use nanosleep()
#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores

typedef enum ptype
{
  frog_bite, // 0
  escargot // 1
}
producer_type;

typedef enum ctype
{
  Lucy, // 0
  Ethel // 1
}
consumer_type;

// this enables us to say Link instead of struct node *
typedef struct node * Link; // Link is pointer type

struct node{
    producer_type candy_type;
    Link next;
};

struct multivar
{
    // semaphores
    sem_t belt_access; // only one tread can have access to belt push or pop
    sem_t type; // configuratoin for production or consumption

    producer_type product_id; // frog bytes = 0, escargot = 1
	consumer_type consumer_id; // Lucy = 0, Ethel = 1

    int total_produced; // total candies produced so far
    int total_consumed; // total candies consumed so far
    int production_limit; // 100 candies

    // flag variables
    bool producing;
	bool Ethel;
    bool Lucy;
    bool frog;
    bool escar;

    // N sleep time values
	struct timespec Ethel_N;
    struct timespec Lucy_N;
    struct timespec frog_N;
    struct timespec escar_N;
    
    Link belt; // belt in the head of linked list
    int belt_count; // amount of candy currently in belt
};

#endif // MYSTRUCT_H