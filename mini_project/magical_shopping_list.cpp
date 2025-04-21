#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item
{
    char item_name[101];
    struct item *next;
};

struct item *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct item *create_item_node(char item_name[])
{
    struct item *new_item = (struct item *)malloc(sizeof(struct item));

    if (!new_item)
    {
        printf("Failed to create new item node.\n");
        return NULL;
    }

    strcpy(new_item->item_name, item_name);
    new_item->next = NULL;
    return new_item;
}

void add_item(char item_name[])
{
    struct item *new_item = create_item_node(item_name);

    if (!new_item)
    {
        printf("Failed to add item to the shopping list.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_item;
    }
    else
    {
        new_item->next = head;
        head = new_item;
    }

    printf("\033[32mSuccessfully\033[0m executing the program.\n");
}

void remove_item(char item_name[])
{
    if (head == NULL)
    {
        printf("Shopping list is empty. Couldn't find the exact item.\n");
        return;
    }
    else if (head == tail && (strcmp(item_name, head->item_name) == 0))
    {
        temp = head;
        head = tail = NULL;
    }
    else
    {
        if (strcmp(head->item_name, item_name) == 0)
        {
            temp = head;
            head = head->next;
        }
        else if (strcmp(tail->item_name, item_name) == 0)
        {
            curr = head;
            while (curr->next != tail)
            {
                curr = curr->next;
            }
            temp = tail;
            tail = curr;
            tail->next = NULL;
        }
        else
        {
            curr = head;
            while (curr->next != NULL)
            {
                if ((strcmp(curr->next->item_name, item_name) == 0))
                {
                    temp = curr->next;
                    curr->next = temp->next;
                    break;
                }
                curr = curr->next;
            }

            if (curr->next == NULL)
            {
                printf("Oops, looks like there is no such item in your shopping list.\n");
                return;
            }
        }
    }

    free(temp);
    printf("\033[32mSuccessfully\033[0m executing the program.\n");
}

void display_shopping_list()
{
    if (head == NULL)
    {
        printf("There is no item in the shopping list.\n");
        return;
    }

    printf("Your shopping list :\n");
    int i = 1;
    curr = head;
    while (curr != NULL)
    {
        printf("%d. %s\n", i, curr->item_name);
        i++;
        curr = curr->next;
    }

    printf("\033[32mSuccessfully\033[0m executing the program.\n");
}

void print_menu()
{
    printf("=== Magical shopping List Menu ===\n");
    printf("1. Add item to the shopping list.\n");
    printf("2. Remove item from the shopping list.\n");
    printf("3. Display all items in the shopping list.\n");
    printf("4. Exit the program.\n");
    printf("Your input here >> ");
}

void remove_all_data()
{
    while (head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
    tail = NULL;
    printf("\033[32mSuccessfully\033[0m executing the program.\n");
}

int main()
{
    int input;
    char item_name[101];
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Please input the name of item >> ");
            scanf("%[^\n]", item_name);
            getchar();
            add_item(item_name);
            system("pause");
            break;
        case 2:
            printf("Please input the name of item >> ");
            scanf("%[^\n]", item_name);
            getchar();
            remove_item(item_name);
            system("pause");
            break;
        case 3:
            display_shopping_list();
            system("pause");
            break;
        case 4:
            printf("\033[32mClearing memories..\033[0m\n");
            remove_all_data();
            printf("Exitting..\n");
            break;
        }
    } while (input != 4);

    printf("\033[32mSuccessfully\033[0m executing the program. Enjoy your day sir!\n");
    return 0;
}