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

void produce(producer_type candy_type, Link * head);

producer_type consume(Link * head);

int candycount(producer_type candy_type, Link head);

void printlist(Link ptr);

void printbelt();

void printreport();

#endif // BELT_H