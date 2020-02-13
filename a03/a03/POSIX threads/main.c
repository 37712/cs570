#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void * progress_monitor()
{
    for(int i = 0; i<40; i++)
        printf("-");

    return;
}

long wordcount()
{

}

int main()
{
    PROGRESS_STATUS ps;

    // thread ID
    pthread_t tid;

    return 0;
}
