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
    char * filetoread;  // name of file to read from
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

    // get name of file to read from
    filetoread = argv[optind++]; // ++ moves the index to the next argument

    // open trace file
    FILE * tracefile = fopen(filetoread, "rb"); // 'rb' read binary

    // check that file opened successfully
    if (tracefile == NULL)
    {
		printf("Failed to open or find %s!\n", filetoread);
		return -2;
	}

    printf("reading = %s\n", argv[optind]);
    printf("index = %d\n", optind);
    printf("number of arguments = %d\n", argc);

    

    // get number of levels and number of bits per page
    int levelCount =  argc - optind;    // number of levels in tree
    printf("level = %d\n", levelCount);
    int bitsperpage[levelCount];
    int bitcount = 0;



    // allocate memory for root page table
    rootPageTable = malloc(sizeof(struct PAGETABLE)); // rootPageTable is global variable
    rootPageTable->levelCount = levelCount;
    rootPageTable->BitmaskArray = malloc(sizeof(levelCount));

    


    for(int i = 0; optind < argc; i++, optind++)
    {
        bitcount += bitsperpage[i] = atoi(argv[optind]);
    }

 
    fclose(tracefile); // never forget to close opened files
    return 0;
}



//  LogicalAddress to page number
unsigned int LogicalToPage
    (unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift;
}

/*
// Used to add new entries to the page table when we have discovered that 
// a page has not yet been allocated
void PageInsert
    (PageTable pagetable, unsigned int LogicalAddress, unsigned int Frame)
{

}
*/
