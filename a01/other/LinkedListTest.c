#include <stdio.h>
#include <stdlib.h>

#define Nchars 27 /* a-z + ' */

struct node{
       int item;
       struct node*  next[27];
};

typedef struct node* link;

int main(int argc, char *argv[]){


    link head = malloc(sizeof(link));
    printf("%d\n",Nchars);


    return 0;
}
