#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>    // needed to use pthread

// structure for progress status
typedef struct {
long * CurrentStatus;   // represents the current status of the computation being tracked (progress indicator)
long InitialValue;      // starting value for the computation
long TerminationValue;  // value at which the computation is complete
} PROGRESS_STATUS;
// TerminationValue >= Progress Indicator >= InitialValue

/*
As an example of this, let us suppose that InitialValue = 10, TerminationValue
= 60, and the progress indicator (*CurrentStatus) = 50. If the progress_monitor
thread is scheduled under these conditions, 80% (40/50ths) of the task has been
completed. Consequently, .80 * 40 = 32 hyphens should be displayed:
*/

void * progress_monitor(void *progress_stat)
{
    for(int i = 0; i<40; i++)
        printf("-");

    return;
}

long wordcount(FILE * fp)
{

}

int main(int argc,char **argv)
{

    if(argc != 2) // check if arguments are wrong or not set
    {
        printf("arguments check failed");
        return -1;
    }

    // open text file
    FILE *fp = fopen(argv[1], "r");// 'r' is for read

    // check that file opened successfully
    if (fp == NULL)
    {
		printf("Failed to open or find file!\n");
		return -2;
	}

    printf("There are %lu words in %s", wordcount(fp), argv[1]);

    //PROGRESS_STATUS ps;

    // thread ID
    //pthread_t tid;

    return 0;
}
