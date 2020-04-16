/*
 * CS570, spring 2020
 *
 * main.c
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
 */

#include "belt.h"

/* this is a fisr in first out linked list */

// insert candy type in to link list belt
void produce(producer_type candy_type, Link * head)
{
    Link ptr = malloc(sizeof(struct node));// allocates memory for the node
    ptr->candy_type = candy_type;
    ptr->next = *head;
    *head = ptr;

    // update print variables
    produced++;
    if(candy_type == frog_bite) frog_total++;
    else escar_total++;
}

// helps to update belt global variables
void consume_helper(consumer_type consumer, producer_type candy_type)
{
    if(consumer == Lucy)
    {
        if(candy_type == frog_bite)
            L_frog_total++;
        else // escargot
            L_escar_total++;
    }
    else // Ethel
    {
        if(candy_type == frog_bite)
            E_frog_total++;
        else // escargot
            E_escar_total++;
    }
}

// removes and returns the last element in the Link
// Link * head to allow for modification of head pointer
producer_type consume(consumer_type consumer, Link * head){

    if(*head == NULL) return -1;

    // traverse the Link
    Link prev = NULL;// prev is pointer
    Link ptr = *head;// ptr is pointer, not head itself
    while(ptr->next != NULL){
        prev = ptr;
        ptr = ptr->next;
    }

    // if only one node on list
    if(prev == NULL){
        Link tmp = malloc(sizeof(struct node)); // create temporary node
        tmp = ptr;
        *head = NULL;

        // update consumer belt variables
        consume_helper(consumer, tmp->candy_type);
        return tmp->candy_type;
    }

    // if more than one node
    prev->next = NULL;
    // update consumer belt variables
    consume_helper(consumer, ptr->candy_type);
    return ptr->candy_type;
}

// count the number of candy type on list
int candycount(producer_type candy_type, Link head)
{
    Link ptr = head;
    int count = 0;
    while(ptr != NULL){
        if(ptr->candy_type == candy_type) count++;
        ptr = ptr->next;
    }
    return count;
}

//prints the Link for testing
void printlist(Link ptr){
    printf("Printing Linked List:\n");
    while(ptr != NULL){
        // frog bytes = 0, escargot = 1
        printf("%s\n", ptr->candy_type ? "escargot": "frog bites");
        ptr = ptr->next;// same as ptr->next
    }
    printf("\n");
}

// print what is currently in belt
void printupdate(Link head)
{
    int p_frog = candycount(frog_bite, head);
    int p_escar = candycount(escargot, head);
    printf("Belt: %d frogs + %d escargots = %d. produced: %d\t",
         p_frog, p_escar, p_frog + p_escar, produced);
}

// prind production and consupption report
void printreport()
{
    printf("\nPRODUCTION REPORT\n");
    printf("----------------------------------------\n");
	printf("crunchy frog bite producer generated %d candies\n", frog_total);
	printf("escargot sucker producer generated %d candies\n", escar_total);
	printf("Lucy consumed %d crunchy frog bites + %d escargot suckers = %d\n",
    L_frog_total, L_escar_total, L_frog_total + L_escar_total);
	printf("Ethel consumed %d crunchy frog bites + %d escargot suckers = %d\n",
    E_frog_total, E_escar_total, E_frog_total + E_escar_total);
}