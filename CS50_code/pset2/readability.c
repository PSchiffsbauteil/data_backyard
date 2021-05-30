#include <cs50.h>
#include <stdio.h>
#include <string.h>
//this can check for input types, like alphabetical or spaces.
#include <ctype.h>

int main(void)
{
    string t;
    t = get_string("%s", "Text: ");

    //this counts all chars in the text and differentiates for spaces and punctuation
    int n = 0;
    int spaces = 0;
    int punctuation = 0;
    float sentences = 0;
    while (t[n] != '\0')
    {
        n++;
        if (t[n] == ' ')
        {
            spaces++;
        }
        if (ispunct(t[n]))
        {
            punctuation++;
        }
        //because 'ispunct' counts everything, this is for the sentence count only
        if (t[n] == '.' || t[n] == '!' || t[n] == '?')
        {
            sentences++;
        }
    }
    //because there are spaces between words, the amount of space is nearly equal the amount of words.
    float letters = n - spaces - punctuation;
    float words = spaces + 1;

    //this can probably be done as a program and hidden beneath, instead of added here as well.
    float L = letters / words * 100;
    float S = sentences / words * 100;
    float i;
    i = 0.0588 * L - 0.296 * S - 15.8;
    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (i > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", i);
    }
}