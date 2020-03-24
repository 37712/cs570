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

// get size of all levels, including map level
int levelsize(Level ptr, int depth)
{
    // if ptr is at map level
    if(ptr->NextLevelPtr == NULL)
    {
        return sizeof(struct LEVEL) + sizeof(struct MAP) +
                (sizeof(int) * pagetable->EntryCount[pagetable->levelCount -1]);
    }
    int bytes = sizeof(struct LEVEL);
    for (int i = 0; i < pagetable->EntryCount[depth]; i++)
        if(ptr->NextLevelPtr[i] != NULL)
            bytes += levelsize(ptr->NextLevelPtr[i], depth+1);
    return bytes;
}

// used for the final summary
int sizeofpagetable()
{
    int bytes = sizeof(struct PAGETABLE);
    Level ptr = pagetable->RootLevelPtr;
    bytes += levelsize(ptr, 0);
    return bytes;
}





// given a logical address return the frame
int PageLookup(unsigned int LogicalAddress)
{
    Level ptr = pagetable->RootLevelPtr; // don't mess with root, use pointer
    unsigned int bitMask;
    unsigned int shift;
    unsigned int levelindex;
    int depth;
    //traversing the level structure
    for(depth = 0; depth < pagetable->levelCount - 1; depth++)
    {
        // get index for current depth
        bitMask = pagetable->BitmaskArray[depth];
        shift = pagetable->ShiftArray[depth];
        levelindex = (LogicalAddress & bitMask) >> shift; // index for next level

        // move ptr to next level if not NULL
        if(ptr->NextLevelPtr[levelindex] != NULL)
        {
            ptr = ptr->NextLevelPtr[levelindex];
        }
    }

    // ptr is now at map level
    bitMask = pagetable->BitmaskArray[depth];
    shift = pagetable->ShiftArray[depth];
    levelindex = (LogicalAddress & bitMask) >> shift; // index for map array

    return getframe(ptr->MapPtr, levelindex);
}

bool PageInsert(unsigned int LogicalAddress, int frame)
{
    return insertLVL(LogicalAddress, frame); // sent to insert in level file and return value
}

// allocate memory and populate page table structure
void createPageTable(int argc, char ** argv, int optind)
{
    // get number of levels and number of bits per page
    int levelCount =  argc - optind;    // number of levels in tree
    int bitsPerLevel[levelCount]; // 8 8 8 argument in int not bin

    unsigned int offset = 32;
    // populate bitsPerLevel and offset
    for (int i = 0; optind < argc; i++) {
        offset -= bitsPerLevel[i] = atoi(argv[optind++]);
    }

    // allocate memory for root page table
    pagetable = malloc(sizeof(struct PAGETABLE)); // pagetable is global variable

    // number bits for entire page address
    pagetable->pagesize = 32 - offset;

    // number of levels
    pagetable->levelCount = levelCount;

    // +1 to make space for the offset entries
    pagetable->BitmaskArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->ShiftArray = malloc(sizeof(int) * (levelCount +1));
    pagetable->EntryCount = malloc(sizeof(int) * (levelCount +1));


    // entering offset at last position in array
    pagetable->BitmaskArray[levelCount] = (unsigned int) ((1 << offset) - 1);
    pagetable->ShiftArray[levelCount] = 0; // no shifting needed for offset
    pagetable->EntryCount[levelCount] = (unsigned int) (1 << offset);

    // populating pagetable arrays
    unsigned int BitCount = offset;
    unsigned int bitMask;
    for (int i = levelCount - 1; i >= 0; i--)
    {
        // this make the FF value for the bitmarc array
        bitMask = (unsigned int) (1 << bitsPerLevel[i]) - 1; // 100 - 1 = FF
        // this shifts the FF value
        pagetable->BitmaskArray[i] = bitMask << BitCount;
        // number of bits to shift per level
        pagetable->ShiftArray[i] = BitCount;
        // size of array for each level
        pagetable->EntryCount[i] = (unsigned int) 1 << bitsPerLevel[i]; // this is the 2 ^ bits per level
        BitCount += bitsPerLevel[i];
    }
    // start the root level as null
    pagetable->RootLevelPtr = NULL;
}
