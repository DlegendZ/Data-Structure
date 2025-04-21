#include <stdio.h>
#include <stdlib.h>

// define the struct
struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
};

// helper function
struct Node *createNewNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insertion
struct Node *insertValue(struct Node *root, int value)
{
    if (root == NULL)
    {
        printf("SUCCESSFULLY INSERT NEW VALUE\n");
        return createNewNode(value);
    }

    if (value < root->value)
    {
        root->left = insertValue(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insertValue(root->right, value);
    }
    else
    {
        printf("CAN'T INSERT DUPLICATE VALUE\n");
    }

    return root;
}

// predecessor
struct Node *predecessor(struct Node *root)
{
    struct Node *curr = root->left;

    while (curr->right != NULL)
    {
        curr = curr->right;
    }

    return curr;
}

// successor
struct Node *successor(struct Node *root)
{
    struct Node *curr = root->right;

    while (curr->left != NULL)
    {
        curr = curr->left;
    }

    return curr;
}

// deletion
// struct Node *deleteValue(struct Node *root, int value)
// {
//     if (root == NULL)
//     {
//         printf("CAN'T FIND THE VALUE\n");
//         return NULL;
//     }

//     if (value > root->value)
//     {
//         root->right = deleteValue(root->right, value);
//     }
//     else if (value < root->value)
//     {
//         root->left = deleteValue(root->left, value);
//     }
//     else
//     {
//         // no child
//         if (root->right == NULL && root->left == NULL)
//         {
//             free(root);
//             root = NULL;

//             printf("SUCCESSFULLY REMOVE THE VALUE\n");
//         }
//         else
//         {
//             // 1 child
//             if (root->left != NULL || root->right != NULL)
//             {
//                 struct Node *temp;
//                 if (root->left != NULL)
//                 {
//                     temp = root->left;
//                 }
//                 else
//                 {
//                     temp = root->right;
//                 }

//                 *root = *temp;
//                 free(temp);
//             }
//             else
//             {
//                 // 2 children
//                 // predecessor
//                 struct Node *temp = predecessor(root);
//                 root->value = temp->value;
//                 root->left = deleteValue(root->left, temp->value);
//             }
//         }
//     }

//     return root;
// }

// deletion
struct Node *deleteValue(struct Node *root, int value)
{
    if (root == NULL)
    {
        printf("CAN'T FIND THE VALUE\n");
        return NULL;
    }

    if (value > root->value)
    {
        root->right = deleteValue(root->right, value);
    }
    else if (value < root->value)
    {
        root->left = deleteValue(root->left, value);
    }
    else
    {
        // no child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
            printf("SUCCESSFULLY REMOVE THE VALUE\n");
        }
        // two children
        else if (root->left != NULL && root->right != NULL)
        {
            struct Node *temp = predecessor(root);
            root->value = temp->value;
            root->left = deleteValue(root->left, temp->value);
        }
        // one child
        else
        {
            struct Node *temp;
            if (root->left != NULL)
            {
                temp = root->left;
            }
            else
            {
                temp = root->right;
            }

            free(root);
            root = temp;
        }
    }

    return root;
}

// pre order
// print
// left
// right
void printPreOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%d ", root->value);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// in order
// left
// print
// right
void printInOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printInOrder(root->left);
    printf("%d ", root->value);
    printInOrder(root->right);
}

// post order
// left
// right
// print
void printPostOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->value);
}
// freeAll
void freeAll(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    freeAll(root->left);
    freeAll(root->right);
    free(root);
}

// viewBST function
void viewBST(struct Node *root)
{
    if (root == NULL)
    {
        printf("BST is Empty!\n\n");
        return;
    }

    printf("=====[PreOrder]=====\n");
    printPreOrder(root);
    printf("\n\n");

    printf("=====[InOrder]=====\n");
    printInOrder(root);
    printf("\n\n");

    printf("=====[PostOrder]=====\n");
    printPostOrder(root);
    printf("\n\n");
}

int main()
{
    // root variable
    struct Node *root = NULL;

    int input, value;

    do
    {
        system("cls");
        viewBST(root);
        printf("1. Insert Value\n");
        printf("2. Delete Value\n");
        printf("3. Exit\n");

        printf(">> ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
        {
            printf("Input Value: ");
            scanf("%d", &value);
            getchar();

            // insertion
            root = insertValue(root, value);

            system("pause");
            break;
        }
        case 2:
        {
            printf("Input Value: ");
            scanf("%d", &value);
            getchar();

            // deletion
            root = deleteValue(root, value);

            system("pause");
            break;
        }
        }
    } while (input != 3);

    // freeAll
    freeAll(root);

    return 0;
}
