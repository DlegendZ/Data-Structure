#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct node
{
    char str[101];
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
    return new_node;
}

int hash_key(char *str)
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

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i] && strcmp(table[i]->str, new_node->str) == 0)
        {
            printf("WORD <%s> IS A DUPLICATE, SKIPPED.\n", new_node->str);
            free(new_node);
            return;
        }
    }

    int key = hash_key(str);

    while (table[key])
    {
        key = (key + 1) % MAX_SIZE;
    }

    table[key] = new_node;
    printf("WORD <%s> HAS BEEN SUCCESSFULLY SAVED IN THE TABLE.\n", table[key]->str);
}

void reset_memo()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i])
        {
            free(table[i]);
            table[i] = NULL;
        }
    }
}

void print_table()
{
    printf("HASH TABLE : \n");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (table[i])
        {
            printf("%02d. [%-10s]\n", i, table[i]->str);
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

        reset_memo();
    }
    return 0;
}