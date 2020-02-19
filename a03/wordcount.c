/*
 * wordcount.c
 *
 * CS570, spring 2020
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>    // needed to use pthread

// structure for progress status
typedef struct {
long * CurrentStatus;   // represents the current status of the computation being tracked (progress indicator)
long InitialValue;      // starting value for the computation
long TerminationValue;  // value at which the computation is complete
} PROGRESS_STATUS;
// TerminationValue >= Progress Indicator >= InitialValue

// progress bar method
void * progress_monitor(void * progStatus)
{
    printf("C\n");
    // needs casting to work
    PROGRESS_STATUS * currStatus = (PROGRESS_STATUS *) progStatus;

    printf("D\n");
    
    while(true)
    {
        long tmp = (long)(currStatus->CurrentStatus);
        int progBar = (int)(((float)tmp / (float)currStatus->TerminationValue) * 40);
        
        printf("bar = %d\n",progBar);
        for(int i = 0; i<=progBar; i++)
        {   // every 10, print out +
            if(i % 10 == 0 && i != 0)
                printf("+");
            else
                printf("-");
        }
        printf("bar = %d",progBar);
        printf("\n");
        fflush(stdout); // required
        if(progBar > 5) break;
    }
    
}


long wordcount(FILE * fp)
{
    long size;

    // get file size
    fseek(fp, 0, SEEK_END);     // go to the end of the file
    size = ftell(fp);           // get current file pointer
    rewind(fp);                 // rewind back to beginning of file

    printf("size = %lu\n",size);

    // initializing program status
    PROGRESS_STATUS * progStatus = malloc(sizeof(PROGRESS_STATUS));  // allocating memory for pointer
    progStatus->TerminationValue = size;
    progStatus->CurrentStatus = 0;
    
    printf("A\n");
    
    // start the thread for the progress bar
    pthread_t progThread;
    pthread_create(&progThread, NULL, progress_monitor, (void *)progStatus);
    
    printf("B\n");
    
    //delimiter for strtok
    const char delimiters[] = "\t\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

    // counting number of words in file
    char str[512];
    char * tok = NULL;
    long count = 0;
    while(fgets(str, 512, (FILE*)fp))
    {
        tok = strtok(str, delimiters); // tokenise the string
        while (tok != NULL)
        {
            //printf("%s\n",tok);
            tok = strtok(NULL, delimiters);
            count++;
        }
        progStatus->CurrentStatus++; // increase current status
    }

	pthread_join(progThread,NULL);  // join the thread
	free(progStatus);   // free memory

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

    printf("There are %lu words in file %s\n", wordcount(fp), argv[1]);


    // never forget to close opened files
	fclose(fp);

    return 0;
}
