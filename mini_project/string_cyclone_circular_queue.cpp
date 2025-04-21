#include <stdio.h>
#include <string.h>

void left_rotate(char queue[], int *front, int *back, int len)
{
    // hello ohell lohel
    *front = (*front + (len - 1)) % len;
    *back = (*back + (len - 1)) % len;
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
    printf("\n");
}

int main()
{
    printf("please input the number of testcase : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("please input the string : ");
        char string[101];
        scanf("%s", string);
        getchar();

        printf("please input the number of left rotate : ");
        int n;
        scanf("%d", &n);
        getchar();

        int len = strlen(string);
        char queue[len];

        int front = 0, back;
        for (int i = 0; string[i]; i++)
        {
            queue[i] = string[i];
            back = i;
        }

        while (n--)
        {
            left_rotate(queue, &front, &back, len);
        }

        show_str(queue, front, back, len);
    }
    return 0;
}

// #include <stdio.h>
// #include <string.h>

// void left_rotate(char queue[], int *front, int *back, int len)
// {
//     *front = (*front + (len - 1)) % len;
//     *back = (*back + (len - 1)) % len;
// }

// void show_string(int front, int back, char queue[], int len)
// {
//     int curr = front;
//     while (1)
//     {
//         printf("%c", queue[curr]);
//         if (curr == back)
//             break;
//         curr = (curr + 1) % len;
//     }
//     printf("\n");
// }

// int main()
// {
//     printf("Please input the number of testcase : ");
//     int t;
//     scanf("%d", &t);
//     getchar();

//     while (t--)
//     {
//         char string[101];
//         printf("Please input the string : ");
//         scanf("%s", string);
//         getchar();

//         int n;
//         printf("Please input the number of rotation to the left : ");
//         scanf("%d", &n);
//         getchar();

//         int front = 0, back;
//         int len = strlen(string);
//         char queue[len];
//         for (int i = 0; string[i]; i++)
//         {
//             queue[i] = string[i];
//             back = i;
//         }

//         while (n--)
//         {
//             left_rotate(queue, &front, &back, len);
//         }

//         show_string(front, back, queue, len);
//     }
//     return 0;
// }
