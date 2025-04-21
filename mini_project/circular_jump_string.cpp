#include <stdio.h>
#include <string.h>

int total_take;

void jnt(char queue[], int len, int *front, int jump)
{
    *front = (*front + (jump - 1)) % len;
    while (queue[*front] == '.')
    {
        *front = (*front + 1) % len;
    }
    printf("%c", queue[*front]);
    queue[*front] = '.';
    total_take++;
}

int main()
{
    printf("Please input the number of testcase : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        total_take = 0;

        printf("Please input the string : ");
        char str[101];
        scanf("%s", str);
        getchar();

        printf("Please input how many character to jump : ");
        int jump;
        scanf("%d", &jump);
        getchar();

        int len = strlen(str);
        char queue[len];

        int front = 0;
        for (int i = 0; str[i]; i++)
        {
            queue[i] = str[i];
        }

        while (total_take < len)
        {
            jnt(queue, len, &front, jump);
        }

        printf("\n");
    }
    return 0;
}