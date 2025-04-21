#include <stdio.h>
#include <stdlib.h>

void print_menu(int count_data)
{
    printf("1. Push data\n");
    printf("2. View data\n");
    printf("3. Clear data\n");
    printf("4. Exit Program\n");
    printf("Total data in the linked list is %d.\n", count_data);
    printf("Choose your option [1..4] : ");
}

struct node
{
    int value;
    struct node *next;
    struct node *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

struct node *create_node(int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

void push_head(int value)
{
    struct node *new_node = create_node(value);

    // check if empty
    if (head == NULL)
    {
        head = tail = new_node;
    }
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

void view_data()
{
    if (head == NULL)
    {
        printf("Linked list is empty.\n");
        return;
    }

    curr = head;
    printf("From head to tail :");
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }

    printf("NULL\n");

    curr = tail;
    printf("From tail to head :");
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->prev;
    }

    printf("NULL\n");
}

void clear_data()
{
    while (head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
    tail = NULL;
}

int main()
{
    int count_data = 0;
    int option_input;
    do
    {
        system("cls");

        print_menu(count_data);
        scanf("%d", &option_input);
        getchar();

        switch (option_input)
        {
        case 1:
            int number;
            printf("Please input your number : ");
            scanf("%d", &number);
            getchar();
            push_head(number);
            count_data++;
            break;

        case 2:
            view_data();
            break;

        case 3:
            clear_data();
            count_data = 0;
            printf("Successfully clear all the data.\n");
            break;

        case 4:
            printf("Exitting.\n");
            break;

        default:
            printf("Please input the correct number [1..4].\n");
        }

        if (option_input != 4)
            system("pause");
    } while (option_input != 4);

    printf("Successfully exit the program!\n");
    return 0;
}