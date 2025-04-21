#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct request
{
    int num_priority;
    char priority[10];
    char order[100];
    struct request *next, *prev;
} *front, *rear, *curr;

void printMenu()
{
    printf("1. Give An Order\n");
    printf("2. Do An Order\n");
    printf("3. Clear All Orders\n");
    printf("4. Exit\n");
}

// 🔹 Fungsi untuk Sorting (Bubble Sort) -> Masih kurang efisien
void sortList()
{
    struct request *temp;
    curr = front;
    while (curr != NULL)
    {
        temp = rear;
        while (temp != curr)
        {
            if (temp->prev->num_priority > temp->num_priority)
            {
                // Tukar nilai (bukan pointer)
                struct request swap;
                swap.num_priority = temp->prev->num_priority;
                strcpy(swap.priority, temp->prev->priority);
                strcpy(swap.order, temp->prev->order);

                temp->prev->num_priority = temp->num_priority;
                strcpy(temp->prev->priority, temp->priority);
                strcpy(temp->prev->order, temp->order);

                temp->num_priority = swap.num_priority;
                strcpy(temp->priority, swap.priority);
                strcpy(temp->order, swap.order);
            }
            temp = temp->prev;
        }
        curr = curr->next;
    }
}

bool checkInputPriority(const char priority[])
{
    return strcmp(priority, "LOW") == 0 ||
           strcmp(priority, "NORMAL") == 0 ||
           strcmp(priority, "HIGH") == 0;
}

// 🔹 Perbaiki parameter menjadi `const char[]` agar tidak ada warning/error
void queueData(const char order[], const char priority[])
{
    curr = (struct request *)malloc(sizeof(struct request));

    strcpy(curr->order, order);
    strcpy(curr->priority, priority);
    if (strcmp(curr->priority, "HIGH") == 0)
        curr->num_priority = 1;
    else if (strcmp(curr->priority, "NORMAL") == 0)
        curr->num_priority = 2;
    else if (strcmp(curr->priority, "LOW") == 0)
        curr->num_priority = 3;

    // Jika queue kosong
    if (front == NULL)
    {
        front = rear = curr;
        curr->next = NULL;
        curr->prev = NULL;
    }
    // Jika queue tidak kosong
    else
    {
        rear->next = curr;
        curr->prev = rear;
        rear = rear->next;
        rear->next = NULL;
    }
}

void giveAnOrder()
{
    int strlength = 0;
    char order[100], priority[100];

    do
    {
        printf("Input your order [10 - 20 characters]: ");
        scanf(" %[^\n]", order);
        getchar();
        strlength = strlen(order);
    } while (strlength < 10 || strlength > 20);

    do
    {
        printf("Input your priority [LOW, NORMAL, HIGH]: ");
        scanf(" %[^\n]", priority);
        getchar();
    } while (!checkInputPriority(priority));

    queueData(order, priority);
    printf("Your order \"%s\" with \"%s\" priority has been queued!\n\n", order, priority);
}

void printQueue()
{
    if (front == NULL)
    {
        printf("Orders Are Empty\n");
    }
    else
    {
        curr = front;
        while (curr != NULL)
        {
            printf("%-7s %s (%d)\n", curr->priority, curr->order, curr->num_priority);
            curr = curr->next;
        }
    }
    printf("\n");
}

void clearOrders()
{
    if (front == NULL)
    {
        printf("Orders Are Empty\n");
    }
    else
    {
        while (front != NULL)
        {
            curr = front;
            front = front->next;
            free(curr);
        }
        printf("All Orders Have Been Cleared\n");
    }
}

void doAnOrder()
{
    if (front == NULL)
    {
        printf("Orders Are Empty\n");
    }
    else if (front == rear)
    {
        curr = front;
        printf("Order \"%s\" with \"%s\" has been done!\n", curr->order, curr->priority);
        front = rear = NULL;
        free(curr);
    }
    else
    {
        curr = front;
        printf("Order \"%s\" with \"%s\" has been done!\n", curr->order, curr->priority);
        front = front->next;
        free(curr);
    }
}

int main()
{
    // ✅ DATA AWAL tanpa warning/error
    queueData("RHIOSUTOYO1", "LOW");
    queueData("RHIOSUTOYO2", "LOW");
    queueData("RHIOSUTOYO3", "HIGH");
    queueData("RHIOSUTOYO4", "HIGH");
    queueData("RHIOSUTOYO5", "NORMAL");
    queueData("RHIOSUTOYO6", "NORMAL");

    int input = 0;
    do
    {
        sortList();
        printQueue();
        printMenu();

        do
        {
            printf("Please input your choice: ");
            scanf("%d", &input);
            getchar();
            switch (input)
            {
            case 1:
                giveAnOrder();
                break;
            case 2:
                doAnOrder();
                break;
            case 3:
                clearOrders();
                break;
            }
        } while (input < 1 || input > 4);
    } while (input != 4);

    return 0;
}
