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

#include <pthread.h> 
#include <semaphore.h>

typedef enum ptype
{
  frog_bite,
  escargot
}
producer_type;

typedef enum ctype
{
  Lucy,
  Ethel
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
	sem_t goal;
    sem_t unconsumed;
    sem_t frog_bites;
    sem_t available_space; // to check for belt_count
    sem_t belt_access; // only one tread can have access to belt push or pop
    sem_t type; // set up type of production or consumption

    producer_type product_id; // frog bytes = 0, escargot = 1
	consumer_type consumer_id; // Lucy = 0, Ethel = 1
    //int count; // individual count of each candy
    int total; // total candies produced so far
    int production_limit; // 100 candies
    int consumed; // candies consumed so far

    // flag variables
	bool Ethel;
    bool Lucy;
    bool frog;
    bool escar;

    // N values
	int Ethel_N;
    int Lucy_N;
    int frog_N;
    int escar_N;

    Link belt; // belt in the head of linked list
    int belt_count; // amount of candy currently in belt
};

#endif // MYSTRUCT_H