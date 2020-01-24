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
    while(str != 0){
        if (ptr == NULL){
            ptr = malloc(sizeof(dict));// allocates memory for new node
            ptr -> isEndOfWord = false;
        }
        ptr = ptr->next[]// need to make to lowercase and conversion
        str++;
    }

}



/************** dictionary tree ends here **************/

int main(){
    char str[] = {"bat batch boy coy"};
    char * ptr = strtok(str," ");
    while (ptr != NULL && i<10){
        printf("inserting %s\n", ptr);
        insert(ptr);
        ptr = strtok(NULL," ");
	}

	return 0;
}
