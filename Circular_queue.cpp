#include <stdio.h>
#define SIZE 5

int queue[SIZE] = {}, rear = -1, front = -1;

int is_full()
{
    return ((rear + 1) % SIZE == front);
}

int is_empty()
{
    return (front == -1);
}

void enqueue(int value)
{
    if (is_full())
    {
        printf("The queue is full. There is no space left to enqueue.\n");
        return;
    }

    if (is_empty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % SIZE;
    }

    queue[rear] = value;
    printf("enqueued : %d\n", value);
}

void dequeue()
{
    if (is_empty())
    {
        printf("Queue is empty. There is no data to delete.\n");
        return;
    }

    int value = queue[front];

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % SIZE;
    }

    printf("dequeued : %d\n", value);
}

void display_queue()
{
    if (is_empty())
    {
        printf("Queue is empty.\n");
        return;
    }

    int i = front;
    printf("Queue: ");
    while (1)
    {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    display_queue();

    dequeue();
    dequeue();
    dequeue();
    display_queue();
    return 0;
}