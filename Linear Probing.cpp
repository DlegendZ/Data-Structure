#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Data
{
    char name[101];
    int age;
} Data;

Data *table[SIZE] = {NULL}; // Inisialisasi tabel ke NULL

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
    return newData;
}

int hash(const char *name)
{
    int total = 0;
    while (*name)
    {
        total += *name++;
    }
    printf("%d\n", total);
    return total % SIZE;
}

void insertData(const char *name, int age)
{
    Data *newData = create_new_data(name, age);
    if (!newData)
        return;

    int key = hash(name);
    int startKey = key, attempts = 0;

    while (table[key] != NULL)
    {
        key = (key + 1) % SIZE;
        attempts++;
        if (key == startKey || attempts >= SIZE)
        {
            printf("Hash table is full! Cannot insert %s.\n", name);
            free(newData);
            return;
        }
    }
    table[key] = newData;
}

void deleteData(const char *name)
{
    int key = hash(name);
    int startKey = key, attempts = 0;

    while (table[key] != NULL)
    {
        if (strcmp(table[key]->name, name) == 0)
        {
            free(table[key]);
            table[key] = NULL;
            printf("%s deleted from hash table.\n", name);
            return;
        }
        key = (key + 1) % SIZE;
        attempts++;
        if (key == startKey || attempts >= SIZE)
            break;
    }
    printf("%s not found in hash table.\n", name);
}

void printTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%02d. ", i);
        if (table[i])
        {
            printf("[ %-10s | %-3d]", table[i]->name, table[i]->age);
        }
        printf("\n");
    }
}

void freeTable()
{
    for (int i = 0; i < SIZE; i++)
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

    freeTable(); // Bebaskan semua memori yang dialokasikan
    return 0;
}