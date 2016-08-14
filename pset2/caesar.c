#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

/* Prototype of the function */
void caesar(int k);

int main(int argc, string argv[])
{
    /* count of the cmd-line arguments; 2 arguments reqd.*/
    if (argc != 2)
    {
        printf("Retry\n");
        return 1;
    }
    
    else
    {
        /* Convert char to int */
        int k = atoi(argv[1]);
        if (k >= 26)
        {
            k = k % 26;
        }
        /* Call to the function caesar() */
        caesar(k);
    }
    /* Successful execution */
    return 0;
}

void caesar(int k)
{
    string txt = GetString();
    int len = strlen(txt);
    /* char matrix stores lowercase and uppercase characters */
    string appendix[2] = {"abcdefghijklmnopqrstuvwxyz",
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    for (int i = 0; i < len; i++)
    {
        if (isalpha(txt[i]))
        {
            if (isupper(txt[i]))
            {
                /* second index : relative position w.r.t. a */
                txt[i] = appendix[1][((int) (tolower(txt[i]) - 'a') + k) % 26];
            }
            else
            {
                /* second index : relative position w.r.t. a */
                txt[i] = appendix[0][((int) (tolower(txt[i]) - 'a') + k) % 26];
            }
        }
    }
    printf("%s\n", txt);
}
