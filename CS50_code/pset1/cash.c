#include <stdio.h>
#include <cs50.h>
#include <math.h>

float change(void);

int main(void)
{
    //this function converts the float input into an int and converts to only cents, hopefully
    int cents = round(change() * 100);
    //this is equally complicated, but i cant wrap my head around it right now.
    int q = cents / 25;
    int qr = cents % 25;
    int t = qr / 10;
    int tr = qr % 10;
    int f = tr / 5;
    int fr = tr % 5;
    int o = fr / 1;


    if (qr == 0)
    {
        printf("%i\n", q);
    }
    else if (tr == 0)
    {
        printf("%i\n", q + t);
    }
    else if (fr == 0)
    {
        printf("%i\n", q + t + f);
    }
    else
    {
        printf("%i\n", q + t + f + o);
    }
}


float change(void)
{
    //this functions prompts for user input. The user has to put in at least 1 cent.
    float c;
    do
    {
        c = get_float("%s", "Amout of change:");
    }
    while (c < 0.009);
    //i have to return this here, so that the function is void in the end for it to compile
    //if i would include this above, i had to delete 'return'
    return c;
}