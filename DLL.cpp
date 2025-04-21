#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    char c;
    struct node *next;
    struct node *prev;
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
    new_node->prev = NULL;
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
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

void print_string()
{
    node *curr = head;
    while (curr)
    {
        printf("%c", curr->c);
        curr = curr->next;
    }
    printf("\n");
}

int is_palindrome()
{
    node *check_front = head;
    node *check_back = tail;
    while ((check_front && check_back))
    {
        if (check_front->c != check_back->c)
        {
            return 0;
        }
        check_front = check_front->next;
        check_back = check_back->prev;
    }
    return 1;
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
        printf("PLEASE INPUT THE STRING : ");
        char s[101];
        scanf("%s", s);
        getchar();

        for (int i = 0; s[i]; i++)
        {
            add_char(tolower(s[i]));
        }

        if (is_palindrome())
        {
            printf("YOUR STRING IS PALINDROME.\n");
        }
        else
        {
            printf("YOUR STRING IS NOT A PALINDROME.\n");
        }

        reset_memo();
    }
    return 0;
}