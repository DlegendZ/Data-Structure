#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer
{
    char customer_name[101];
    int prior_num;
    struct customer *next;
    struct customer *prev;
};

struct customer *head = NULL, *tail = NULL, *temp = NULL, *curr = NULL;

struct customer *create_new_customer_node(char customer_name[], int prior_num)
{
    struct customer *new_customer = (struct customer *)malloc(sizeof(struct customer));

    if (!new_customer)
    {
        printf("FAIL TO CREATE A NEW CUSTOMER NODE.\n");
        return NULL;
    }

    strcpy(new_customer->customer_name, customer_name);
    new_customer->prior_num = prior_num;
    new_customer->next = NULL;
    new_customer->prev = NULL;
    return new_customer;
}

void add_customer(char customer_name[], int prior_num)
{
    struct customer *new_customer = create_new_customer_node(customer_name, prior_num);

    if (!new_customer)
    {
        printf("FAIL TO ADD A NEW CUSTOMER.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_customer;
    }
    else if (head->prior_num > new_customer->prior_num)
    {
        head->prev = new_customer;
        new_customer->next = head;
        head = new_customer;
    }
    else if (tail->prior_num <= new_customer->prior_num)
    {
        tail->next = new_customer;
        new_customer->prev = tail;
        tail = new_customer;
    }
    else
    {
        curr = head->next;
        while (curr != NULL)
        {
            if (curr->prior_num > new_customer->prior_num)
            {
                curr->prev->next = new_customer;
                new_customer->prev = curr->prev;
                new_customer->next = curr;
                curr->prev = new_customer;
                break;
            }
            curr = curr->next;
        }
    }
}

void view_queue()
{
    printf("=== VIEW QUEUE ===\n");

    if (head == NULL)
    {
        printf("QUEUE IS EMPTY.\n");
        return;
    }

    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s | PRIORITY : %d.\n", i, curr->customer_name, curr->prior_num);
        curr = curr->next;
        i++;
    }
}

void pop_queue()
{
    if (head == NULL)
    {
        printf("QUEUE IS EMPTY.\n");
        return;
    }

    if (head == tail)
    {
        temp = head;
        head = tail = NULL;
    }
    else
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
}

void display_menu()
{
    printf("=== PRIORITY QUEUE ===\n");
    printf("1. ADD QUEUE.\n");
    printf("2. VIEW QUEUE.\n");
    printf("3. POP QUEUE.\n");
    printf("4. EXIT.\n");
    printf("YOUR INPUT HERE >> ");
}

void clear_memories()
{
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    tail = NULL;
}

int main()
{
    int input;
    char customer_name[101];
    int prior_num;

    do
    {
        system("cls");
        display_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE CUSTOMER'S NAME >> ");
            scanf("%s", customer_name);
            getchar();

            printf("PLEASE INPUT THE CUSTOMER'S PRIORITY NUMBER >> ");
            scanf("%d", &prior_num);
            getchar();

            add_customer(customer_name, prior_num);
            system("pause");
            break;
        case 2:
            view_queue();
            system("pause");
            break;
        case 3:
            pop_queue();
            system("pause");
            break;
        case 4:
            clear_memories();
            break;
        }
    } while (input != 4);
    return 0;
}