/* Program to find min no. of coins */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* Function prototype */
void greedy(float change);

int main(void)
{
    printf("O hai! How much change is owed? \n");
    float change = GetFloat();
    /* To check for negative inputs */
    while (change < 0)
    {
        printf("How much change is owed? \n");
        change = GetFloat();
    }
    /* Call to the greedy() function */
    greedy(change);
    return 0;
}


/* Function to count no. of coins */
void greedy(float change)
{
    int coins, quarters, dimes, nickels, pennies;
    change = change * 100;
    /* Rounding off to prevent imprecision */
    change = roundf(change);
    
    /* To count no. of quarters */
    quarters = floor(change / 25);
    change = change - quarters * 25;
    
    /* To count no. of dimes */
    dimes = (change / 10);
    change = change - dimes * 10;
    
    /* To count no. of nickels */
    nickels = floor(change / 5);
    change = change - nickels * 5;
    
    /* To count no. of pennies */
    pennies = floor(change / 1);
    change = change - pennies * 1;
    
    /* Total no. of coins */
    coins = quarters + dimes + nickels + pennies;
    printf("%d\n", coins);
}
    
