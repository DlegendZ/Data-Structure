#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char c;
    struct node *next;
} node;

node *head = NULL, *tail = NULL;

node *create_node(char c)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->c = c;
    new_node->next = NULL;
    return new_node;
}

void add_char(char c)
{
    node *new_node = create_node(c);
    if (!head)
    {
        head = tail = new_node;
    }
    else
    {
        new_node->next = head;
        head = new_node;
    }
}

void match_and_pop(int value, int *check)
{
    if (!head)
    {
        *check = 0;
        return;
    }

    if (value == 1 && head->c != '(' ||
        value == 2 && head->c != '[' ||
        value == 3 && head->c != '{')
    {
        *check = 0;
        return;
    }

    node *temp = NULL;
    temp = head;
    if (head == tail)
    {
        head = tail = NULL;
    }
    else
    {
        head = head->next;
    }
    free(temp);
}

void reset_memo()
{
    node *temp = NULL;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

int main()
{
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        char s[101];
        printf("PLEASE INPUT THE STRING : ");
        scanf("%s", s);
        getchar();

        int check = 1;
        for (int i = 0; s[i] && check; i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            {
                add_char(s[i]);
            }
            else
            {
                if (s[i] == ')')
                {
                    match_and_pop(1, &check);
                }
                if (s[i] == ']')
                {
                    match_and_pop(2, &check);
                }
                if (s[i] == '}')
                {
                    match_and_pop(3, &check);
                }
            }
        }

        if (check && !head)
        {
            printf("OUTPUT : YES\n");
        }
        else
        {
            printf("OUTPUT : NO\n");
        }
        reset_memo();
    }
    return 0;
}