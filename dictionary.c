/*
 * CS570
 * Carlos Gamino 
 * 819230978
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// enambles boolean
#include <string.h>		// string manipulation

#define Nchars 27 /* a-z + ' */
typedef struct dictentry
{
	// isEndOfWord is true if the node represents end of a word
	bool isEndOfWord;
	// Subsequent characters in words. Null pointers if there
	// are no further words with the next letter.
	struct dictentry *next[Nchars];
}

int main(){
	while(!quit){
		
		// waiting for string
		char str[] = " af sd ";
		char * str = readline(">");
		
		// parse string
		parse(str);

		// print linked list
		printAll();
		
		// clear linked list
		clear();
	}
	return 0;
}
