
#include <stdio.h>
#include <stdlib.h>

/*
    assignment:
    singly linked list, unordered, duplicates ok.
*/

// typedef is used to give a data type a new name
typedef struct node *link ;// link is now type struct node pointer
/*
    typedef allows us to say "link ptr"
    instead of "struct node * ptr"
*/

struct node{
    int data;
    link next;//same as struct node * next, next is pointer type
};

// These are the 3 methods/functions you will define
void printAll(link head); // print a linked list , starting at link head
void addFirst(link *ptr, int val ); // add a node with given value to a list
link removeLast(link *head); // removes and returns the last element in the link

//prints the link
void printAll(link ptr){
    printf("\nPrinting Linked List:\n");
    while(ptr != NULL){
        printf(" %d ", (*ptr).data);
        ptr = (*ptr).next;// same as ptr->next
    }
    printf("\n");
}

//adds to the head of the link
// link * ptr so that we may modify the head pointer
void addFirst(link *ptr, int val ){
    link tmp = malloc(sizeof(struct node));// allocates memory for new node
    tmp->data = val;
    tmp->next = * ptr;
    *ptr = tmp;
}

// removes and returns the last element in the link
// link * head so that we may modify the head pointer if needed
link removeLast(link *head){

    if(* head == NULL) return NULL;

    // traverse the link
    link prev = NULL;// prev is pointer
    link ptr = *head;// ptr is pointer, not head itself
    while(ptr->next != NULL){
        prev = ptr;
        ptr = ptr->next;
    }

    // if only one node on list
    if(prev == NULL){
        link tmp = malloc(sizeof(struct node));// allocates memory for new node
        tmp = ptr;
        *head = NULL;
        return tmp;
    }

    // if more than one node
    prev->next = NULL;
    return ptr;
}

// testing
int main(void) {

    link head = NULL;// same as struct node * head, head is a pointer type

    //populating list
    for(int i = 0; i<10; i++){
        addFirst(&head, i);// "&" is needed to pass address of head
    }

    printAll(head);

    while(head != NULL){
        link tmp = removeLast(&head);
        printf(" %d ", tmp->data);
    }

    printAll(head);

    return 0;
}
