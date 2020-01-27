/*
 * CS570
 * Carlos Gamino Reyes
 * 819230978
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// enables boolean
#include <string.h>		// string manipulation
#include <ctype.h>      // tolower()

#include "dictionary.h"   // my dictionary

//Global Variables


int main (int argc, char **argv)
{
    const char delimiters[256] = "\0\t\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

    // text to check
    FILE *fp1 = fopen(argv[1], "r");// 'r' is for read

    // dictionary
    FILE *fp2 = fopen(argv[2], "r");// 'r' is for read

    if (fp1 == NULL || fp2 == NULL)
    {
		printf("Failed to open or find file!\n");
		printf("argc = %d\n", argc);
        printf("fp1 = %s\n", argv[1]);
        printf("fp2 = %s\n", argv[2]);
		return 1;
	}
	printf("fp1 = %s\n", argv[1]);
    printf("fp2 = %s\n", argv[2]);

    // populate dictionary
    char str[512];
	char * tok = NULL;
	while(fgets(str, 512, (FILE*)fp2))
    {
        //printf("a");
        tok = strtok(str, delimiters);
        tok = strtok(tok,"\n");
        //printf("tok (%s)\n",tok);
        insert(tok);
	}
	fclose(fp2);// never forget to close the file

    // find token
	char str2[512];

	while(fgets(str2, 512, (FILE*)fp1))
    {
        tok = strtok(str2, delimiters);
        tok = strtok(tok, "\n");
        while (tok != NULL)
        {
            printf("tok = (%s)\n",tok);
            if(!find(tok)) printf("%s\n",tok);
            tok = strtok(NULL, delimiters);
            tok = strtok(tok, "\n");
        }
	}
	fclose(fp1);// never forget to close the file

    return 0;
}
