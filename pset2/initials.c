#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    /* To prompt user for a string */
    string username = GetString();
    /* To loop over the entire length of string */
    for (int i = 0, len = strlen(username); i < len; i++)
    {
        /* Check if character is a space or the first character */
        if ((username[i] == ' ') || (i == 0))
        {
            if (i == 0)
            {
                /* To convert to initials to uppercase then print */
                printf("%c", toupper(username[i]));
            }
            
            else
            {
                printf("%c", toupper(username[i + 1]));
            }
        }
    }
    printf("\n");
    /* To indicate that the program executes properly */
    return 0;
}
