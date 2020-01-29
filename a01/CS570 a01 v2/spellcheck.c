/*
 * spellcheck.c
 *
 * CS570, spring 2020
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // enables boolean
#include <string.h>		// string manipulation
#include <ctype.h>      // tolower()

#include "dictionary.h"   // my dictionary

int main (int argc, char **argv)
{
    if(argc != 3) // check if arguments are wrong or not set
    {
        printf("failed to specify arguments");
        return -1;
    }

    // open text to spellcheck
    FILE *fp1 = fopen(argv[1], "r");// 'r' is for read

    // open dictionary
    FILE *fp2 = fopen(argv[2], "r");// 'r' is for read

    // check that both files opened successfully
    if (fp1 == NULL || fp2 == NULL)
    {
		printf("Failed to open or find file!\n");
		return -2;
	}

	//delimiter for strtok
    const char delimiters[] = "\t\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

    // populate dictionary
    char str[512];
	char * tok = NULL;
	while(fgets(str, 512, (FILE*)fp2))
    {
        tok = strtok(str, delimiters);
        if(!insert(tok)) // if failed to insert end program
        {
            printf("failed to insert (%s)\n", tok);
            return -3;
        }
	}

    // find token
	char str2[512];
    char tmp[128];
	while(fgets(str2, 512, (FILE*)fp1))
    {
        tok = strtok(str2, delimiters);
        while (tok != NULL)
        {
            strcpy (tmp,tok); // do not modify original token string
            if(!find(tmp)) printf("%s\n",tok);// if not found, print to stdout
            tok = strtok(NULL, delimiters);
        }
	}

	// never forget to close opened files
	fclose(fp2);
	fclose(fp1);

    return 0;
}
