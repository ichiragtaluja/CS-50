#include <cs50.h>
#include <stdio.h>

long print_card_number(void);
int check_sum(long n);

int main(void)
{
    long credit_card;
    int s;
    long f;
    long g;
    // Run function which asks card number and prints it
    credit_card = print_card_number();
    printf("%ld\n", credit_card);
    s = check_sum(credit_card);

    //program for American Express or Visa or Mastercard
    if (((s % 10) == 0) && ((credit_card / 10000000000000) < 100) && ((credit_card / 10000000000000) == 34))
    {
        printf("AMEX\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 10000000000000) < 100) && ((credit_card / 10000000000000) == 37))
    {
        printf("AMEX\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 100000000000000) < 100) && ((credit_card / 100000000000000) == 51))
    {
        printf("MASTERCARD\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 100000000000000) < 100) && ((credit_card / 100000000000000) == 52))
    {
        printf("MASTERCARD\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 100000000000000) < 100) && ((credit_card / 100000000000000) == 53))
    {
        printf("MASTERCARD\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 100000000000000) < 100) && ((credit_card / 100000000000000) == 54))
    {
        printf("MASTERCARD\n");
    }
    else if (((s % 10) == 0) && ((credit_card / 100000000000000) < 100) && ((credit_card / 100000000000000) == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (((credit_card / 1000000000000) == 4) && ((s % 10) == 0) && ((credit_card / 100000000000) < 100))
    {
        printf("VISA\n");
    }
    else if (((credit_card / 1000000000000000) == 4) && ((s % 10) == 0) && ((credit_card / 100000000000000) < 100))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


// Make a function that prints customer's card
long print_card_number()
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);
    return n;
}

// Make a function that tests sum of digit test
int check_sum(long n)
{
    int sum = 0;
    int pos = 0;
    int p;

    while (((n % 10) >= 1) || (((n % 10) == 0) && (n > 1)))
    {
        if (pos % 2 == 0)
        {
            sum += (n % 10);
            n = n / 10;
            pos ++;
        }
        else
        {
            p = 2 * (n % 10);
            if (p < 10)
            {
                sum += p;
            }
            else
            {
                sum += ((p / 10) + (p % 10));
            }
            n = n / 10;
            pos ++;
        }
    }
    //printf("%i\n",sum);
    //printf("%i\n",pos);

    return sum;
}



