#include <stdio.h>
#include <stdlib.h>

#define max 10

int q[max], front = -1, back = -1;

int is_empty()
{
    if (front == -1)
    {
        return 1;
    }
    return 0;
}

int is_full()
{
    if ((back + 1) % max == front)
    {
        return 1;
    }
    return 0;
}

void enq(int value)
{
    if (is_full())
    {
        printf("QUEUE IS FULL. CAN'T ADD ENQUEUE.\n");
        return;
    }

    if (is_empty())
    {
        front = back = 0;
    }
    else
    {
        back = (back + 1) % max;
    }

    q[back] = value;
    printf("INSERTED %d TO THE QUEUE.\n", value);
}

void deq()
{
    if (is_empty())
    {
        printf("QUEUE IS EMPTY. CAN'T DEQUEUE.\n");
        return;
    }

    int value = q[front];

    if (front == back)
    {
        front = back = -1;
    }
    else
    {
        front = (front + 1) % max;
    }

    printf("SUCCESSFULLY DEQUEUE THE VALUE %d FROM THE QUEUE.\n", value);
}

void show_queue()
{
    if (is_empty())
    {
        printf("NULL\n");
        return;
    }

    int curr = front;
    while (1)
    {
        printf("%d", q[curr]);
        if (curr == back)
            break;
        curr = (curr + 1) % max;
        printf(" -> ");
    }
    printf(" -> NULL\n");
}

void menu()
{
    printf("=== CANTEEN CIRCULAR QUEUE ===\n");
    printf("1. ENQUEUE DATA.\n");
    printf("2. DEQUEUE DATA.\n");
    printf("3. SHOW DATA.\n");
    printf("4. EXIT\n");
    printf("YOUR INPUR HERE >> ");
}

int main()
{
    int input, value;
    do
    {
        system("cls");
        menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE VALUE : ");
            scanf("%d", &value);
            getchar();

            enq(value);
            break;
        case 2:
            deq();
            break;
        case 3:
            show_queue();
            break;
        case 4:
            printf("EXITTING..THANK YOU FOR USING OUR PROGRAM.\n");
            break;
        default:
            printf("INPUT IS INVALID. PLEASE INPUT CORRECTLY.\n");
            break;
        }
        system("pause");
    } while (input != 4);
    return 0;
}