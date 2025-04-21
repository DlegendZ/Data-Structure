#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Data
{
    char name[101];
    int age;
    struct Data *next;
} Data;

Data *table[SIZE] = {NULL};

Data *create_new_data(const char *name, int age)
{
    Data *newData = (Data *)malloc(sizeof(Data));
    if (!newData)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newData->name, name);
    newData->age = age;
    newData->next = NULL;
    return newData;
}

int hash(const char *name)
{
    int total = 0;
    while (*name)
    {
        total += *name++;
    }
    return total % SIZE;
}

void insertData(const char *name, int age)
{
    Data *newData = create_new_data(name, age);
    if (!newData)
        return;

    int key = hash(name);
    if (!table[key])
    {
        table[key] = newData;
    }
    else
    {
        Data *curr = table[key];
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = newData;
    }
}

void deleteData(const char *name)
{
    int key = hash(name);
    Data *curr = table[key];
    Data *prev = NULL;

    while (curr)
    {
        if (strcmp(curr->name, name) == 0)
        {
            if (!prev)
            {
                table[key] = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            printf("%s deleted from hash table.\n", name);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("%s not found in hash table.\n", name);
}

void printTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%2d. ", i);
        Data *curr = table[i];
        while (curr)
        {
            printf("[ %-10s | %-3d ] -> ", curr->name, curr->age);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

void freeTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        Data *curr = table[i];
        while (curr)
        {
            Data *temp = curr;
            curr = curr->next;
            free(temp);
        }
        table[i] = NULL;
    }
}

int main()
{
    insertData("Niko", 40);
    insertData("Joshua", 50);
    insertData("okiN", 50);
    insertData("huaJos", 50);

    printf("\nHash Table:\n");
    printTable();

    printf("\nDeleting Joshua...\n");
    deleteData("Joshua");

    printf("\nUpdated Hash Table:\n");
    printTable();

    freeTable(); // Bebaskan semua memori
    return 0;
}
