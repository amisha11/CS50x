/* Program to print pyramids */

#include <stdio.h>
#include <cs50.h>

/* Function prototype*/
int pyramid(int n);

int main(void)
{
    int flag = 0;
    /* Prompt user for an integer value */
    do
    {
        printf("Height: ");
        int i = GetInt();
        /* Check for the height to be a +ve integer no greater than 23 */
        if ((i >= 0) && (i < 24))
        {
            flag += 1;
            /* Call to function pyramid() */
            pyramid(i);
        }
    }while (!flag);
    return 0;
}


/* Function to create '#' pyramid */
int pyramid(int n)
{
    int j, k, tot_hash;
    for (j = 0; j < n; j++)
    {
        /* Loop to print required number of spaces */
        for (k = 1; k < n - j; k++)
        {
            printf(" ");
        }
        /* Loop to print required number of # */
        for (tot_hash = 0; tot_hash <= j + 1; tot_hash++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
           
