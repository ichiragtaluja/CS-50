// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//declare an int to count total size of dictionary
unsigned int i = 0;
unsigned int s;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //first, hash the word using hash function
    int t = hash(word);

    //generate null poiter for node
    node *tmp = NULL;
    if (tmp != NULL)
    {
        return false;
    }
    tmp = table[t];
    for (tmp = table[t]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
            break;
        }
        else
        {
        }
    }

    //go to that array number and create a pointer that points at the beginning of that aray
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';

    //if string length is equal to only 1
    //if (strlen(word) == 1)
    //{
    //int a = toupper(word[0]) - '@';
    //return (a-1);
    //}
    //else
    //{
    //int a = toupper(word[0]) - '@';
    //int b = toupper(word[1]) - '@';
    //int c = (a * 100) + b;
    //return c;
    //}

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //make temporary memory for reading each and every word
    //char *t = malloc((LENGTH + 1) * sizeof(char));
    char t[LENGTH + 1];

    //open the dictionary file in temporary filr input
    FILE *input = fopen(dictionary, "r");
    {
        if (input == NULL)
        {
            return false;
        }
    }

    //scan the file one word at a time
    while (fscanf(input, "%s", t) != EOF)
    {
        //create new memory for word
        node *n = malloc(sizeof(node));
        {
            if (n == NULL)
            {
                //free(n);
                return false;
                break;
            }
        }
        //strcpy(n->word, "Hello");
        //n->next = NULL;
        //copy word in node from t
        strcpy(n->word, t);

        //convert first word into number
        s = hash(n->word);

        //put it in hash table
        n->next = table[s];
        table[s] = n;
        i ++;
    }
    //free(t);
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return i;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    node *curser = NULL;
    if (curser != NULL)
    {
        return false;
    }

    node *tmp = NULL;
    if (tmp != NULL)
    {
        return false;
    }

    for (int j = 0; j < N; j ++)
    {
        for (curser = table[j]; curser != NULL;)
        {
            tmp = curser;
            curser = curser->next;

            free(tmp);
        }
    }

    return true;
}
