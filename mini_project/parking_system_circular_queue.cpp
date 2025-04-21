#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX], front = -1, rear = -1;

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
    if ((rear + 1) % MAX == front)
    {
        return 1;
    }
    return 0;
}

void park_car(int value)
{
    if (is_full())
    {
        printf("PARKING SLOT IS FULL.\n");
        return;
    }

    if (is_empty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = value;
    printf("SUCCESSFULLY PARK %d.\n", value);
}

void car_exit()
{
    if (is_empty())
    {
        printf("PARKING SLOT IS EMPTY.\n");
        return;
    }

    int car = queue[front];

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }

    printf("SUCCESSFULLY EXITTING THE CAR %d.\n", car);
}

void show_car()
{
    if (is_empty())
    {
        printf("NULL\n");
        return;
    }

    int curr = front;
    while (1)
    {
        printf("%d", queue[curr]);
        if (curr == rear)
            break;
        printf(" -> ");
        curr = (curr + 1) % MAX;
    }
    printf(" -> NULL\n");
}

void menu()
{
    printf("=== PARKING SYSTEM CIRCULAR QUEUE ===\n");
    printf("1. PARK CAR.\n");
    printf("2. EXIT THE CAR.\n");
    printf("3. SHOW THE PARKED CAR.\n");
    printf("4. EXIT.\n");
    printf("YOUR INPUT HERE >> ");
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
            printf("PLEASE INPUT THE CAR : ");
            scanf("%d", &value);
            getchar();

            park_car(value);
            break;
        case 2:
            car_exit();
            break;
        case 3:
            show_car();
            break;
        case 4:
            printf("EXITTING..");
            break;
        default:
            printf("YOUR INPUR IS INVALID.\n");
        }
        system("pause");
    } while (input != 4);
    printf("SUCCESSFULLY EXITTING THE PROGRAM.\n");
    return 0;
}