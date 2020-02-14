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

    // start the thread for the progress bar
    pthread_t progThread;
    pthread_create(&progThread, NULL, progress_monitor, (void *)progStatus);

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
    }

    // house cleaning part - thread join and free the allocated memory
	pthread_join(progThread,NULL);
	free(progStatus);

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
