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
#include <unistd.h>     // needed for getopt and optind
#include <stdbool.h>    // needed for bool

#include "pagetable.h"
#include "byutr.h"

/*
 *  IMPORTANT:
 *  OPTIONAL ARGUMENTS LIKE -n -p -t
 *  MUST COME FIRST WHEN RUNNING THE EXE
 */

bool pHandler(char * filetowrite);

int main(int argc, char ** argv)
{
    // check if arguments are wrong or not set
    if(argc < 2)
    {
        printf("arguments are wrong or not set");
        return -1;
    }

    // needed variables
    int N;      // Number of memory references
    int Option;
    char * filetowrite; // name of file to write to
    // optional arguments
    bool n = false; // Number of memory references
    bool p = false; // print to file
    bool t = false; // show logical to phisical translation

    // getopt gets next argument option from argv and argc
    while ( (Option = getopt(argc, argv, "n:p:t")) != -1)
    {
        switch (Option)
        {
            case 'n': /* Number of addresses to process */
                n = true;
                N = atoi(optarg); // Number of memory references
                break;

            case 'p': /* produce map of pages */
                p = true;
                filetowrite = optarg; // file to write to
                break;

            case 't': /* Show address translation */
                t = true;
                break;
        }
    }

    // open trace file, 'r' read, optind++ to move to next index
    FILE * tracefile = fopen(argv[optind++], "rb"); // rb = read binary b/c this is not a text file

    // check that file opened successfully
    if (tracefile == NULL)
    {
		printf("Failed to open or find %s!\n", argv[optind-1]);
		return -2;
	}

    // allocate memory and populate page table structure with arguments
    createPageTable(argc, argv, optind);

    // Start reading and inserting addresses from trace file
    p2AddrTr trace_item; // not pointer
    unsigned int hit = 0;      // hit counter
    unsigned int miss = 0;      // miss counter
    unsigned int frames;
    int count = 0;
    while(!feof(tracefile)) // b/c byu uses fread()
    {
        // get next address
        NextAddress(tracefile, &trace_item);

        if(PageInsert(trace_item.addr, frames))
        {
            frames++;
        }
        else
        {
            hit++;
        }
        count++;

        // -t option handler
        if(t)
        {

        }

        // -n option handler
        if(count >= N && n) // if N memory addresses have been processed
        {
            printf("N break has been reached\n");
            break;
        }
    }

    // p option handler
    if(p)
    {
        if(!pHandler(filetowrite))
            return -3;
    }








    fclose(tracefile); // never forget to close opened files

    printf("THE END, count = %d\n", count);
    return 0;

    //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN
}   //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN
    //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN

// dump page table to file
bool pHandler(char * filetowrite)
{
    FILE * writefile = fopen(filetowrite, "w+"); // w = write

    // check that file opened successfully
    if (writefile == NULL)
    {
		printf("Failed to open or find %s!\n", filetowrite);
		return false;
	}

    int pagemax = 1 << pagetable->pagesize; // creates the max address that the page can be


    // makes
    int pageoffset = pagetable->ShiftArray[pagetable->levelCount - 1];

    printf("pageoffset = %d\n", pageoffset);

    int frameNumber;
    int logicalAddress;

    unsigned int bitMask = pagetable->BitmaskArray[depth];
    unsigned int shift = pageTablePtr->levelShiftArray[depth];
    unsigned int location = (logicalAddress & bitMask) >> shift;

    for (int i = 0; i < pagemax; i++) {

        logicalAddress = i << pageoffset; // creates page address to with respect to i
        // use pagenumber as logicalAddress to search

        frameNumber = pt->getFrameNumber(pageNumber);
        //Only print valid frames once
        if (frameNumber != INVALID)
        {
            if (!frameNumberOutputed[frameNumber])
            {
                // write to file
                fprintf(filePointer, "%08X -> %08X\n", i, frameNumber);
                frameNumberOutputed[frameNumber] = true;
            }
        }

    }



    //printf(filePointer, "%08X -> %08X\n", i, frameNumber);

    fclose(writefile);

    return true;
}


