/*
 * CS570, spring 2020
 *
 * pagetable.c
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#include "pagetable.h"

struct MAP * PageLookup(unsigned int LogicalAddress)
{
    return malloc(sizeof(struct MAP));
}

bool PageInsert(unsigned int LogicalAddress, unsigned int Frame)
{
    return insertLVL(LogicalAddress, Frame); // sent to sinrt in level file and return value
}

// allocate memory and populate page table structure
void createPageTable(int argc, char ** argv, int optind)
{
    // get number of levels and number of bits per page
    int levelCount =  argc - optind;    // number of levels in tree
    printf("number of levels = %d\n", levelCount);
    int bitsPerLevel[levelCount]; // 8 8 8 argument in int not bin

    unsigned int offset = 32;
    // populate bitsPerLevel and offset
    for (int i = 0; optind < argc; i++) {
        offset -= bitsPerLevel[i] = atoi(argv[optind++]);
    }

    printf("offset = %u\n", offset);
    printf("pagesize = %u\n", 32 - offset);

    // allocate memory for root page table
    pagetable = malloc(sizeof(struct PAGETABLE)); // pagetable is global variable

    pagetable->pagesize = 32 - offset;
    pagetable->levelCount = levelCount;

    // the  +1  is to make space for the offset values
    pagetable->BitmaskArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->ShiftArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->EntryCount = malloc(sizeof(int) * (levelCount +1));


    // entering offset at level count - START
    pagetable->BitmaskArray[levelCount] = (unsigned int) ((1 << offset) - 1);
    pagetable->ShiftArray[levelCount] = 0; // no shifting needed for offset
    //size of each array
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

    pagetable->RootLevelPtr = NULL;
}
