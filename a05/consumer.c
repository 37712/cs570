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

#include "consumer.h"

void * consumer(void * ptr)
{
    // needs casting to work
    struct multivar * var = (struct multivar *) ptr;
	
	// type of of consumer
	sem_wait(&var->type); // semaphore down
        int consumer_type;
        //int total_frog = 0; // total frog so far
        //int total_escar = 0; // total escargot so far
        // Lucy = 0, Ethel = 1
        switch (var->consumer_id)
        {
            case Lucy:
                //printf("Lucy tread started\n");
                consumer_type = Lucy;
                var->consumer_id = Ethel;
                break;
            case Ethel:
                //printf("Ethel tread started\n");
                consumer_type = Ethel;
                var->consumer_id = Lucy;
                break;
        }
    sem_post(&var->type); // semaphore up

    // while production is still going on or there is candy in the belt
	//while (total < limit && producing)
    while(var->producing || var->belt != NULL)
    {
        // remove candy from belt
        producer_type candy_type;
        //printf("cA\n");
		sem_wait(&var->belt_access);

            candy_type = consume(consumer_type, &var->belt);// Add to belt

            //printf("cA1\n");

            // if no candy was removed, skip iteration
            if(candy_type == -1)
            {
                sem_post(&var->belt_access);
                continue;
            }

            //printf("cA2\n");

            // print bealt update
            printupdate(var->belt);
            printf("%s consumed %s.\n",
                consumer_type ? "Ethel": "Lucy",
                candy_type ? "escargot sucker": "crunchy frog bite");

		sem_post(&var->belt_access);
        
        //printf("cB\n");

		// sleep consumption thread for N miliseconds
		if (var->Lucy && consumer_type == Lucy)
			sleep(var->Lucy_N); // suspend execution of thread for x miliseconds
		else if (var->Ethel && consumer_type == Ethel)
			sleep(var->Ethel_N); // suspend execution of thread for x miliseconds
        
	}
}