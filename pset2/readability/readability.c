#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //asking customer to put in an input
    string input = get_string("Text : ");

    //print the number of letters
    printf("Letters: %i\n", count_letters(input));

    //print the number of words
    printf("Words: %i\n", count_words(input));

    //print the number of sentences
    printf("Sentences %i\n", count_sentences(input));
    float a = count_letters(input);
    float b = count_words(input);
    float c = count_sentences(input);

    //calculate L
    float l = (a / b) * 100;

    //printf("l: %f\n", l);
    //calculate S
    float s = (c / b) * 100.00;

    //printf("s: %f\n", s);
    float index = (0.0588 * l) - (0.296 * s) - 15.8;
    //printf("Float: %f\n", index);

    int value = (0.0588 * l) - (0.296 * s) - 15.8;
    //printf("Int : %i\n", value);

    //program to round off to nearest integer
    if ((index - value) >= 0.5 && (index < 16) && (index > 1))
    {
        printf("Grade %i\n", value + 1);
    }
    else if ((index - value) < 0.5 && (index < 16) && (index > 1))
    {
        printf("Grade %i\n", value);
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    //printf("%f\n", index);
}
//number of letters function
int count_letters(string text)
{
    int n;
    n = strlen(text);

    //program to delete punctuation, digits and spaces from n
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            n += 0;
        }
        else
        {
            n -= 1;
        }
    }
    return n;

}
//function to calculate number of words
int count_words(string text)
{
    int m = 1;
    int o = strlen(text);

    //calculate number of spaces
    for (int i = 0; i < o; i++)
    {
        if (text[i] == 32)
        {
            m += 1;
        }
        else
        {
            m += 0;
        }
    }
    return m;
}

//function to count sentences
int count_sentences(string text)
{
    int m = 0;
    int o = strlen(text);

    //calculate number of spaces
    for (int i = 0; i < o; i++)
    {
        if ((text[i] == 46) || (text[i] == '?') || (text[i] == 33))
        {
            m += 1;
        }
        else
        {
            m += 0;
        }
    }
    return m;

}
