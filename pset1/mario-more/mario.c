#include <cs50.h>
#include <stdio.h>

int main(void)


{
    // taking in correct input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

// function for printing ..

    for (int i = 0; i < n ; i++)
    {
        // function for printing space

        for (int j = n - i - 1 ; j > 0 ; j--)
        {
            printf(" ");
        }
        // function for printing #

        for (int k = 0 ; k <= i ; k++)
        {
            printf("#");
        }

        // function for printing double space

        printf("  ");

        for (int l = 0 ; l <= i ; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}