#include <stdio.h>
#include <stdlib.h>
struct node{
       int item;
       struct node*  next;
};

typedef struct node* link;

int main(int argc, char *argv[]){
    struct node n1, n2, n3;

    n3.item = 2;
    n3.next = NULL;

    n2.item = 8;
    n2.next = &n3;//& means address in this case &n3 means address of n3

    n1.item = 5;
    n1.next = &n2;

    link x = &n1;

    while( x!= NULL)
    {
           printf("%d ", (*x).item);
           x = (*x).next;// x->next;
    }

    printf("\n");

    // remove the value 8 from the list
    x = &n1;  //reset pointer to start of linked list
    while( x != NULL)  {
            if( x->next->item == 8){//check for key using previous node
             x->next = x->next->next;
             break; //jump out of while loop since 8 was found
           }
    }

    x = &n1;  //reset pointer to start of linked list
    while( x!= NULL)   {
           printf("%d ", (*x).item);
           x = (*x).next;// x->next;
    }
    printf("\n\n");
    return 0;
}
