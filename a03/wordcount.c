/*
 * wordcount.c
 *
 * CS570, spring 2020
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>      // needed for isspace
#include <pthread.h>    // needed to use pthread

// structure for progress status
typedef struct {
long * CurrentStatus;   // represents the current status of the computation being tracked (progress indicator)
long InitialValue;      // not needed, useless variable
long TerminationValue;  // value at which the computation is complete
} PROGRESS_STATUS;
// TerminationValue >= Progress Indicator >= InitialValue

// progress bar method
void * progress_monitor(void * progStatus)
{
    int progBar = 0;
    int i = 0;
    // needs casting to work
    PROGRESS_STATUS * tmp = (PROGRESS_STATUS *) progStatus;

    while(progBar < 40)
    {
        // calculating progress of the bar
        progBar = (int)(((long)tmp->CurrentStatus / (float)tmp->TerminationValue) * 40);

        // makes the bar
        while(i<=progBar)
        {   // every 10, print out +
            if(i % 10 == 0 && i != 0)
                printf("+");
            else
                printf("-");
            fflush(stdout); // required
            i++;
        }
    }
    printf("\n");
}


long wordcount(FILE * fp)
{
    long size;

    // get file size
    fseek(fp, 0, SEEK_END);     // go to the end of the file
    size = ftell(fp);           // get current file pointer
    rewind(fp);                 // rewind back to beginning of file

    // initializing program status
    PROGRESS_STATUS * progStatus = malloc(sizeof(PROGRESS_STATUS));  // create and allocating memory for pointer
    progStatus->CurrentStatus = 0;
    progStatus->TerminationValue = size;

    // start the thread for the progress bar
    pthread_t progThread;
    pthread_create(&progThread, NULL, progress_monitor, (void *)progStatus);

    // needed to count number of words in file
    char ptr, pre;
    long count = 0;

    // while ptr does not reach end of file
    while(ptr != EOF)
    {
        ptr = getc(fp); // get character
        progStatus->CurrentStatus++; // increase current status

        // count anything that is separated by white space
        if(!isspace(pre) && isspace(ptr)) count++;

        pre = ptr; // give previous location to pre
    }

	pthread_join(progThread,NULL);  // proper way to end a thread
	free(progStatus);   // never forget to free pointer memory

    return count;
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

    printf("There are %lu words in %s\n", wordcount(fp), argv[1]);

    // never forget to close opened files
	fclose(fp);

    return 0;
}
