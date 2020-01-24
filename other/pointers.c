#include <stdio.h>
#include <stdlib.h>

struct Pt{
    double x;
    double y;
};

void foo(char * ptr){
	printf("%s\n", ptr);
}

int main()
{
	printf("%c\n",40);
	//printf("%s\n", ptr);
	
    int x, y, z, i =2;
    int list[] = {-1, 1, 2, 3, 5, 6};
    struct Pt p1 = {5, 3};
    struct Pt p2 = {14, 7};

    int *a, *b;
    struct Pt *ptPtr = &p1;//address of p1
    int *v = list;
    v++;

    x = 40;
    x -= 6;
    y = 8;
    z = x - 5;
    *(list + 3) = 53;

    a = &x;
    b = &y;

    *a = 6;
    z = x - 3;
    y = *a + *b;

    int arrayVal = list[i++];//after this line i = 3

    printf("%d  %d  %d\n", x, y, z);
    printf("%d  %d\n", i, arrayVal);
    printf("%d  %d  %d\n", *v, *(list), *(list + 1));
    printf("%f  %f\n", p1.x, p2.y);
    printf("%f\n", ptPtr->y);
    printf("%f\n", (*ptPtr).x);
	*/
    return 0;
}
