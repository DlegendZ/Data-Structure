#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Node *createNewNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int max(int a, int b)
{
    return a >= b ? a : b;
}

int getHeight(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBF(struct Node *node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *B = y->left;

    y->left = x;
    x->right = B;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *B = x->right;

    x->right = y;
    y->left = B;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

struct Node *insertValue(struct Node *root, int value)
{
    if (root == NULL)
        return createNewNode(value);

    if (value < root->value)
        root->left = insertValue(root->left, value);
    else if (value > root->value)
        root->right = insertValue(root->right, value);
    else
    {
        printf("Duplicate value.\n");
        return root;
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bf = getBF(root);

    // LL
    if (bf > 1 && value < root->left->value)
        return rightRotate(root);
    // RR
    if (bf < -1 && value > root->right->value)
        return leftRotate(root);
    // LR
    if (bf > 1 && value > root->left->value)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RL
    if (bf < -1 && value < root->right->value)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node *predecessor(struct Node *root)
{
    struct Node *node = root->left;
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

struct Node *deleteValue(struct Node *root, int value)
{
    if (root == NULL)
    {
        printf("Error : Can't Find The Value\n");
        return NULL;
    }

    if (value < root->value)
        root->left = deleteValue(root->left, value);
    else if (value > root->value)
        root->right = deleteValue(root->right, value);
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
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
            struct Node *temp = predecessor(root);
            root->value = temp->value;
            root->left = deleteValue(root->left, temp->value);
        }
    }

    // Balancing logic
    if (root == NULL)
        return root;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int bf = getBF(root);

    // LL
    if (bf > 1 && getBF(root->left) >= 0)
        return rightRotate(root);
    // LR
    if (bf > 1 && getBF(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR
    if (bf < -1 && getBF(root->right) <= 0)
        return leftRotate(root);
    // RL
    if (bf < -1 && getBF(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printAll(struct Node *root)
{
    if (root == NULL)
        return;
    printAll(root->left);
    printf("%d (BF=%d)\n", root->value, getBF(root));
    printAll(root->right);
}

int main()
{
    struct Node *root = NULL;

    root = insertValue(root, 10);
    root = insertValue(root, 5);
    root = insertValue(root, 7);
    root = insertValue(root, 15);
    root = insertValue(root, 20);
    root = insertValue(root, 17);
    root = insertValue(root, 30);

    printf("INSERTION:\n");
    printAll(root);

    printf("\n");

    root = deleteValue(root, 5);
    printf("After Deletion (5):\n");
    printAll(root);

    root = deleteValue(root, 30);
    printf("After Deletion (30):\n");
    printAll(root);

    root = deleteValue(root, 20);
    printf("After Deletion (20):\n");
    printAll(root);

    return 0;
}
