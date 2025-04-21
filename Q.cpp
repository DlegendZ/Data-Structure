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
        tail->next = new_node;
        tail = new_node;
    }
}

void delete_char()
{
    node *temp = head;
    head = head->next;
    printf("CHARACTER %c NOW IS BEING PROCESSED.\n", temp->c);
    free(temp);
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
    printf("PLEASE INPUT THE TESTCASE : ");
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
            add_char(s[i]);
            if (i > 1)
            {
                delete_char();
            }
        }

        printf("OUTPUT FOR THE QUEUE LEFT: ");
        print_string();

        reset_memo();
    }
    return 0;
}