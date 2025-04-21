#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;

node *create_node(int value)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *insert_root(node *root, int value)
{
    if (!root)
    {
        printf("SUCCESSFULLY INSERTED ROOT TO THE BST.\n");
        return create_node(value);
    }

    if (value > root->value)
    {
        root->right = insert_root(root->right, value);
    }
    else if (value < root->value)
    {
        root->left = insert_root(root->left, value);
    }
    else
    {
        printf("DUPLICATED VALUE CAN'T BE INPUTTED.\n");
    }

    return root;
}

node *predecessor(node *root)
{
    node *curr = root->left;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

node *successor(node *root)
{
    node *curr = root->right;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

node *delete_value(node *root, int value)
{
    if (!root)
    {
        return NULL;
    }

    if (value > root->value)
    {
        root->right = delete_value(root->right, value);
    }
    else if (value < root->value)
    {
        root->left = delete_value(root->left, value);
    }
    else
    {
        if (!root->left && !root->right)
        {
            free(root);
            root = NULL;
        }
        else if (root->left && root->right)
        {
            node *temp = predecessor(root);
            root->value = temp->value;
            root->left = delete_value(root->left, temp->value);
        }
        else
        {
            node *temp = NULL;
            if (root->right)
            {
                temp = root->right;
            }
            else
            {
                temp = root->left;
            }
            free(root);
            root = temp;
        }
        printf("SUCCESSFULLY DELETED ROOT FROM BST.\n");
    }

    return root;
}

void print_pre_order(node *root)
{
    if (!root)
    {
        return;
    }
    printf("%d ", root->value);
    print_pre_order(root->left);
    print_pre_order(root->right);
}

void print_in_order(node *root)
{
    if (!root)
    {
        return;
    }
    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

void print_post_order(node *root)
{
    if (!root)
    {
        return;
    }
    print_post_order(root->left);
    print_post_order(root->right);
    printf("%d ", root->value);
}

void view_bst(node *root)
{
    if (!root)
    {
        printf("BST IS EMPTY.\n");
        return;
    }

    printf("BST IN IN-ORDER FORM : ");
    print_in_order(root);
    printf("\n\n");

    printf("BST IN PRE-ORDER FORM : ");
    print_pre_order(root);
    printf("\n\n");

    printf("BST IN POST-ORDER FORM : ");
    print_post_order(root);
    printf("\n\n");
}

void reset_bst(node *root)
{
    if (!root)
    {
        return;
    }
    reset_bst(root->left);
    reset_bst(root->right);
    free(root);
}

int main()
{

    return 0;
}