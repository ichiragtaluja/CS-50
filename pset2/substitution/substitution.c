#include <cs50.h>
#include <stdio.h>
#include <string.h>

string substitution(string a, string b);

int main(int argc, string argv[])
{
    //ensure only one word is being typed
    if (argc == 2)
    {
        //ensure string is 26 letters long
        if (strlen(argv[1]) == 26)
        {
            //functon to ensure only letters are being fed
            for (int i = 0; i < 26; i ++)
            {
                if (((argv[1])[i] > 64 && (argv[1])[i] < 91) || ((argv[1])[i] > 96 && (argv[1])[i] < 123))
                {
                    //function to see if there is no repetition
                    for (int k = 0; k < 26; k++)
                    {
                        for (int l = 0; l < 26; l++)
                        {
                            if ((((argv[1])[k] == (argv[1])[l]) && (k != l)) || ((argv[1])[k] == (argv[1])[l] + 32) || ((argv[1])[l] == (argv[1])[k] + 32))
                            {
                                printf("Error: repetition of letters not allowed\n");
                                return 1;
                            }
                            else
                            {
                            }
                        }
                    }
                }
                else
                {
                    printf("Error: type only alphabets\n");
                    return 1;
                }
            }
            printf("%s\n", argv[1]);
        }
        else
        {
            printf("Error: Charaters must be 26\n");
            return 1;
        }
    }
    else
    {
        printf("Error: Enter only one word\n");
        return 1;
    }

    //prompt user for input
    string input = get_string("Enter text: ");
    printf("plaintext: %s\n", input);

    //function for replacing text with code
    printf("ciphertext: ");
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] > 64 && input[i] < 91)
        {
            if (((argv[1])[(input[i] - 65)]) > 64 && ((argv[1])[(input[i] - 65)]) < 91)
            {
                printf("%c", (argv[1])[(input[i] - 65)]);
            }
            else
            {
                printf("%c", (argv[1])[(input[i] - 65)] - 32);
            }
        }
        else if (input[i] > 96 && input[i] < 123)
        {
            if (((argv[1])[(input[i] - 97)]) > 96 && ((argv[1])[(input[i] - 97)]) < 123)
            {
                printf("%c", (argv[1])[(input[i] - 97)]);
            }
            else
            {
                printf("%c", (argv[1])[(input[i] - 97)] + 32);
            }
        }
        else
        {
            printf("%c", input[i]);
        }
    }
    printf("\n");
}





