#include <stdio.h>
#include <string.h>

int check_pal(char queue[], int len, int front, int back)
{
    char temp[len];
    int i = len;
    int index = 0;
    int curr = front;
    while (i--)
    {
        temp[index] = queue[curr];
        curr = (curr + 1) % len;
        index++;
    }

    // printf("temp : %s\n", temp);

    char mirrored[len];
    for (int j = len - 1, m_ind = 0; j >= 0; j--, m_ind++)
    {
        mirrored[m_ind] = temp[j];
    }

    // printf("mirrored : %s\n", mirrored);

    for (int j = 0; j < len; j++)
    {
        if (temp[j] != mirrored[j])
            return 1;
    }

    return 0;
}

void rotate_left(char queue[], int *front, int *back, int len)
{
    *front = (*front + 1) % len;
    *back = (*back + 1) % len;
}

void show_str(char queue[], int front, int back, int len)
{
    int curr = front;
    while (1)
    {
        printf("%c", queue[curr]);
        if (curr == back)
            break;
        curr = (curr + 1) % len;
    }
}

int main()
{
    printf("Please input the number of testcase : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("Please input the string : ");
        char string[101];
        scanf("%[^\n]", string);
        getchar();

        int len = strlen(string);
        char queue[len];

        int front = 0, back;
        for (int i = 0; string[i]; i++)
        {
            queue[i] = string[i];
            back = i;
        }

        int total_rotation = 0;

        while (check_pal(queue, len, front, back) && total_rotation < len)
        {
            rotate_left(queue, &front, &back, len);
            total_rotation++;
        }

        if (!check_pal(queue, len, front, back))
        {
            printf("The palindrome version of this string is : ");
            show_str(queue, front, back, len);
            printf(" after %d times of rotation.\n", total_rotation);
        }
        else
        {
            printf("The string has no palindrome version.\n");
        }
    }
    return 0;
}