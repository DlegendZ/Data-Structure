#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;

    struct node *next;
    struct node *prev;
};

struct node *head = NULL, *tail = NULL, *temp = NULL, *curr = NULL;

struct node *create_new_node(int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    if (!new_node)
    {
        printf("FAIL TO CREATE A NEW NODE.\n");
        return NULL;
    }

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void push_head(int value)
{
    struct node *new_node = create_new_node(value);

    if (!new_node)
    {
        printf("FAIL TO ADD NEW NODE.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_node;
    }
    else
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

void push_tail(int value)
{
    struct node *new_node = create_new_node(value);

    if (!new_node)
    {
        printf("FAIL TO ADD NEW NODE.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_node;
    }
    else
    {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
}

void push_mid(int value)
{
    struct node *new_node = create_new_node(value);

    if (!new_node)
    {
        printf("FAIL TO ADD NEW NODE.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_node;
    }
    else if (head->value > new_node->value)
    {
        push_head(value);
    }
    else if (tail->value <= new_node->value)
    {
        push_tail(value);
    }
    else
    {
        curr = head->next;
        while (curr != NULL)
        {
            if (curr->value > new_node->value)
            {
                new_node->prev = curr->prev;
                curr->prev->next = new_node;
                new_node->next = curr;
                curr->prev = new_node;
                break;
            }
            curr = curr->next;
        }
    }
}

void pop_head()
{
    if (head == NULL)
    {
        printf("LINKED LIST IS EMPTY.\n");
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
}

void pop_tail()
{
    if (head == NULL)
    {
        printf("LINKED LIST IS EMPTY.\n");
        return;
    }

    if (head == tail)
    {
        temp = head;
        head = tail = NULL;
    }
    else
    {
        temp = tail;
        tail = tail->prev;
        tail->next = NULL;
    }

    free(temp);
}

void pop_mid(int value)
{
    if (head == NULL)
    {
        printf("LINKED LIST IS EMPTY.\n");
        return;
    }

    if (head == tail && head->value == value)
    {
        temp = head;
        head = tail = NULL;
    }
    else if (head->value == value)
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
    }
    else if (tail->value == value)
    {
        temp = tail;
        tail = tail->prev;
        tail->next = NULL;
    }
    else
    {
        printf("yes");
        curr = head->next;
        while (curr != NULL)
        {
            if (curr->value == value)
            {
                temp = curr;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                break;
            }
            curr = curr->next;
        }
    }

    free(temp);
}

void menu()
{
    printf("=== LINKED LIST SYSTEM ===\n");
    printf("1. PUSH HEAD.\n");
    printf("2. PUSH TAIL.\n");
    printf("3. PUSH MID.\n");
    printf("4. POP HEAD.\n");
    printf("5. POP TAIL.\n");
    printf("6. POP MID.\n");
    printf("7. DISPLAY.\n");
    printf("8. EXIT.\n");
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
}

void display_menu()
{
    curr = head;
    while (curr != NULL)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main()
{
    int input;
    int value;
    do
    {
        system("cls");
        menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE VALUE >> ");
            scanf("%d", &value);
            getchar();
            push_head(value);
            system("pause");
            break;
        case 2:
            printf("PLEASE INPUT THE VALUE >> ");
            scanf("%d", &value);
            getchar();
            push_tail(value);
            system("pause");
            break;
        case 3:
            printf("PLEASE INPUT THE VALUE >> ");
            scanf("%d", &value);
            getchar();
            push_mid(value);
            system("pause");
            break;
        case 4:
            pop_head();
            system("pause");
            break;
        case 5:
            pop_tail();
            system("pause");
            break;
        case 6:
            printf("PLEASE INPUT THE VALUE >> ");
            scanf("%d", &value);
            getchar();
            pop_mid(value);
            system("pause");
            break;
        case 7:
            display_menu();
            system("pause");
            break;
        case 8:
            clear_memories();
            break;
        }
    } while (input != 8);
    return 0;
}