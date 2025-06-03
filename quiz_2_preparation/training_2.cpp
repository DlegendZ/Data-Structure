#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    int height;
    struct node *left;
    struct node *right;
} node;

node *create_new_node(int value)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = value;
    new_node->height = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

int max(int a, int b)
{
    return a >= b ? a : b;
}

int get_height(node *root)
{
    if (!root)
    {
        return 0;
    }
    return root->height;
}

int get_bf(node *root)
{
    if (!root)
    {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

node *left_rotate(node *x)
{
    node *y = x->right;
    node *b = y->left;
    y->left = x;
    x->right = b;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

node *right_rotate(node *y)
{
    node *x = y->left;
    node *b = x->right;
    x->right = y;
    y->left = b;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return x;
}

node *insert_value(node *root, int value)
{
    if (!root)
    {
        return create_new_node(value);
    }

    if (value < root->value)
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

node *predecessor(node *root)
{
    node *current = root->left;
    while (current->right)
    {
        current = current->right;
    }
    return current;
}

node *delete_value(node *root, int value)
{
    if (!root)
    {
        printf("Err : Unable to find the value.\n");
        return NULL;
    }

    if (value < root->value)
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

void print_pre_order(node *root)
{
    if (!root)
    {
        return;
    }

    printf("%d (BF = %d)\n", root->value, get_bf(root));
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
    printf("%d (BF = %d)\n", root->value, get_bf(root));
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
    printf("%d (BF = %d)\n", root->value, get_bf(root));
}

void view_all(node *root)
{
    printf("PRINT PRE ORDER :\n");
    print_pre_order(root);
    printf("\n");

    printf("PRINT IN ORDER :\n");
    print_in_order(root);
    printf("\n");

    printf("PRINT POST ORDER :\n");
    print_post_order(root);
    printf("\n");
}

void exit_program(node *root)
{
    if (!root)
    {
        return;
    }
    exit_program(root->left);
    free(root);
    exit_program(root->right);
}

void menu_list()
{
    printf("=== AVL TREE SIMULATOR ===\n");
    printf("1. INSERT A VALUE\n");
    printf("2. DELETE  A VALUE\n");
    printf("3. VIEW AVL TREE\n");
    printf("4. EXIT SIMULATOR\n");
    printf("YOUR INPUT HERE >> ");
}

int main()
{
    node *root = NULL;
    int menu_option;
    int value;
    do
    {
        system("cls");
        menu_list();
        scanf("%d", &menu_option);
        getchar();

        switch (menu_option)
        {
        case 1:
            printf("PLEASE INPUT THE VALUE TO INSERT >> ");
            scanf("%d", &value);
            getchar();
            root = insert_value(root, value);
            system("pause");
            break;
        case 2:
            printf("PLEASE INPUT THE VALUE TO DELETE >> ");
            scanf("%d", &value);
            getchar();
            root = delete_value(root, value);
            system("pause");
            break;
        case 3:
            view_all(root);
            system("pause");
            break;
        case 4:
            exit_program(root);
            system("pause");
            break;
        default:
            printf("ERR : WRONG OUTPUT\n");
            system("pause");
            break;
        }
    } while (menu_option != 4);

    printf("THANK YOU FOR USING OUR SERVICE.\n");

    return 0;
}