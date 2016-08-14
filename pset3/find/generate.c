/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    /* If the command line argument count is not equal to 2 or 3,
    we return a sentinel value of 1 */
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Convert char to int and store it in n; the argument input by user is stored as char in argv[]
    int n = atoi(argv[1]);

    // if argc is 3, we call srand48() with the seed provided as command line argument
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    /* loop to generate n random numbers and display them on separate lines.
     *
     * We multiply the output of drand() by constant value 
     * LIMIT to generate the pseudorandom number
     *******************************************************************/
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
