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

#ifndef BELT_H
#define BELT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mystruct.h"
#include <pthread.h> 
#include <semaphore.h>

// global variables, not for use in threads
int produced; // total produced
int frog_total;
int escar_total;

int L_frog_total;
int L_escar_total;

int E_frog_total;
int E_escar_total;

void produce(producer_type candy_type, Link * head);

producer_type consume(consumer_type consumer, Link * head);

int candycount(producer_type candy_type, Link head);

void printlist(Link ptr);

void printupdate(Link head);

void printreport();

#endif // BELT_H