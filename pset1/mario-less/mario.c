#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //. getting input again if it is less than one and more than 8
    int n;
    do
    {
        n = get_int("Height: ");
    } while (n < 1 || n > 8);

    // it inserts a new ine
    for (int i = 0; i < n; i++)
    {
        // it prints space for enery line
        for (int k = n - i - 1; k > 0; k--)
        {

            printf(" ");
        }
        // it prints hash for every line
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}