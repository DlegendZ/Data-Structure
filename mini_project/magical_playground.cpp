#include <stdio.h>
#include <stdlib.h>

struct child
{
    int number;
    struct child *next;
};

struct child *head, *tail;

struct child *add_child(int number)
{
    struct child *new_child = (struct child *)malloc(sizeof(struct child));
    new_child->number = number;
    new_child->next = NULL;
    return new_child;
}

void push_mid(int number)
{
    struct child *new_child = add_child(number);

    if (head == NULL)
    {
        head = tail = new_child;
    }
    else if (head->number > new_child->number)
    {
        new_child->next = head;
        head = new_child;
    }
    else if (tail->number < new_child->number)
    {
        tail->next = new_child;
        tail = new_child;
    }
    else
    {
        struct child *curr = head;
        while (curr->next != NULL)
        {
            if (curr->next->number > new_child->number)
            {
                new_child->next = curr->next;
                curr->next = new_child;
                break;
            }
            curr = curr->next;
        }
    }
}

void pop_mid(int number)
{
    if (head == NULL)
    {
        printf("Linked list is empty.\n");
        return;
    }

    struct child *temp;
    struct child *curr;

    if (head == tail && head->number == number)
    {
        temp = head;
        head = tail = NULL;
    }
    else if (head->number == number)
    {
        temp = head;
        head = head->next;
    }
    else if (tail->number == number)
    {
        curr = head;
        while (curr->next != NULL)
        {
            if (curr->next->number == number)
            {
                temp = curr->next;
                tail = curr;
                tail->next = NULL;
                break;
            }
            curr = curr->next;
        }
    }
    else
    {
        curr = head;
        while (curr->next != NULL)
        {
            if (curr->next->number == number)
            {
                temp = curr->next;
                curr->next = temp->next;
                break;
            }
            curr = curr->next;
        }
        if (curr->next == NULL)
        {
            printf("Child not found!\n");
            return;
        }
    }
    free(temp);
}

// to print linked list
void print_all()
{
    struct child *curr = head;
    while (curr != NULL)
    {
        printf("%d -> ", curr->number);
        curr = curr->next;
    }
    printf("NULL\n\n");
}

void print_menu()
{
    printf("====[Please choose an action]====\n");
    printf("1. add child to the queue.\n");
    printf("2. remove child from the queue.\n");
    printf("3. Exit the program.\n");
    printf("Your input here >> ");
}

int main()
{
    int input;
    int number;

    do
    {
        system("cls");
        printf("====[Welcome to the magical playground!]====\n\n");
        printf("====[queue's status]====\n");
        print_all();

        print_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Please input child's number >> ");
            scanf("%d", &number);
            getchar();

            push_mid(number);
            printf("Successfully execute the order.\n");
            break;
        case 2:
            printf("Please input child's number to remove >> ");
            scanf("%d", &number);
            getchar();

            pop_mid(number);
            printf("Successfully execute the order.\n");
            break;
        }
        system("pause");
    } while (input != 3);

    // free memory before exitting
    struct child *curr = head;
    while (curr != NULL)
    {
        head = head->next;
        free(curr);
        curr = head;
    }
    return 0;
}