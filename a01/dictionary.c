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
//  DO NOT MESS AROUND WITH ORIGINAL STRING USE A POINTER

#define Nchars 27 /* a-z + ' 0-25 + 26*/

struct dictEntry{
	bool isEndOfWord;// isEndOfWord is true if the node represents end of a word
	struct dictEntry *next[Nchars];// make all null if end of word is true
};

// this enables us to just say "dict" instead of "struct dictEntry"
typedef struct dictEntry * dict; // dict is pointer

// Global variables
dict root = NULL;

// method to help debug;
void pprint(char *ptr){
    // print character of pointer
    printf("ptr (chr) -> (%c)\n",*ptr);
    // print decimal value of character
    printf("ptr (dec) -> %d\n",*ptr);
    // print pointer location address
    printf("ptr (adr) -> %p\n\n",ptr);
}

// make lowercase and convert to range 0 - 26
int tokToInt(char * tok){

    //printf("tok = (%c), dec = %d, ",*tok, *tok);

    // if A - Z, make lowercase
    if(*tok > 64 && *tok < 91) *tok = tolower(*tok);
    // if tok is not a lower case letter or a '
    if((*tok < 'a' || *tok > 'z') && *tok != '\''){
        printf("\nError on tokToInt method\n");
        pprint(tok);
    }
    // if ' char, return 26
    if(*tok == '\'') return 26;
    //convert *tok letter char to int from 0 to 25
    int tok_int = (int)*tok - 97;

    //printf("tok_int = %d\n",tok_int);

    return tok_int;
}

// insert word
void insert(char * str){
    //printf("inserting (%s)\n", str);

    // create root node and allocate memory
    if (root == NULL){
        //printf("****rood is created****\n");
        root = malloc(sizeof(struct dictEntry));// allocate memory for new node
        for(int i = 0; i < 27; i++)
            root->next[i] = NULL;    // set all possible children to NULL
        root -> isEndOfWord = false;  // root is never end of word
    }

    char * tok = str; // do not mess around with original string, use pointer
    dict ptr = root; // remember, never mess around with the root

    for(int i = 0; i < strlen(str); i++){

        //printf("iteration %d\n",i);

        // make lowercase and convert
        int tok_int = tokToInt(tok);
        //printf("tok = %c, int = (%d)\n",*tok,tok_int);

        //printf("A\n");

        // if ptr->next is NULL, create new dictEntry
        if (ptr->next[tok_int] == NULL){
            ptr->next[tok_int] = malloc(sizeof(struct dictEntry));// allocate memory for new node
            dict tmp = ptr->next[tok_int];
            for(int j = 0; j < 27; j++)
                tmp->next[j] = NULL;// make all NULL
            tmp->isEndOfWord = false;
            //printf("next node end is set to true\n");
        }

        //printf("B\n");

        //ptr->isEndOfWord = false; // ptr node is no longer end, set to true
        ptr = ptr->next[tok_int]; // move pointer to next location

        //printf("C\n");

        tok++;  // go to next character in token
    }
    ptr->isEndOfWord = true; // ptr node is no longer end, set to true
}

bool find (char * str){
    if(root == NULL) return false;
    char * tok = str; // do not mess around with original string, use pointer
    dict ptr = root; // remember, never mess around with the root

    for(int i = 0; i < strlen(str); i++){
        //printf("iteration %d, cheking for %c\n",i,*tok);

        int tok_int = tokToInt(tok); // convert tok to int
        if(ptr->next[tok_int] == NULL){
            //printf("exit find\n");
            return false;
        }

        ptr = ptr->next[tok_int]; // move pointer to next location
        tok++;
    }
    return (ptr->isEndOfWord) ? true : false;
}

/************** dictionary tree ends here **************/
/*
void test (){
    int i;
    printf("\n*****testing*****\n");
    printf("root address %p\n", root);
    printf("root end of word %s\n\n",(root->isEndOfWord) ? "true" : "false");

    // b = 1
    i = 1;
    if(root->next[i] == NULL) printf("root next[%d] = NULL\n",i);
    dict ptr = root->next[i];
    printf("ptr address %p\n", ptr);
    printf("ptr end of word %s\n\n",(ptr->isEndOfWord) ? "true" : "false");

    // a = 0
    i = 0;
    if(ptr->next[i] == NULL) printf("ptr next[%d] = NULL\n",i);
    dict ptr2 = ptr->next[i];
    printf("ptr2 address %p\n", ptr2);
    printf("ptr2 end of word %s\n\n",(ptr2->isEndOfWord) ? "true" : "false");

    // t = 19
    i = 19;
    if(ptr2->next[i] == NULL) printf("ptr2 next[%d] = NULL\n",i);
    dict ptr3 = ptr2->next[i];
    printf("ptr3 address %p\n", ptr3);
    printf("ptr3 end of word %s\n\n",(ptr3->isEndOfWord) ? "true" : "false");

    // c = 2
    i = 2;
    if(ptr3->next[i] == NULL) printf("ptr3 next[%d] = NULL\n",i);
    dict ptr4 = ptr3->next[i];
    printf("ptr4 address %p\n", ptr4);
    printf("ptr4 end of word %s\n\n",(ptr4->isEndOfWord) ? "true" : "false");

    // h = 7
    i = 7;
    if(ptr4->next[i] == NULL) printf("ptr4 next[%d] = NULL\n",i);
    dict ptr5 = ptr4->next[i];
    printf("ptr5 address %p\n", ptr5);
    printf("ptr5 end of word %s\n",(ptr5->isEndOfWord) ? "true" : "false");
    printf("*****testing*****\n\n");
}

int main(){

    char buff[] = "batch bat";

    // inserting
    char * tok = strtok(buff," ");
    while (tok != NULL){
        printf("inserting %s\n", tok);
        insert(tok);
        tok = strtok(NULL," ");
	}

	test();

	// find
	char buff2[] = " ba bat batc batch batcha";
	printf(" string to find = %s\n", buff2);
	tok = strtok(buff2," ");
    while (tok != NULL){
        printf("finding %s\n", tok);
        if(find(tok)) printf("tok: %s, was found\n", tok);
        else printf("tok: %s, was NOT found\n", tok);
        tok = strtok(NULL," ");
	}

	return 0;
}
*/
