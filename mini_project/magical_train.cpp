#include <stdio.h>
#include <stdlib.h>

int total_carriages = 0;

struct carriage
{
    int value;
    struct carriage *next;
    struct carriage *prev;
};

struct carriage *head = NULL, *tail = NULL, *curr = NULL;

struct carriage *create_new_carriage(int value)
{
    struct carriage *new_carriage = (struct carriage *)malloc(sizeof(struct carriage));

    if (!new_carriage)
    {
        printf("Fail to create a new carriage!\n");
        return NULL;
    }

    new_carriage->value = value;
    new_carriage->next = NULL;
    new_carriage->prev = NULL;
    return new_carriage;
}

void add_carriage(int value)
{
    struct carriage *new_carriage = create_new_carriage(value);

    if (!new_carriage)
    {
        printf("Fail to add child!\n");
        return;
    }

    total_carriages++;

    if (head == NULL)
    {
        head = tail = new_carriage;
    }
    else
    {
        head->prev = new_carriage;
        new_carriage->next = head;
        head = new_carriage;
    }

    printf("\033[32mSuccessfully\033[0m executing the program!\n");
}

void display_carriages()
{
    printf("Carriage(s) from front to behind : ");
    curr = head;
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }

    printf("NULL\n");

    printf("Carriage(s) from behind to front : ");
    curr = tail;
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->prev;
    }

    printf("NULL\n");

    printf("\033[32mSuccessfully\033[0m executing the program!\n");
}

void remove_all_carriages()
{
    while (head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
    tail = NULL;

    total_carriages = 0;
    printf("\033[32mSuccessfully\033[0m executing the program!\n");
}

void print_menu()
{
    printf("=== Magical Train Menu ===\n");
    printf("1. add_carriage\n");
    printf("2. display all the carriages\n");
    printf("3. remove all the carriages\n");
    printf("4. Exit\n");
    printf("Total carriages : %d\n", total_carriages);
    printf("Your input here >> ");
}

int main()
{
    int input;
    int value;
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Please input the carriage's value >> ");
            scanf("%d", &value);
            getchar();
            add_carriage(value);
            system("pause");
            break;
        case 2:
            display_carriages();
            system("pause");
            break;
        case 3:
            remove_all_carriages();
            system("pause");
            break;
        case 4:
            total_carriages = 0;
            printf("Clearing memories..\n");
            remove_all_carriages();
            printf("Exitting..\n");
        }
    } while (input != 4);

    printf("\033[32mSuccessfully\033[0m executing the program! Enjoy your day sir!\n");

    return 0;
}