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
#include <unistd.h>     // needed for getopt
#include <stdbool.h>    // needed for bool

#include "pagetable.h"
#include "byutr.h"

/*
 *  IMPORTANT:
 *  OPTIONAL ARGUMENTS LIKE -n -p -t
 *  MUST COME FIRST WHEN RUNNING THE EXE
 */

//  LogicalAddress to page number
unsigned int LogicalToPage
    (unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift);

// allocate memory for the structure and populate page table
void createPageTable(int argc, char ** argv);

//Inserts into Page Table, returns Hit/Miss
bool pageInsert(unsigned int logicalAddr, unsigned int frame);

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
    FILE * tracefile = fopen(argv[optind++], "r");

    // check that file opened successfully
    if (tracefile == NULL)
    {
		printf("Failed to open or find %s!\n", optind-1);
		return -2;
	}

    printf("number of arguments = %d\n", argc);
    printf("index = %d\n", optind);
    printf("reading = %s\n", argv[optind]);



    // allocate memory and populate page table structure with arguments
    createPageTable(argc, argv); // optid is global variable
    
    // Start reading addresses from trace file
    p2AddrTr trace_item;
    bool done = false;
    unsigned int hits = 0;      //??????
    unsigned int misses = 0;    //??????

    // testing
    NextAddress(tracefile, &trace_item);
    pageInsert(trace_item.addr, hits++);

    /*
    while (! done)
    {
        if(NextAddress(tracefile, &trace_item)) // fails if NextAddress returns 0
        {
            printf("Address %x\n", trace_item.addr);
            if(pageInsert(trace_item.addr, ))
            {

            }

        }
        
    }
    */
    

    

 
    fclose(tracefile); // never forget to close opened files
    return 0;

    //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN
}   //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN
    //  END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN, END OF MAIN

bool pageInsert(unsigned int logicalAddr, unsigned int frame)
{
    if(insertPT(logicalAddr, frame)) return true;
    return false;
}

//  LogicalAddress to page number
unsigned int LogicalToPage
    (unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift;
}

// allocate memory and populate page table structure
void createPageTable(int argc, char ** argv)
{
    

    // get number of levels and number of bits per page
    int levelCount =  argc - optind;    // number of levels in tree
    printf("number of levels = %d\n", levelCount);
    int bitsPerLevel[levelCount]; // 8 8 8 argument in int not bin
    int addressSizeUsed = 0; // counts the total number of bits used for pages
    
    unsigned int offset = 32; // need to subtract by bits per level
    
    // populate pageTableSizes array and set offset
    for (int i = 0; optind < argc; i++) {
        offset -= bitsPerLevel[i] = atoi(argv[optind++]);
    }

    printf("offset = %u\n", offset);
    printf("pagebits = %u\n", 32 - offset);
    
    // allocate memory for root page table
    pagetable = malloc(sizeof(struct PAGETABLE)); // pagetable is global variable

    
    
    pagetable->levelCount = levelCount;
    
    // the  +1  is to make space for the offset
    pagetable->BitmaskArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->ShiftArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->EntryCount = malloc(sizeof(int) * (levelCount +1));

    
    // entering offset at level count - START
    //[Level Count] matches with the offset bits
    pagetable->BitmaskArray[levelCount] = (unsigned int) ((1 << offset) - 1);
    pagetable->ShiftArray[levelCount] = 0; // no shifting needed for offset
    //Page Size
    pagetable->EntryCount[levelCount] = (unsigned int) (1 << offset);
    // entering offset at level count - END

    
    unsigned int cumulativeBitCount = offset;
    unsigned int bitMask;
    for (int i = levelCount - 1; i >= 0; i--)
    {
        bitMask = (unsigned int) (1 << bitsPerLevel[i]) - 1; // this make the FF
        
        pagetable->BitmaskArray[i] = bitMask << cumulativeBitCount; // shifts the FF
        pagetable->ShiftArray[i] = cumulativeBitCount;
        pagetable->EntryCount[i] = (unsigned int) 1 << bitsPerLevel[i]; // same as 2 ^ number of bits
        printf("entrycount = %u, %x\n",pagetable->EntryCount[i],pagetable->EntryCount[i]);
        cumulativeBitCount += bitsPerLevel[i];
    }

    // allocate memory and set varibales for RootLevelPtr
    pagetable->RootLevelPtr = malloc(sizeof(struct LEVEL));
    pagetable->RootLevelPtr->depth = 0;
    pagetable->RootLevelPtr->NextLevelPtr = malloc(sizeof(struct LEVEL) * pagetable->EntryCount[0]);
    pagetable->RootLevelPtr->MapPtr = NULL;
    // make all entries NULL at start
    for(int j = 0; j < pagetable->EntryCount[0]; j++)
        pagetable->RootLevelPtr->NextLevelPtr[j] = NULL;
}





