#include <stdio.h>

int front, rear; // 1

int is_full(int max)
{
    if ((rear + 1) % max == front)
    {
        return 1;
    }
    return 0;
}

int is_empty()
{
    if (front == -1) // 2
    {
        return 1;
    }
    return 0;
}

void add_char(char c, char queue[], int max)
{
    if (is_full(max))
    {
        front = (front + 1) % max;
        rear = (rear + 1) % max;
    }
    else if (is_empty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % max;
    }

    queue[rear] = c;
}

void print_string(char queue[], int max)
{
    int curr = front; // 3
    while (1)
    {
        printf("%c", queue[curr]);
        if (curr == rear)
            break;
        curr = (curr + 1) % max;
    }
    printf("\n"); // 4
}

int main()
{
    printf("Please input how many testcase : ");
    int t;
    scanf("%d", &t);
    getchar();

    for (int i = 0; i < t; i++)
    {
        front = rear = -1;
        printf("Please input what is the max : ");
        int max;
        scanf("%d", &max);
        getchar();
        char queue[max]; // 5
        printf("Please input how many character : ");
        int char_count;
        scanf("%d", &char_count);
        getchar();

        printf("Please input the string : ");
        char string[char_count];
        scanf("%s", string);
        getchar();

        for (int j = 0; j < char_count; j++)
        {
            add_char(string[j], queue, max);
        }

        print_string(queue, max);
    }
    return 0;
}