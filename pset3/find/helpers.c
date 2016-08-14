/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int max = n-1, min = 0;
    int mid;
    while (max >= min)
    {
        mid = (max + min)/2;
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value)
        {
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int tmp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (values[i] > values[j])
            {
                tmp = values[i];
                values[i] = values[j];
                values[j] = tmp;
            }
        } 
    }
    return;
}
