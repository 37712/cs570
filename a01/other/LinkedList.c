#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
	linked list, single, unordered, duplicates ok.
*/

//	Note for self:
//	DO NOT MESS AROUND WITH THE HEAD USE A POINTER
//	DONT FORGET TO INCREASE OR DECREASE SIZE
//	DONT FORGET TO FREE MEMORY

struct node{
    int data;
    struct node *next;// next is a pointer type
};

//**** global variables ****//
struct node *head = NULL;// head is a pointer type
int size = 0;

// clears the linked list
void clear(){
	struct node *ptr = head;
	while(head != NULL){
		head = head->next;
		free(ptr);
		ptr = head;
	}
    size = 0;
}

void printAll(){
    struct node * ptr = head;// pointer to traverse the link
    printf("\nprinting linked list : \n");
    while(ptr != NULL){
        printf(" %d ", (*ptr).data);// (*ptr).data same as ptr->data
        ptr = (*ptr).next;// (*ptr).next same as ptr->next
    }
    printf("\n\n");
}

// add link to the start of the linked list
void addFirst(int val){
    struct node * ptr = malloc(sizeof(struct node));// allocates memory for the node
    ptr->data = val;
    ptr->next = head;
    head = ptr;
    size++;
}

// add link to the end of the linked list
void addLast(int val){
    if(head == NULL){ addFirst(val); return; }
    struct node * ptr = head;// pointer to traverse the link
    while(ptr->next != NULL) ptr = (*ptr).next;// same as ptr = ptr->next;
    ptr->next = malloc(sizeof(struct node));// creates and allocates memory for the node
    ptr = ptr->next;
    ptr->data = val;
    ptr->next = NULL;
    size++;
}

//is there a node with the val. true/false
bool contains(int val){
    struct node * ptr = head;
    while(ptr != NULL){
        if(ptr->data == val)
            return true;
        ptr = ptr->next;
    }
    return false;
}

//find and return the node/link itself
struct node *find(int val){
	struct node * ptr = head;
	while(ptr != NULL){
		if(ptr->data == val)
			return ptr;
		ptr = ptr->next;
	}
	return ptr;
}

// removes and returns node/link
struct node *removeFirst(){
	if(head == NULL) return head;
    struct node * tmp = head;
    head = head->next;
    size--;
    return tmp;
}

// removes and returns node/link
struct node *removeLast(){
	if(head == NULL) return head;
    struct node * ptr = head;
    struct node * prev = NULL;
    // traverse the link
    while(ptr->next != NULL){
		prev = ptr;
		ptr = (*ptr).next;// same as ptr = ptr->next;
    }
    // if only one node on list
    if(prev == NULL){
        struct node *tmp = malloc(sizeof(struct node));// allocates memory for new node
        tmp = ptr;
        head = NULL;
        size--;
        return tmp;
    }
    // if more than one node
    prev->next = NULL;
    size--;
    return ptr;
}

/*
	******************* TESTING *******************
	******************* TESTING *******************
	******************* TESTING *******************
*/

//populate with set numbers
void populate(int x){
	for(int i = 0; i<x; i++) addFirst(i);
}

// populate with random numbers ranging from 0 to 100
void populateRandom(int x){
	//srand(time(NULL));
	for(int i = 0; i<x; i++){
		addFirst(rand() % 100);
	}
}

// tests
int main(void){

	populateRandom(10);
//	populate(3);

    printAll();

	int val = 10;
    printf("find(%d) = %s\n", val, contains(val) ? "true" : "false");

    printf("size = %d\n", size);

    printf("\n*** removeFirst ALL ***\n");
    while(head != NULL){
		struct node *tmp = removeFirst();
		printf(" %d ", tmp->data);
		free(tmp);
    }printf("\n");

    struct node *tmp = removeFirst();
    if(tmp != NULL)
		printf("tmp is NOT NULL\n");
	else
		printf("tmp is NULL\n");

    printAll();

	populate(10);

	clear();

	printf("Linked list should be empty\n");

	printAll();

	populate(10);

	val = 8;
	struct node *ptr = find(val);
	if(ptr == NULL) printf("find returned NULL\n");
	else printf("find(%d) returned link with val = %d", val, ptr->data);

	printf("\n*** removeLast ALL ***\n");
    while(head != NULL){
		struct node *tmp2 = removeLast();
		printf(" %d ", tmp2->data);
		free(tmp2);
    }printf("\n");
    struct node *tmp2 = removeLast();
    if(tmp != NULL)
		printf("tmp2 is NOT NULL\n");
	else
		printf("tmp2 is NULL\n");


    return 0;
}
