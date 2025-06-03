#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    int height;
    struct node *left;
    struct node *right;
} node;

struct node *create_new_node(int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(node));
    new_node->value = value;
    new_node->height = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

int max(int a, int b)
{
    return (a >= b) ? a : b;
}

int get_height(struct node *node)
{
    if (!node)
    {
        return 0;
    }
    return node->height;
}

int get_bf(struct node *node)
{
    if (!node)
    {
        return 0;
    }
    return (get_height(node->left) - get_height(node->right));
}

struct node *left_rotate(struct node *x)
{
    struct node *y = x->right;
    struct node *b = y->left;

    y->left = x;
    x->right = b;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

struct node *right_rotate(struct node *y)
{
    struct node *x = y->left;
    struct node *b = x->right;

    x->right = y;
    y->left = b;

    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return x;
}

struct node *insert_value(struct node *root, int value)
{
    if (!root)
    {
        return create_new_node(value);
    }
    else if (value < root->value)
    {
        root->left = insert_value(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insert_value(root->right, value);
    }
    else
    {
        printf("Err : Unable to insert duplicate value.\n");
        return root;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int bf = get_bf(root);

    if (bf > 1 && value < root->left->value)
    {
        return right_rotate(root);
    }

    if (bf > 1 && value > root->left->value)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (bf < -1 && value > root->right->value)
    {
        return left_rotate(root);
    }

    if (bf < -1 && value < root->right->value)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

struct node *predecessor(struct node *node)
{
    struct node *current = node->left;
    while (current->right)
    {
        current = current->right;
    }
    return current;
}

struct node *delete_value(struct node *root, int value)
{
    if (!root)
    {
        printf("Err : Unable to find the value.\n");
        return NULL;
    }
    else if (value < root->value)
    {
        root->left = delete_value(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = delete_value(root->right, value);
    }
    else
    {
        if (!root->left || !root->right)
        {
            node *temp = (root->left) ? root->left : root->right;

            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }

            free(temp);
        }
        else
        {
            node *temp = predecessor(root);
            root->value = temp->value;
            root->left = delete_value(root->left, temp->value);
        }
    }

    if (!root)
    {
        return NULL;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int bf = get_bf(root);

    if (bf > 1 && get_bf(root->left) >= 0)
    {
        return right_rotate(root);
    }

    if (bf > 1 && get_bf(root->left) < 0)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (bf < -1 && get_bf(root->right) <= 0)
    {
        return left_rotate(root);
    }

    if (bf < -1 && get_bf(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void print_all(node *root)
{
    if (!root)
    {
        return;
    }
    print_all(root->left);
    printf("%d (BF = %d)\n", root->value, get_bf(root));
    print_all(root->right);
}

int main()
{
    // assume i know this
    return 0;
}