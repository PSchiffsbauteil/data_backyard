#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//needs the input of a valid key

int main(int argc, string argv[])
{
    //for better style: the bounce is put into a variable
    string u = "Usage: ./caesar key\n";
    //this prompts for correct input; if there are exactly two arguments, the loop checks if the second cmd arg only has digits
    if (argc == 2)
    {
        //this checks for nondigits and stops the program in case of letters
        int l = strlen(argv[1]);
        for (int n = 0; n < l; n++)
        {
            if ((int) argv[1][n] < 48 || (int) argv[1][n] > 57)
            {
                printf("%s", u);
                return n;
            }
        }
        //this converts the string at argv[1] into an integer
        int k = atoi(argv[1]);
        string p = get_string("plaintext: ");
        int i = strlen(p);
        char c[i - 1];
        for (int j = 0; j < i; j++)
        {
            //this should correct for everything that is not a letter
            if ((int) p[j] < 65)
            {
                c[j] = (char)(int) p[j];
            }
            //this should fix for upper case
            else if ((int) p[j] > 64 && p[j] < 91)
            {
                c[j] = (char)(((((int) p[j] - 65) + k) % 26) + 65);
            }
            //this should do for every letter lowercase
            else if ((int) p[j] >= 97)
            {
                c[j] = (char)(((((int) p[j] - 97) + k) % 26) + 97);
            }
        }
        printf("ciphertext: %s\n", c);
    }
    else
    {
        printf("%s", u);
        return 1;
    }
}