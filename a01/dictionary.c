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

/************** dictionary tree starts here **************/

//	Note to self:
//	DO NOT MESS AROUND WITH THE ROOT USE A POINTER
//  DO NOT FORGET TO MAKE BOOL TRUE OR FALSE

#define Nchars 27 /* a-z + ' */

struct dictEntry{
	// isEndOfWord is true if the node represents end of a word
	bool isEndOfWord;
	// Subsequent characters in words. Null pointers if there
	// are no further words with the next letter.
	struct dictEntry *next[Nchars];
};

// this enables us to just say "dict" instead of "struct dictEntry"
typedef struct dictEntry * dict;

// Global variables
dict root = NULL;

// insert word
void insert(char * str){
    dict ptr = root;
    char * tok = str;
    for(int i = 0; i < strlen(str); i++){

        // to lowercase
        if(*tok > 64 && *tok < 91) *tok = tolower(*tok);

        printf("======level %d (%c)======\n",i,*tok);

        if (ptr == NULL){
            ptr = malloc(sizeof(dict));// allocates memory for new node
            ptr -> isEndOfWord = false;
        }

        printf("A");

        ptr = ptr->next[*tok];// need to make to lowercase and conversion
        printf("B");
        tok++;
        printf("C\n");
    }
    // if last child is null, then it is end of word
    if (ptr == NULL){
        ptr = malloc(sizeof(dict));// allocates memory for new node
        ptr -> isEndOfWord = true;
    }

}



/************** dictionary tree ends here **************/


int main(){
    char buff[] = {"Boy cOy"};
    char * tok = strtok(buff," ");
    while (tok != NULL){
        printf("inserting %s\n", tok);
        insert(tok);
        tok = strtok(NULL," ");
	}

	return 0;
}
