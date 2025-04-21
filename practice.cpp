#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int priority_num;
    char order[100];
    struct Node *next;
    struct Node *prev;
};

struct Node *head = NULL, *tail = NULL;

struct Node *createNewNode(int priority_num, char order[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->priority_num = priority_num;
    strcpy(newNode->order, order);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void pushSorted(int priority_num, char order[])
{
    struct Node *newNode = createNewNode(priority_num, order);

    // Jika list kosong
    if (head == NULL)
    {
        head = tail = newNode;
        return;
    }

    struct Node *curr = head;

    while (curr != NULL && curr->priority_num >= priority_num)
    {
        curr = curr->next;
    }

    if (curr == head)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else if (curr == NULL)
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else
    {
        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

void pop_head()
{
    if (head == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    if (head != NULL)
    {
        head->prev = NULL;
    }
    else
    {
        tail = NULL;
    }

    free(temp);
}

void printAll()
{
    struct Node *curr = head;
    while (curr != NULL)
    {
        printf("[Priority: %d] %s -> ", curr->priority_num, curr->order);
        curr = curr->next;
    }
    printf("NULL\n");
}

void printMenu()
{
    printf("\nMenu:\n");
    printf("1. Enqueue\n");
    printf("2. Dequeue\n");
    printf("3. Display Queue\n");
    printf("4. Exit\n");
}

int main()
{
    int input;

    do
    {
        printMenu();
        printf("Please input your choice: ");
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
        {
            int priority_num;
            char order[100];

            printf("Please enter the order: ");
            scanf("%99[^\n]", order);
            getchar();

            printf("Please enter the priority number: ");
            scanf("%d", &priority_num);
            getchar();

            pushSorted(priority_num, order);
            break;
        }
        case 2:
            pop_head();
            break;
        case 3:
            printAll();
            break;
        case 4:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid input! Please enter a valid option.\n");
        }
    } while (input != 4);

    return 0;
}
