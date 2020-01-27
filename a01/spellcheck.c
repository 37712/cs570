/*
 * spellcheck.c
 *
 * CS570
 * Carlos Gamino Reyes
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
    if(argc < 3)
    {
        printf("failed to specify argumetns");
        return -1;
    }

    //delimiter for strtok
    const char delimiters[] = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

    // text to check
    FILE *fp1 = fopen(argv[1], "r");// 'r' is for read

    // dictionary
    FILE *fp2 = fopen(argv[2], "r");// 'r' is for read

    if (fp1 == NULL || fp2 == NULL)
    {
		printf("Failed to open or find file!\n");
		return -2;
	}

    // populate dictionary
    char str[512];
	char * tok = NULL;
	while(fgets(str, 512, (FILE*)fp2))
    {
        tok = strtok(str, delimiters);
        insert(tok);
	}

    // find token
	char str2[512];
    char tmp[128];
	while(fgets(str2, 512, (FILE*)fp1))
    {
        tok = strtok(str2, delimiters);
        while (tok != NULL)
        {
            strcpy (tmp,tok);// do not modify original string
            if(!find(tmp)) printf("%s\n",tok);// if not found, print to stdout
            tok = strtok(NULL, delimiters);
        }
	}

	// never forget to close the file
	fclose(fp2);
	fclose(fp1);

    return 0;
}
