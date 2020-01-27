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
    const char delimiters[] = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

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

    printf("*********POPULATING***********\n");

    // populate dictionary
    char str[512];
	char * tok = NULL;
	while(fgets(str, 512, (FILE*)fp2))
    {
        //printf("a");
        tok = strtok(str, delimiters);
        //tok = strtok(tok,"\n");
        //printf("tok (%s)\n",tok);
        insert(tok);
	}

    printf("*********FINDING***********\n");

    // find token
	char str2[512];
    char tmp[128];
	while(fgets(str2, 512, (FILE*)fp1))
    {
        //printf("_str = (%s)\n",str2);
        tok = strtok(str2, delimiters);
        //printf("Atok = (%s)\n",tok);
        //tok = strtok(tok, "\n");
        //printf("Btok = (%s)\n",tok);
        while (tok != NULL)
        {
            //printf("find(%s)\n",tok);
            strcpy (tmp,tok);// do not modify original string
            if(!find(tmp)) printf("%s\n",tok);
            tok = strtok(NULL, delimiters);
        }
	}

	// never forget to close the file
	fclose(fp2);
	fclose(fp1);

    return 0;
}
