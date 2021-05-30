#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //this part asks for an integer and rejects everything that isn't between 1 and 8 inclusive
    int n;
    do
    {
        n = get_int("%s", "Height: ");
    }
    while (n < 1 || n > 8);

    /*this part makes the pyramid, based on the user input
    the first loop just makes rows, equal to the input*/
    for (int i = 0; i < n; i++)
    {
        /*this second loop puts a number of spaces infront of the input of a row
        depending on how many rows are printed. I dont really know why this works.*/
        for (int j = i + 1; j < n; j++)
        {
            printf(" ");
        }
        /*this part prints the hashs, the pyramid, the given number minus the number of rows
        tells it how many hashes should be printed. Got this via trial and error, cant fully describe it.*/
        for (int k = n - i; k <= n; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}