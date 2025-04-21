#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;

    struct Node *next;
} *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct Node *createNewNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

// insertion
void pushHead(int value)
{
    struct Node *newNode = createNewNode(value);

    // if your head is empty
    if (head == NULL)
    {
        head = tail = newNode;
    }
    else
    { // when the head is not empty
        newNode->next = head;
        head = newNode;
    }
}

// deletion
void popHead()
{
    // if stack is empty
    if (head == NULL)
    {
        printf("Your stack is empty");
        return;
    }
    else if (head == tail)
    {
        temp = head;
        head = tail = NULL;
    }
    else
    { // if stack has more than 1 element
        temp = head;
        head = head->next;
    }

    free(temp);
}

void print()
{
    curr = head;
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }

    printf("NULL\n");
}

int main()
{
    pushHead(3);
    pushHead(5);
    pushHead(10);
    print();
    printf("POP HEAD\n");
    popHead();
    print();
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// struct node
// {
//     int value;
//     struct node *next;
// };

// struct node *head, *tail, *temp, *curr;

// struct node *create_new_node(int value)
// {
//     struct node *new_node = (struct node *)malloc(sizeof(struct node));

//     new_node->value = value;
//     new_node->next = NULL;
//     return new_node;
// }

// void push_head(int value)
// {
//     struct node *new_node = create_new_node(value);

//     if (head == NULL)
//     {
//         head = tail = new_node;
//     }
//     else
//     {
//         new_node->next = head;
//         head = new_node;
//     }
// }

// void pop_head()
// {
//     if (head == NULL)
//     {
//         printf("There is no data in the linked list.");
//     }
//     else if (head == tail)
//     {
//         temp = head;
//         head = temp = NULL;
//     }
//     else
//     {
//         temp = head;
//         head = head->next;
//     }

//     free(temp);
// }

// void print_all()
// {
//     curr = head;
//     while (curr != NULL)
//     {
//         printf("%d -> ", curr->value);
//         curr = curr->next;
//     }

//     printf("NULL\n");
// }

// int main()
// {
//     push_head(20);
//     push_head(200);
//     pop_head();
//     print_all();
//     return 0;
// }