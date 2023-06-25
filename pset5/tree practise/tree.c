#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void print_tree(node *root);
void free_tree(node *root);

int main(void)
{
    //make tree 0
    node *tree = NULL;

    //allocate number to first memory
    node *n = malloc(sizeof(node));

    if (n == NULL)
    {
        return 1;
    }

    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }

    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    n = malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }

    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);
    free_tree(tree);
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free(root->left);
    free(root->right);
    free(root);
}



