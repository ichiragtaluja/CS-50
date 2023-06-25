#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    //initiate a node pointer
    node *list = NULL;

    //add a number to the list
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n->next = NULL;
    list = n;

    //add number 2 to the list

    n = malloc(sizeof(node));

    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->number = 2;
    n->next = NULL;
    list = n;

    list->next = n;

    for (node *temp = list; temp != NULL; temp = temp->next)
    {
        printf("%i\n", temp->number);
    }
    while (list != NULL)
    {
        node *temp = list->next;
        free(list);
        list = temp;
    }
    return 0;
}








