/*
 * CS570, spring 2020
 *
 * Carlos Gamino Reyes
 * misc0230@edoras.sdsu.edu
 * 819230978
 *
 * Tan Truong
 * misc0308@edoras.sdsu.edu
 * 821006778
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // needed for getopt
#include <stdbool.h>    // needed for bool

int main(int argc, char ** argv)
{
    // needed variables
    int Option = 0;
    int N = 0;
    bool n = false;
    bool p = false;
    bool t = false;
    char * str;
    FILE * fp;

    if(argc != 2) // check if arguments are wrong or not set
    {
        printf("arguments are wrong or not set");
        return -1;
    }

    // n = 0, p = 1, t = 2
    while ( (Option = getopt(argc, argv, "n:p:t")) != -1) {
        switch (Option) {
            case 'n': /* Number of addresses to process */
                n = true;
                N = atoi()
                // optarg will contain the string following -n
                // Process appropriately (e.g. convert to integer atoi(optarg))
                break;
            case 'p': /* produce map of pages */
                // optarg contains name of page file…
                break;
            case 't': /* Show address translation */
                // No argument this time, just set a flag
                break;
            default:
                break;
        }
    }

    return 0;
}
