// test file

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>	// enambles boolean
#include <string.h>

//strtok returns NULL when there is no other token

char str[] = "boy";
int i = 0;

void pprint(char *ptr){
    // print character of pointer
    printf("ptr (chr) -> %c\n",*ptr);
    // print decimal value of character
    printf("ptr (dec) -> %d\n",*ptr);
    // print pointer location address
    printf("ptr (adr) -> %p\n\n",*ptr);
}

void one(){
    char * ptr = str;
    while (*ptr != 0 && i<10){
        pprint(ptr);
        ptr++;
        i++;
	}

}

void two(){
    char * ptr = strtok(str," ");
    while (ptr != NULL && i<10){
        printf("%s\n", ptr);
        ptr = strtok(NULL," ");
	}

}

int main(){


	printf("%s\n",str);

	one();

    printf("\ni = %d\n", i);

	return 0;
}

