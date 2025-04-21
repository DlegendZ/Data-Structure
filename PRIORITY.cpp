#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    char string[101];
    char prior_str[10];
    int prior_num;
    struct node *next;
    struct node *prev;
} node;

node *head = NULL, *tail = NULL;

node *create_node(const char *string, int prior_num, char *prior_str)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    strcpy(new_node->string, string);
    new_node->prior_num = prior_num;
    strcpy(new_node->prior_str, prior_str);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void add_word(const char *string, int prior_num, char *prior_str)
{
    node *new_node = create_node(string, prior_num, prior_str);
    if (!head)
    {
        head = tail = new_node;
    }
    else
    {
        node *curr = head;
        while (curr && curr->prior_num >= new_node->prior_num)
        {
            curr = curr->next;
        }

        if (curr == head)
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        else if (!curr)
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        else
        {
            new_node->next = curr;
            new_node->prev = curr->prev;
            curr->prev->next = new_node;
            curr->prev = new_node;
        }
    }
}

int det_num(char *string)
{
    if (strcmp(string, "HIGH") == 0)
    {
        return 3;
    }
    if (strcmp(string, "NORMAL") == 0)
    {
        return 2;
    }
    if (strcmp(string, "LOW") == 0)
    {
        return 1;
    }
    return 0;
}

void print_string()
{
    node *curr = head;
    while (curr)
    {
        printf("PROCESSING %s WITH PRIORITY %d.\n", curr->string, curr->prior_num);
        curr = curr->next;
    }
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
    int t;
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE NUMBER OF WORD : ");
        int n;
        scanf("%d", &n);
        getchar();

        while (n--)
        {
            char string[101];
            char prior_str[10];
            scanf("%s %s", string, prior_str);
            getchar();

            int prior_num = det_num(prior_str);
            add_word(string, prior_num, prior_str);
        }

        print_string();

        reset_memo();
    }
    return 0;
}