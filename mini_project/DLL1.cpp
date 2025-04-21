#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} node;

node *head = NULL, *tail = NULL;

node *create_node(int value)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void push_head(int value)
{
    node *new_node = create_node(value);

    if (!head)
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
    node *new_node = create_node(value);

    if (!head)
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
    node *new_node = create_node(value);

    if (!head)
    {
        head = tail = new_node;
    }
    else
    {
        if (head->value > new_node->value)
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        else if (tail->value <= new_node->value)
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        else
        {
            node *curr = head;
            while (curr && curr->value <= new_node->value)
            {
                curr = curr->next;
            }
            new_node->next = curr;
            new_node->prev = curr->prev;
            curr->prev->next = new_node;
            curr->prev = new_node;
        }
    }
}

void pop_head()
{
    if (!head)
    {
        printf("LINKED LIST IS EMPTY.\n");
        return;
    }

    node *temp = head;
    if (head == tail)
    {
        head = tail = NULL;
    }
    else
    {
        head = head->next;
        head->prev = NULL;
    }
    free(temp);
}

void pop_tail()
{
    if (!head)
    {
        printf("LINKED LIST IS EMPTY.\n");
        return;
    }

    node *temp = tail;
    if (head == tail)
    {
        head = tail = NULL;
    }
    else
    {
        tail = tail->prev;
        tail->next = NULL;
    }
    free(temp);
}

void pop_mid(int value)
{
    if (!head)
    {
        printf("LINKED LIST IS EMPTY.\n");
        return;
    }

    if (head == tail && head->value == value)
    {
        node *temp = head;
        head = tail = NULL;
        free(temp);
    }
    else
    {
        if (head->value == value)
        {
            pop_head();
        }
        else if (tail->value == value)
        {
            pop_tail();
        }
        else
        {
            node *curr = head;
            while (curr)
            {
                if (curr->value == value)
                {
                    node *temp = curr;
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    free(temp);
                    break;
                }
                curr = curr->next;
            }

            if (!curr)
            {
                printf("VALUE NOT FOUND IN THE LINKED LIST.\n");
            }
        }
    }
}

void reset_linked_list()
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

void print_all()
{
    node *curr = head;
    while (curr)
    {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main()
{
    push_mid(20);
    push_mid(25);
    push_mid(15);

    pop_mid(20);
    print_all();

    return 0;
}