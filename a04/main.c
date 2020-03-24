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
#include <getopt.h>

#include "pagetable.h"
#include "byutr.h"

/*
 *  IMPORTANT:
 *  OPTIONAL ARGUMENTS LIKE -n -p -t
 *  MUST COME FIRST WHEN RUNNING THE EXE
 */

bool pHandler(char * writefile);

bool tHandler(unsigned int LogicalAddress);

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
    int Option; // option value index
    char * writefile; // name of file to write to
    // option arguments
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
                writefile = optarg; // file to write to
                break;

            case 't': /* Show address translation */
                t = true;
                break;
        }
    }

    // open trace file, 'rb' read binary, optind++ to move to next index
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
    int hit = 0;      // hit counter
    int frame = 0;
    int count = 0;  // counts num
    while(!feof(tracefile)) // b/c byu uses fread()
    {
        // get next address
        NextAddress(tracefile, &trace_item);

        if(PageInsert(trace_item.addr, frame))
        {
            frame++; // same as miss
        }
        else
        {
            hit++;
        }
        count++;

        // -t option handler
        if(t)
        {
            // print physical address translation
            tHandler(trace_item.addr);
        }

        // -n option handler
        if(n && count >= N) // if -n N memory addresses have been processed
            break;

    } // end insertion

    // p option handler
    if(p && !pHandler(writefile)) return -3;

    //summary
    printf("Page size: %u\n", pagetable->EntryCount[pagetable->levelCount]);
    printf("Hits %d (%.2f%%)", hit, (float)hit/count * 100);
    printf(", Misses %d (%.2f%%)", count - hit, (float)(count - hit)/count * 100);
    printf(" # Addresses %d\n", count);
    printf("Bytes used: %d\n", sizeofpagetable());

    // never forget to close opened files
    fclose(tracefile);
    return 0;
}

// -t, print logical and physical address translation.
bool tHandler(unsigned int LogicalAddress)
{
    // get the actual frame, not map table
    int frame = PageLookup(LogicalAddress);

    // frame + offset = physical address
    // creates the frame
    int physicalAddress = frame * pagetable->EntryCount[pagetable->levelCount];
    // creates the offset
    physicalAddress += LogicalAddress & pagetable->BitmaskArray[pagetable->levelCount];

    printf("%08X -> %08X\n", LogicalAddress, physicalAddress);
    return true;
}

// -p, dump page table to file
bool pHandler(char * filetowrite)
{
    FILE * writefile = fopen(filetowrite, "w+"); // w = write

    // check that file opened successfully
    if (writefile == NULL)
    {
		printf("Failed to open or find %s!\n", filetowrite);
		return false;
	}

    // max address value of page address
    int pagemax = 1 << pagetable->pagesize;

    // makes offset
    int offset = pagetable->ShiftArray[pagetable->levelCount - 1];
    bool skip = false;
    int frame;
    int depth;
    unsigned int address;
    unsigned int bitMask;
    unsigned int shift;
    unsigned int levelindex;
    Level ptr; // pointer to traverse the page table structure
    for (int i = 0; i < pagemax; i++)
    {
        skip = false; // reset skip
        ptr = pagetable->RootLevelPtr; // reset pointer
        address = i << offset; // creates address

        //traversing the level structure
        for(depth = 0; depth < pagetable->levelCount - 1; depth++)
        {
            // get index for current depth
            bitMask = pagetable->BitmaskArray[depth];
            shift = pagetable->ShiftArray[depth];
            levelindex = (address & bitMask) >> shift; // index for next level

            // move ptr to next level if not NULL
            if(ptr->NextLevelPtr[levelindex] != NULL)
            {
                ptr = ptr->NextLevelPtr[levelindex];
            }
            else
            {
                skip = true;
                break;
            }
        }

        // if it ptr is null, skip current address
        if (skip) continue;

        // pointer is now pointing to last level

        bitMask = pagetable->BitmaskArray[depth];
        shift = pagetable->ShiftArray[depth];
        levelindex = (address & bitMask) >> shift; // index for map array

        frame = getframe(ptr->MapPtr, levelindex);

        // if frame is valid, write to file
        if(frame >= 0) fprintf(writefile, "%08X -> %08X\n", i, frame);
    }

    fclose(writefile); // never forget to close opened files
    return true;
}
