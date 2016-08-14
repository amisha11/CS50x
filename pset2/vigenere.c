#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

/* Prototype of the function */
void vigenere(string k);

int main(int argc, string argv[])
{
    /* Check the count of the cmd-line arguments; 2 arguments reqd.*/
    if (argc != 2)
    {
        printf("Retry\n");
        return 1;
    }
    
    else
    {
        int i = 0;
        /* Check for non-alphabetical characters */
        while (argv[1][i])
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Retry\n");
                return 1;
            }
            i++;
        }
        vigenere(argv[1]);
    }
    /* Successful execution */
    return 0;
}

void vigenere(string k)
{
    string txt = GetString();
    
    int key = strlen(k), j = -1;
    int tmp;
    int len = strlen(txt);
    char rel;
    
    /* matrix to lowercase & uppercase characters */
    string app[2] = {"abcdefghijklmnopqrstuvwxyz",
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    for (int i = 0; i < len; i++)
    {
        if (isalpha(txt[i]))
        {
            /* To index over the key */
            j++;
            if (isupper(txt[i]))
            {
                tmp = j % key;
                /* calculate relative pos of alphabet */
                rel = (tolower(txt[i]) - 'a');
                
                /* calculate pos of encrypted character */
                if (isupper(k[tmp]))
                {
                    txt[i] = app[1][((int) rel
                            + (int) (tolower(k[tmp] - 'A'))) % 26];
                }
                else if (islower(k[tmp]))
                {
                    txt[i] = app[1][((int) rel
                            + (int) (tolower(k[tmp] - 'a'))) % 26];
                }
            }
            else
            {
                tmp = j % key;
                /* calculate relative pos of alphabet */
                rel = (tolower(txt[i]) - 'a');
                
                /* calculate pos of encrypted character */
                if (isupper(k[tmp]))
                {
                    txt[i] = app[0][((int) rel
                            + (int) (tolower(k[tmp] - 'A'))) % 26];
                }
                else if (islower(k[tmp]))
                {
                    txt[i] = app[0][((int) rel
                            + (int) (tolower(k[tmp] - 'a'))) % 26];
                }
            }
        }
    }
    printf("%s\n", txt);
}
