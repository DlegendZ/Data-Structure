#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order
{
    char customer_name[101];
    char order[101];

    struct order *next;
    struct order *prev;
};

struct order *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct order *create_new_order_node(char customer_name[], char order[])
{
    struct order *new_order = (struct order *)malloc(sizeof(struct order));

    if (!new_order)
    {
        printf("\033[31mFail to create new order node.\033[0m\n");
        return NULL;
    }

    strcpy(new_order->customer_name, customer_name);
    strcpy(new_order->order, order);
    new_order->next = NULL;
    new_order->prev = NULL;
    return new_order;
}

void add_order(char customer_name[], char order[])
{
    struct order *new_order = create_new_order_node(customer_name, order);

    if (!new_order)
    {
        printf("\033[31mFail to add order to the queue.\033[0m\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_order;
    }
    else
    {
        tail->next = new_order;
        new_order->prev = tail;
        tail = new_order;
    }

    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

void serve_order()
{
    if (head == NULL)
    {
        printf("\033[31mQueue is empty. Order is not found.\033[0m\n");
        return;
    }

    if (head == tail)
    {
        temp = head;
        head = tail = NULL;
        printf("Order (name : \033[31m%s\033[0m | Order : \033[32m%s\033[0m) has been served and removed from the queue.\n", temp->customer_name, temp->order);
    }
    else
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
        printf("Order (name : \033[31m%s\033[0m | Order : \033[32m%s\033[0m) has been served and removed from the queue.\n", temp->customer_name, temp->order);
    }

    free(temp);
    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

void display_all()
{
    curr = head;
    int i = 1;
    printf("\033[34mQueue List :\033[0m\n");
    while (curr != NULL)
    {
        printf("%d. %s | %s\n", i, curr->customer_name, curr->order);
        i++;
        curr = curr->next;
    }
    printf("%d. NUll\n", i);
    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

void search_customer(char customer_name[])
{
    if (head == NULL)
    {
        printf("\033[31mqueue is empty.\033[0m\n");
        return;
    }

    curr = head;
    while (curr != NULL)
    {
        if (strcmp(curr->customer_name, customer_name) == 0)
        {
            printf("Order Found : %s | %s\n", curr->customer_name, curr->order);
            break;
        }
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("\033[31mOrder not found.\033[0m\n");
        return;
    }

    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

void cancel_order(char customer_name[])
{
    if (head == NULL)
    {
        printf("\033[31mqueue is empty.\033[0m\n");
        return;
    }

    if (head == tail && strcmp(head->customer_name, customer_name) == 0)
    {
        temp = head;
        head = tail = NULL;
    }
    else if (strcmp(head->customer_name, customer_name) == 0)
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
    }
    else if (strcmp(tail->customer_name, customer_name) == 0)
    {
        temp = tail;
        tail = tail->prev;
        tail->next = NULL;
    }
    else
    {
        curr = head->next;
        while (curr != tail)
        {
            if (strcmp(curr->customer_name, customer_name) == 0)
            {
                temp = curr;
                curr = curr->prev;
                curr->next = temp->next;
                temp->next->prev = curr;
                break;
            }
            curr = curr->next;
        }

        if (curr == tail)
        {
            printf("\033[31mOrder not found.\033[0m\n");
            return;
        }
    }
    printf("Order (name : \033[31m%s\033[0m | Order : \033[32m%s\033[0m) has been canceled and removed from the queue.\n", temp->customer_name, temp->order);
    free(temp);
    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

void print_menu()
{
    printf("=== \033[34mFAST FOOD RESTAURANT QUEUE\033[0m ===\n");
    printf("1. ADD ORDER.\n");
    printf("2. SERVE ORDER.\n");
    printf("3. PRINT QUEUE.\n");
    printf("4. SEARCH ORDER.\n");
    printf("5. CANCEL ORDER.\n");
    printf("6. EXIT.\n");
    printf("PLEASE INPUT YOUR CHOICE >> ");
}

void clear_data()
{
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    printf("\033[32mSuccessfully execute the program.\033[0m\n");
}

int main()
{
    int input;
    char customer_name[101];
    char order[101];
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &input);
        getchar();
        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE CUSTOMER'S NAME >> ");
            scanf("%[^\n]", customer_name);
            getchar();

            printf("PLEASE INPUT THE ORDER >> ");
            scanf("%[^\n]", order);
            getchar();

            add_order(customer_name, order);
            system("pause");
            break;
        case 2:
            serve_order();
            system("pause");
            break;
        case 3:
            display_all();
            system("pause");
            break;
        case 4:
            printf("PLEASE INPUT THE CUSTOMER'S NAME >> ");
            scanf("%[^\n]", customer_name);
            getchar();

            search_customer(customer_name);
            system("pause");
            break;
        case 5:
            printf("PLEASE INPUT THE CUSTOMER'S NAME >> ");
            scanf("%[^\n]", customer_name);
            getchar();

            cancel_order(customer_name);
            system("pause");
            break;
        case 6:
            printf("\033[32mCLEARING ALL THE MEMORIES...\033[0m\n");
            clear_data();
            printf("\033[32mEXITTING..\033[0m\n");
            break;
        }
    } while (input != 6);
    printf("\033[32mSuccessfully execute the program.\033[0m\n");
    return 0;
}