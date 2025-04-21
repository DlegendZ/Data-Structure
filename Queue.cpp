#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
let say there is a shop.

And there are a lot of customers that
want to buy something from that shop.

But, because of the limitation on the cashier.
The customer can only be served one by one.
And the cashier will serve using FIFO concept.
*/

// customer
struct customer
{
    char name[101];
    char product[101];

    struct customer *next;
} *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct customer *createNewCustomer(char name[101], char product[101])
{
    struct customer *newCustomer = (struct customer *)malloc(sizeof(struct customer));

    strcpy(newCustomer->name, name);
    strcpy(newCustomer->product, product);

    return newCustomer;
}

void pushTail(char name[101], char product[101])
{
    struct customer *newCustomer = createNewCustomer(name, product);

    // if queue is empty
    if (head == NULL)
    {
        head = tail = newCustomer;
    }
    else
    {
        tail->next = newCustomer;
        tail = newCustomer;
    }
}

struct customer *popHead()
{
    // if queue is empty
    if (head == NULL)
    {
        printf("The queue is empty\n");
        return NULL;
    }

    // if there is only one element in queue
    if (head == tail)
    {
        temp = head;
        head = tail = NULL;
    }
    else
    {
        temp = head;
        head = head->next;
    }

    //	free(temp);
    return temp;
}

void addCustomer()
{
    char name[101];
    char product[101];

    printf("Customer Name: ");
    scanf("%[^\n]", name);
    getchar();

    printf("Customer's Product: ");
    scanf("%[^\n]", product);
    getchar();

    pushTail(name, product);
    printf("Successfully add new customer\n");
    // to pause the terminal until any key got pressed
    system("pause");
}

void serveCustomer()
{
    temp = popHead();

    if (temp == NULL)
    {
        printf("There is no customer.\n");
        system("pause");
        return;
    }

    printf("Customer's Detail: \n'");
    printf("Name : %s\n", temp->name);
    printf("Product : %s\n", temp->product);

    printf("==============");
    printf("Successfully add new customer\n");

    system("pause");

    free(temp);
}

void printQueue()
{
    curr = head;

    int count = 1;

    if (curr == NULL)
    {
        printf("The queue is empty.\n");
        system("pause");
        return;
    }

    while (curr != NULL)
    {
        printf("====[Customer %d]====\n", count);
        printf("Name: %s\n", curr->name);
        printf("Product : %s\n", curr->product);
        printf("\n");

        curr = curr->next;
        count++;
    }
    system("Pause");
}

int main()
{
    int input;

    do
    {
        // clear screen
        system("cls");

        printf("==== [Main Menu] ====\n");
        printf("1. Add Customer\n");
        printf("2. Serve Customer\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");

        printf(">> ");
        scanf("%d", &input);
        getchar();

        if (input == 1)
        {
            addCustomer();
        }
        else if (input == 2)
        {
            serveCustomer();
        }
        else if (input == 3)
        {
            printQueue();
        }
    } while (input != 4);

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

// void push_tail(int value)
// {
//     struct node *new_node = create_new_node(value);

//     if (head == NULL)
//     {
//         head = tail = new_node;
//     }
//     else
//     {
//         tail->next = new_node;
//         tail = new_node;
//     }
// }

// void pop_head()
// {
//     if (head == NULL)
//     {
//         printf("There is no data in the linked-list.\n");
//     }
//     else if (head == tail)
//     {
//         temp = head;
//         head = tail = NULL;
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
//     push_tail(10);
//     push_tail(100);
//     print_all();
//     pop_head();
//     print_all();
//     return 0;
// }