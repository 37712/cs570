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
        //int total = var->total_produced; // total so far
        //int limit = var->production_limit; // production limit 100
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
	//while (total < limit)
    while(var->total_produced < var->production_limit)
    {
        //printf("pA\n");
        //Checks if 10 candies on belt
		/*sem_wait(&var->available_space);

            if(var->belt_count >= 10)
            {
                //sem_post(&var->available_space);
                continue;
            }

        sem_post(&var->available_space);*/

        //printf("pB\n");

        // add candy type to belt
		sem_wait(&var->belt_access);

            //checck if belt is full
            if(var->belt_count >= 10)
            {
                sem_post(&var->belt_access);
                continue;
            }

            //printf("pB1\n");
            // if frog bite, check for less than 3 frog bite
            if (candy_type == frog_bite && candycount(frog_bite, var->belt) >= 3)
            {
                sem_post(&var->belt_access);
                continue;
            }

            // update total right before adding to belt
            //sem_wait(&var->update_total);
                var->total_produced++; // update total
                var->belt_count++;
            //sem_post(&var->update_total);
                
            //printf("pB2\n");
            // print bealt update
            produce(candy_type, &var->belt);// Add candy to belt
            printupdate(var->belt);
            printf("added %s.\n", candy_type ? "escargot sucker": "crunchy frog bite");

		sem_post(&var->belt_access);

        //printf("pC\n");

		// sleep production thread for N miliseconds
		if (var->frog && candy_type == frog_bite)
			nanosleep(&var->frog_N, NULL); // suspend execution of thread for x miliseconds
		else if (var->escar && candy_type == escargot)
			nanosleep(&var->escar_N, NULL); // suspend execution of thread for x miliseconds
        
        //printf("pT\n");
        
	}

    //sem_wait(&var->prod);
      //  var->producing = false; // production has ended
    //sem_post(&var->prod);
}