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
#include "consumer.h"

#include <unistd.h>     // needed for getopt and optind
#include <getopt.h>     // for linux compilation

/* time conversions */
#define NSPERMS     1000000 /* million ns/ms */
#define MSPERSEC    1000  /* thousand ms/s */

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
                //printf("Ethel %d\n", Ethel_N);
                break;

            case 'L': /* Lucy consumer, N = number of miliseconds */
                L = true;
                Lucy_N = atoi(optarg);
                //printf("Lucy %d\n", Lucy_N);
                break;

            case 'f': /* frog bite, N = number of miliseconds */
                f = true;
                frog_N = atoi(optarg);
                //printf("frog bites %d\n", frog_N);
                break;
            
            case 'e': /* escargot, N = number of miliseconds */
                e = true;
                escar_N = atoi(optarg);
                //printf("escargot %d\n", escar_N);
                break;
        }
    }
    /*
        Requeremnt #4:
        Do not use global variables to communicate information to your threads.
        Pass information through data structures.
    */
    // initialize gloval variables, these variables do not pass information to threads
    produced = 0;
    frog_total = 0;
    escar_total = 0;

    L_frog_total = 0;
    L_escar_total = 0;

    E_frog_total = 0;
    E_escar_total = 0;

    /* these variables are not global, so they will be used for threads */
    // multivariable structure for threads
    struct multivar * var = malloc(sizeof(struct multivar));

    var->product_id = frog_bite; // frog bytes = 0, escargot = 1
	var->consumer_id = Lucy; // Lucy = 0, Ethel = 1

    var->total_produced = 0;
    var->total_consumed = 0;
    var->production_limit = 100;			    // produce 100 candies
	
    // bool variables
    var->Ethel = E;
	var->Lucy = L;
	var->frog = f;
	var->escar = e;
    var->producing = true;

    // N miliseconds time conversion
    var->Ethel_N.tv_sec = Ethel_N / MSPERSEC;               /* # secs */
    var->Ethel_N.tv_nsec = (Ethel_N % MSPERSEC) * NSPERMS;  /* # nanosecs */

    var->Lucy_N.tv_sec = Lucy_N / MSPERSEC;                 /* # secs */
    var->Lucy_N.tv_nsec = (Lucy_N % MSPERSEC) * NSPERMS;    /* # nanosecs */

    var->frog_N.tv_sec = frog_N / MSPERSEC;                 /* # secs */
    var->frog_N.tv_nsec = (frog_N % MSPERSEC) * NSPERMS;    /* # nanosecs */

    var->escar_N.tv_sec = escar_N / MSPERSEC;               /* # secs */
    var->escar_N.tv_nsec = (escar_N % MSPERSEC) * NSPERMS;  /* # nanosecs */

    // belt (linked list) variables
	var->belt = NULL;    // FIFO link list should be started as null
    var->belt_count = 0; // this is size of link list

    // initialize semaphores
    sem_init(&var->belt_access, 0, 1);			// to get access to belt operations
	sem_init(&var->type, 0, 1);				    // To set producer or consumer type

    // thread variables
    pthread_t frogbite_thread;
	pthread_t escargot_thread;
	pthread_t lucy_thread;
	pthread_t ethel_thread;

    // thread creation
    pthread_create(&frogbite_thread, NULL, producer, var);
	pthread_create(&escargot_thread, NULL, producer, var);
	pthread_create(&lucy_thread, NULL, consumer, var);
	pthread_create(&ethel_thread, NULL, consumer, var);

    // proper thread finalization
    pthread_join(frogbite_thread, NULL);
    pthread_join(escargot_thread, NULL);
	pthread_join(lucy_thread, NULL);
	pthread_join(ethel_thread, NULL);

    // destroy semaphores	
    sem_destroy(&var->belt_access);		
    sem_destroy(&var->type);			
    
    // print final report
    printreport();
    return 0;
}