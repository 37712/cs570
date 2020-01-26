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

#define Nchars 27 /* a-z + ' 0-25 + 26*/

struct dictEntry{
	// isEndOfWord is true if the node represents end of a word
	bool isEndOfWord;
	// Subsequent characters in words. Null pointers if there
	// are no further words with the next letter.
	struct dictEntry *next[Nchars];
};

// this enables us to just say "dict" instead of "struct dictEntry"
typedef struct dictEntry * dict; // dict is pointer

// Global variables
dict root = NULL;

// make lowercase and convert to range 0 - 26
int tokToInt(char * tok){
    // make lowercase
    if(*tok > 64 && *tok < 91) *tok = tolower(*tok);
    // if tok is not a lower case letter
    if(*tok < 'a' || *tok > 'z') printf("\nError, tok = %c\n",*tok);
    //convert *tok letter char to int from 0 to 25
    int tok_int = (int)*tok - 97;

    return tok_int;
}

// insert word
void insert(char * str){
    dict ptr = root;
    char * tok = str;
    // create root node and allocate memory
    if (ptr == NULL){
        ptr = malloc(sizeof(struct dictEntry));// allocate memory for new node
        for(int i = 0; i < 27; i++)
            ptr->next[i] = NULL;    // set all possible children to NULL
        ptr -> isEndOfWord = true;  // declare end
    }
    for(int i = 0; i < strlen(str); i++){

        printf("iteration %d\n",i);

        // make lowercase and convert
        int tok_int = tokToInt(tok);
        printf("tok = %c, int = (%d)\n",*tok,tok_int);

        printf("A\n");

        // if ptr->next is NULL
        if (ptr->next[tok_int] == NULL){
            ptr->next[tok_int] = malloc(sizeof(struct dictEntry));// allocate memory for new node
            dict tmp = ptr->next[tok_int];
            for(int i = 0; i < 27; i++)
                tmp->next[i] = NULL;
            tmp->isEndOfWord = true;
        }

        printf("B\n");

        ptr->isEndOfWord = false; // ptr node is no longer end
        ptr = ptr->next[tok_int]; // move pointer to next location

        printf("C\n");

        tok++;  // go to next token character

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

/*
questions and todo list:

is char ' an aceptable char to store?








*/
