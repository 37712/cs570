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
    int total = var->total; // total so far
    int limit = var->production_limit; // production limit 100
    // frog bytes = 0, escargot = 1
    switch (var->product_id)
    {
        case frog_bite:
            printf("frog bite tread started\n");
            candy_type = frog_bite;
            var->product_id = escargot;
            break;
        case escargot:
            printf("escargot tread started\n");
            candy_type = escargot;
            var->product_id = frog_bite;
            break;
    }
    //printf("%S count = %d\n", total);
    sem_post(&var->type); // semaphore up

    int count = 0;

    //printf("A\n");

    // while total produced is less than limit 100
	while (total < limit)
    {
        //Checks for no more than 10 candies on belt
		sem_wait(&var->available_space);
        
        if(var->belt_count >= 10)
        {
            sem_post(&var->available_space);
            continue; // skip this iteration
        }

        sem_post(&var->available_space);

		// check if frogbite
        if (candy_type == frog_bite) {
            bool skip = false;
			sem_wait(&var->belt_access);

            // check for less than 3 frog bites
            if(candycount(frog_bite, var->belt) >= 3) skip = true;

            sem_post(&var->belt_access);

            if(skip) printf("frog_bite skipped %d\n", var->frog_N);
            if(skip) continue; // skip this iteration
		}

        // add candy type to belt
		sem_wait(&var->belt_access);

		produce(candy_type, &var->belt);//Add to belt

        printf("added candy type %s\n", candy_type ? "escargot": "frog bites");

		sem_post(&var->belt_access);

		//Sleep production thread for N miliseconds
		if (var->frog && candy_type == frog_bite)
			usleep(var->frog_N); // suspend execution of thread for x miliseconds
		else if (var->escar && candy_type == escargot)
			usleep(var->escar_N); // suspend execution of thread for x miliseconds
	}
}