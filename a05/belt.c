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

// push candy type in to link list belt
// push(frog_bite, &head);
void produce(producer_type candy_type, Link * head)
{
    Link ptr = malloc(sizeof(struct node));// allocates memory for the node
    ptr->candy_type = candy_type;
    ptr->next = *head;
    *head = ptr;
}

// removes and returns the last element in the Link
// Link head so that we may modify the head pointer if needed
// pop(&head)
producer_type consume(Link * head){

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
        return tmp->candy_type;
    }

    // if more than one node
    prev->next = NULL;
    return ptr->candy_type;
}

// count the number of candy type on list
int candycount(producer_type candy_type, Link head)
{
    Link ptr = head;
    int count = 0;
    while(ptr != NULL){
        if(ptr->candy_type == candy_type) count++;
        ptr = ptr->next;// same as ptr->next
    }
    return count;
}

//prints the Link
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
void printbelt()
{

}

void printreport()
{

}