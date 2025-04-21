#include <stdio.h>

void add_char(char c, int *front, int *back, char *queue, int k)
{
    if (((*back) + 1) % k == *front && *back != -1)
    {
        printf("CHARACTER %c IS BEING PROCESSED.\n", queue[*front]);
        *front = ((*front) + 1) % k;
    }

    *back = ((*back) + 1) % k;
    queue[*back] = c;
}

void print_string(int *front, int *back, int k, char *queue)
{
    int curr = *front;
    while (1)
    {
        printf("CHARACTER %c IS BEING PROCESSED.", queue[curr]);
        if (curr == *back)
            break;
        curr = (curr + 1) % k;
        printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE SIZE OF THE CIRCULAR QUEUE : ");
        int k;
        scanf("%d", &k);
        getchar();

        printf("PLEASE INPUT THE LENGTH OF THE STRING : ");
        int n;
        scanf("%d", &n);
        getchar();

        printf("PLEASE INPUT THE STRING : ");
        char string[101];
        scanf("%s", string);
        getchar();

        char queue[k] = {'\0'};
        int front = 0, back = -1;

        for (int i = 0; i < n && string[i]; i++)
        {
            add_char(string[i], &front, &back, queue, k);
        }

        print_string(&front, &back, k, queue);
    }
    return 0;
}