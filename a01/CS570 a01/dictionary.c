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

// make lowercase and convert to range 0 - 26
int tokToInt(char * tok){
    // if A - Z, make lowercase
    if(*tok > 64 && *tok < 91) *tok = tolower(*tok);
    // if tok is not a lower case letter
    if((*tok < 'a' || *tok > 'z') && *tok != '\'')
        printf("\nError on tokToInt method, tok = %c\n",*tok);
    // if ' char, make 26
    if(*tok == '\'') *tok = 26;
    //convert *tok letter char to int from 0 to 26
    int tok_int = (int)*tok - 97;

    return tok_int;
}

// insert word
void insert(char * str){
    // create root node and allocate memory
    if (root == NULL){
        printf("****rood is created****\n");
        root = malloc(sizeof(struct dictEntry));// allocate memory for new node
        for(int i = 0; i < 27; i++)
            root->next[i] = NULL;    // set all possible children to NULL
        root -> isEndOfWord = true;  // declare end
    }

    char * tok = str; // do not mess around with original string, use pointer
    dict ptr = root; // remember, never mess around with the root

    for(int i = 0; i < strlen(str); i++){

        printf("iteration %d\n",i);

        // make lowercase and convert
        int tok_int = tokToInt(tok);
        //printf("tok = %c, int = (%d)\n",*tok,tok_int);

        //printf("A\n");

        // if ptr->next is NULL
        if (ptr->next[tok_int] == NULL){
            ptr->next[tok_int] = malloc(sizeof(struct dictEntry));// allocate memory for new node
            dict tmp = ptr->next[tok_int];
            for(int j = 0; j < 27; j++)
                tmp->next[j] = NULL;// make all NULL
            tmp->isEndOfWord = true;
            //printf("next node end is set to true\n");
        }

        //printf("B\n");

        ptr->isEndOfWord = false; // ptr node is no longer end, set to true
        ptr = ptr->next[tok_int]; // move pointer to next location

        //printf("C\n");

        tok++;  // go to next character in token
    }
}

bool find (char * str){
    if(root == NULL) return false;
    char * tok = str; // do not mess around with original string, use pointer
    dict ptr = root; // remember, never mess around with the root

    for(int i = 0; i < strlen(str); i++){
        printf("iteration %d, cheking for %c\n",i,*tok);

        int tok_int = tokToInt(tok); // convert tok to int
        if(ptr->next[tok_int] == NULL){
            printf("exit find\n");
            return false;
        }

        ptr = ptr->next[tok_int]; // move pointer to next location
        tok++;
    }
    return true;
}

/************** dictionary tree ends here **************/
/*
void test (){
    printf("\n*****testing*****\n");
    printf("root address %p\n", root);
    printf("root end of word %s\n",(root->isEndOfWord) ? "true" : "false");
    if(root->next[0] == NULL) printf("root next[0] = NULL\n");

    dict ptr = root->next[0];
    printf("ptr address %p\n", ptr);
    printf("ptr end of word %s\n",(ptr->isEndOfWord) ? "true" : "false");
    if(ptr->next[0] == NULL) printf("ptr next[0] = NULL\n");

    dict ptr2 = root->next[0]->next[0];
    printf("ptr2 address %p\n", ptr2);
    printf("ptr2 end of word %s\n",(ptr2->isEndOfWord) ? "true" : "false");
    if(ptr2->next[0] == NULL) printf("ptr2 next[0] = NULL\n");
    printf("*****testing*****\n\n");
}

int main(){

    char buff[] = "Boy cOy";
    //char buff[256] = "aaa";

    // inserting
    char * tok = strtok(buff," ");
    while (tok != NULL){
        printf("inserting %s\n", tok);
        insert(tok);
        tok = strtok(NULL," ");
	}


	//test();

	// find
	char buff2[] = "cOY bOy";
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

/*
questions and to do list:







*/
