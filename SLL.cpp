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

void print_string_reversed()
{
    node *curr = head;
    while (curr)
    {
        printf("%c", curr->c);
        curr = curr->next;
    }
    printf("\n");
}

void reset_linked_list()
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
    printf("PLEASE INPUT THE NUMBER OF TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE LENGTH OF THE STRING : ");
        int n;
        scanf("%d", &n);
        getchar();

        printf("PLEASE INPUT THE STRING : ");
        char s[101];
        scanf("%s", s);
        getchar();

        for (int i = 0; i < n; i++)
        {
            add_char(s[i]);
        }

        printf("OUTPUT : ");
        print_string_reversed();

        reset_linked_list();
    }
    return 0;
}