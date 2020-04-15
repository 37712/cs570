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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // needed for bool

#include <unistd.h>     // needed for getopt and optind
#include <getopt.h>     // for linux compilation

#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores

#include "mystruct.h"
#include "belt.h"
#include "producer.h"
#include "consumer.h"

/*
 *  IMPORTANT:
 *  OPTIONAL ARGUMENTS LIKE -E -L -f -e
 *  MUST COME FIRST WHEN RUNNING THE EXE
 */

int main(int argc, char ** argv)
{
    // option arguments
    int Option; // option value index
    int Ethel_N = 0;
    int Lucy_N = 0;
    int frog_N = 0;
    int escar_N = 0;
    bool E = false;
    bool L = false;
    bool f = false; 
    bool e = false;

    // getopt gets next argument option from argv and argc
    while ( (Option = getopt(argc, argv, "E:L:f:e:")) != -1)
    {
        switch (Option)
        {
            case 'E': /* Ethel consumer, N = number of miliseconds */
                E = true;
                Ethel_N = atoi(optarg);
                printf("Ethel %d\n", Ethel_N);
                break;

            case 'L': /* Lucy consumer, N = number of miliseconds */
                L = true;
                Lucy_N = atoi(optarg);
                printf("Lucy %d\n", Lucy_N);
                break;

            case 'f': /* frog bite, N = number of miliseconds */
                f = true;
                frog_N = atoi(optarg);
                printf("frog bites %d\n", frog_N);
                break;
            
            case 'e': /* escargot, N = number of miliseconds */
                e = true;
                escar_N = atoi(optarg);
                printf("escargot %d\n", escar_N);
                break;
        }
    }

    //initialize semaphore multivariables
    struct multivar * var = malloc(sizeof(struct multivar));
    var->total = 0;
    var->production_limit = 10;			    // produce 100 candies
	var->product_id = frog_bite; // frog bytes = 0, escargot = 1
	var->consumer_id = Lucy; // Lucy = 0, Ethel = 1
	
    var->Ethel = E;
	var->Lucy = L;
	var->frog = f;
	var->escar = e;

    var->Ethel_N = Ethel_N;
    var->Lucy_N = Lucy_N;
    var->frog_N = frog_N;
    var->escar_N = escar_N;

	var->belt = NULL;    // FIFO link list should be started as null
    var->belt_count = 0; // this is size of link list

    // initialize semaphores
    //sem_init(&var->goal, 0, goal);              // Produce 100 candies
	sem_init(&var->unconsumed, 0, 0);			// Number of unconsumed candies on belt
	sem_init(&var->frog_bites, 0, 3);			// no more than 3 frog bites on belt
	sem_init(&var->available_space, 0, 1);	    // to check for belt_count
    sem_init(&var->belt_access, 0, 1);			// Critical region
	sem_init(&var->type, 0, 1);				    // To set producer or consumer type

    // thread variables
    pthread_t frogbite_thread;
	//pthread_t escargot_thread;
	//pthread_t lucy_thread;
	//pthread_t ethel_thread;

    // thread creation
    pthread_create(&frogbite_thread, NULL, producer, var);
	//pthread_create(&escargot_thread, NULL, producer, var);
	//pthread_create(&lucy_thread, NULL, consumer, var);
	//pthread_create(&ethel_thread, NULL, consumer, var);

    // proper thread finalization
    pthread_join(frogbite_thread, NULL);
	//pthread_join(escargot_producer, NULL);
	//pthread_join(lucy_consumer, NULL);
	//pthread_join(ethel_consumer, NULL);

    // destroy semaphores
    //sem_destroy(&var->goal);          
    sem_destroy(&var->unconsumed);		
    sem_destroy(&var->frog_bites);		
    sem_destroy(&var->available_space);	
    sem_destroy(&var->belt_access);		
    sem_destroy(&var->type);			
    
    return 0;
}