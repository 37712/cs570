/*
 * dictionary.c
 *
 * CS570, spring 2020
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
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
//  DO NOT MESS AROUND WITH ORIGINAL STRING USE A POINTER

#define Nchars 27 /* a-z + ' 0-25 + 26 */

struct dictEntry
{
	bool isEndOfWord;// isEndOfWord is true if the node represents the end of a word
	struct dictEntry *next[Nchars];// make all null if end of word is true
};

// this enables us to just say "dict" instead of "struct dictEntry"
typedef struct dictEntry * dict; // also, dict is pointer type

// Global variables
dict root = NULL;

// method to help debug;
void pprint(char *ptr)
{
    // print character of pointer
    printf("ptr (chr) -> (%c)\n",*ptr);
    // print decimal value of character
    printf("ptr (dec) -> (%d)\n",*ptr);
    // print pointer location address
    printf("ptr (adr) -> (%p)\n\n",ptr);
}

// make lowercase and convert to range 0 - 26
int tokToInt(char * tok)
{
    // if A - Z, make lowercase
    if(*tok > 64 && *tok < 91) *tok = tolower(*tok);
    // if tok is not a lower case letter or a '
    if((*tok < 'a' || *tok > 'z') && *tok != '\'')
    {
        perror("\nError on tokToInt method\n");
        pprint(tok);
        return -1; // return error = -1
    }
    // if ' char, return 26
    if(*tok == '\'') return 26;
    //convert *tok letter char to int from 0 to 25
    return (int)*tok - 97;
}

// insert word
bool insert(char * str)
{
    // create root node and allocate memory
    if (root == NULL)
    {
        root = malloc(sizeof(struct dictEntry)); // allocate memory for root node
        for(int i = 0; i < 27; i++) root->next[i] = NULL; // set all children to NULL
        root -> isEndOfWord = false; // root is never end of word
    }

    char * tok = str; // do not mess around with original string, use pointer
    dict ptr = root; // remember, never mess around with the root

    for(int i = 0; i < strlen(str); i++)
    {
        // make lowercase and convert
        int tok_int = tokToInt(tok);

        // if tokToInt method returns error
        if(tok_int == -1) return false;

        // if ptr->next is NULL, create new dictEntry
        if (ptr->next[tok_int] == NULL)
        {
            ptr->next[tok_int] = malloc(sizeof(struct dictEntry));// allocate memory for new node
            dict tmp = ptr->next[tok_int];
            for(int j = 0; j < 27; j++) tmp->next[j] = NULL;// set all children to NULL
            tmp->isEndOfWord = false;
        }

        ptr = ptr->next[tok_int]; // move pointer to next location
        tok++;  // go to next character in token
    }

    ptr->isEndOfWord = true; // ptr node is end of word, set to true
    return true;
}

// find word
bool find (char * str){
    if(root == NULL) return false; // if root has yet to be created
    dict ptr = root; // remember, never mess around with the root
    char * tok = str; // do not mess around with original string, use pointer

    for(int i = 0; i < strlen(str); i++)
    {
        int tok_int = tokToInt(tok); // convert tok to int

        // if tokToInt method returns error
        if(tok_int == -1) return false;

        if(ptr->next[tok_int] == NULL)return false;
        ptr = ptr->next[tok_int]; // move pointer to next location
        tok++; // go to next character in token
    }
    // reached end of tok, check to see if word exists
    return (ptr->isEndOfWord) ? true : false;
}

/************** dictionary tree ends here **************/
