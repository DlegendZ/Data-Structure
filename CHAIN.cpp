#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node
{
    char str[101];
    struct node *next;
} node;

node *table[MAX_SIZE] = {NULL};

node *create_node(char *str)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    strcpy(new_node->str, str);
    new_node->next = NULL;
    return new_node;
}

int hash(char *str)
{
    int key = 0;
    while (*str)
    {
        key += *str++;
    }
    return key % MAX_SIZE;
}

void add_node(char *str)
{
    node *new_node = create_node(str);
    int key = hash(str);

    node *curr = table[key];
    while (curr)
    {
        if (strcmp(curr->str, new_node->str) == 0)
        {
            printf("<%s> IS A DUPLICATE, SKIPPED.\n", new_node->str);
            free(new_node);
            return;
        }
        curr = curr->next;
    }

    if (!table[key])
    {
        table[key] = new_node;
    }
    else
    {
        node *curr = table[key];
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = new_node;
    }

    printf("WORD HAS BEEN SUCCESSFULLY SAVED IN THE TABLE.\n");
}

void print_table()
{
    printf("HASH TABLE : \n");

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i])
        {
            printf("%02d. ", i);
            node *curr = table[i];
            while (curr)
            {
                printf("[%-10s] -> ", curr->str);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

void reset_table()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i])
        {
            node *temp = NULL;
            while (table[i])
            {
                temp = table[i];
                table[i] = table[i]->next;
                free(temp);
            }
        }
    }
}

int main()
{
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE NUMBER OF THE STRING : ");
        int n;
        scanf("%d", &n);
        getchar();

        while (n--)
        {
            printf("PLEASE INPUT THE STRING : ");
            char str[101];
            scanf("%s", str);
            getchar();

            add_node(str);
        }

        print_table();

        reset_table();
    }
    return 0;
}