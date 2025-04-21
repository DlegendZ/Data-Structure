#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef struct node
{
    char str[101];
} node;

node *table[MAX_SIZE] = {NULL};

node *create_node(const char *str)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    strcpy(new_node->str, str);
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

void insert_data(char *str)
{
    node *new_node = create_node(str);
    int key = hash(str);
    int start = key;
    while (table[key])
    {
        if ((key + 1) % MAX_SIZE == start)
        {
            printf("TABLE IS FULL.\n");
            free(new_node);
            return;
        }
        key = (key + 1) % MAX_SIZE;
    }
    table[key] = new_node;
}

void delete_data(char *str)
{
    int key = hash(str);
    int start = key;

    while (table[key])
    {
        if (strcmp(table[key]->str, str) == 0)
        {
            free(table[key]);
            table[key] = NULL;
            printf("SUCCESSFULLY DELETED FROM TABLE.\n");
            return;
        }

        if ((key + 1) % MAX_SIZE == start)
        {
            break;
        }

        key = (key + 1) % MAX_SIZE;
    }

    printf("STRING NOT FOUND IN THE TABLE.\n");
}

void print_table()
{
    printf("HASH TABLE : ");
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%02d. ", i);
        if (table[i])
        {
            printf("[%-10s]\n", table[i]->str);
        }
        else
        {
            printf("NULL\n");
        }
    }
}

void free_table()
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

int main()
{
    insert_data("RAYNALD");
    insert_data("NIGEL");
    insert_data("KIMSYEL");

    print_table();
    free_table();
    return 0;
}