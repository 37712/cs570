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

#include "producer.h"

void * producer(void * ptr)
{
    // needs casting to work
    struct multivar * var = (struct multivar *) ptr;
	
	// type of candy to produce
	sem_wait(&var->type); // semaphore down
        int candy_type;
        // frog bytes = 0, escargot = 1
        switch (var->product_id)
        {
            case frog_bite:
                //printf("frog bite tread started\n");
                candy_type = frog_bite;
                var->product_id = escargot;
                break;
            case escargot:
                //printf("escargot tread started\n");
                candy_type = escargot;
                var->product_id = frog_bite;
                break;
        }
    sem_post(&var->type); // semaphore up

    // while total produced is less than limit 100
    while(var->total_produced < var->production_limit)
    {
        // add candy type to belt
		sem_wait(&var->belt_access);

            //checck if belt is full
            if(var->belt_count >= 10)
            {
                sem_post(&var->belt_access);
                continue;
            }

            // if frog bite, check for less than 3 frog bite
            if (candy_type == frog_bite && candycount(frog_bite, var->belt) >= 3)
            {
                sem_post(&var->belt_access);
                continue;
            }

            // update total produced and belt count
            var->total_produced++;
            var->belt_count++;
                
            //printf("pB2\n");
            // print bealt update
            produce(candy_type, &var->belt);// Add candy to belt
            printupdate(var->belt);
            printf("added %s.\n", candy_type ? "escargot sucker": "crunchy frog bite");

		sem_post(&var->belt_access);

		// sleep production thread for N miliseconds
		if (var->frog && candy_type == frog_bite)
			nanosleep(&var->frog_N, NULL); // suspend execution of thread
		else if (var->escar && candy_type == escargot)
			nanosleep(&var->escar_N, NULL); // suspend execution of thread
	}
}