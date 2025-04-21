#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shelf_quota = 0;

struct book
{
    char book_name[101];

    struct book *next;
    struct book *prev;
};

struct book *head = NULL, *tail = NULL, *temp = NULL, *curr = NULL;

struct book *create_new_book_node(char book_name[])
{
    struct book *new_book = (struct book *)malloc(sizeof(struct book));
    if (!new_book)
    {
        printf("FAIL TO CREATE A NEW BOOK NODE.\n");
        return NULL;
    }
    strcpy(new_book->book_name, book_name);
    new_book->next = NULL;
    new_book->prev = NULL;
    return new_book;
}

void add_book(char book_name[])
{
    struct book *new_book = create_new_book_node(book_name);

    if (!new_book)
    {
        printf("FAIL TO ADD A NEW BOOK.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_book;
    }
    else
    {
        new_book->next = head;
        head->prev = new_book;
        head = new_book;
    }

    shelf_quota++;
}

void remove_book()
{
    if (head == NULL)
    {
        printf("SHELF IS EMPTY.\n");
        return;
    }

    if (head == tail)
    {
        temp = head;
        head = tail = NULL;
    }
    else
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
    shelf_quota--;
}

void view_shelf()
{
    printf("=== SHELF ===\n");

    if (head == NULL)
    {
        printf("NO BOOK STORED IN THE SHELF.\n");
        return;
    }

    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s.\n", i, curr->book_name);
        curr = curr->next;
        i++;
    }
}

void menu()
{
    printf("=== BOOK SHELF SYSTEM ===\n");
    printf("1. ADD BOOK.\n");
    printf("2. REMOVE BOOK.\n");
    printf("3. VIEW SHELF.\n");
    printf("4. EXIT.\n");
    printf("SHELF QUOTA USED : %d/10.\n", shelf_quota);
    printf("YOUR INPUT HERE >> ");
}

void clear_memories()
{
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    shelf_quota = 0;
}

int main()
{
    int input;
    char book_name[101];

    do
    {
        system("cls");
        menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            if (shelf_quota < 10)
            {
                printf("PLEASE INPUT THE BOOK'S NAME : ");
                scanf("%s", book_name);
                getchar();

                add_book(book_name);
                system("pause");
            }
            else
            {
                printf("SHELF QUOTE HAS REACHED 10. CAN'T ADD MORE BOOKS.\n");
                system("pause");
            }
            break;

        case 2:
            remove_book();
            system("pause");
            break;
        case 3:
            view_shelf();
            system("pause");
            break;
        case 4:
            clear_memories();
            break;
        }
    } while (input != 4);

    return 0;
}