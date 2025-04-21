#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *next;
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
        if (value < head->value)
        {
            push_head(value);
            free(new_node);
        }
        else if (value >= tail->value)
        {
            push_tail(value);
            free(new_node);
        }
        else
        {
            node *curr = head;
            while (curr->next && curr->next->value <= value)
            {
                curr = curr->next;
            }
            new_node->next = curr->next;
            curr->next = new_node;
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
        node *curr = head;
        while (curr->next != tail)
        {
            curr = curr->next;
        }
        tail = curr;
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

    node *temp = NULL;
    if (head == tail && head->value == value)
    {
        temp = head;
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
            while (curr->next && curr->next->value != value)
            {
                curr = curr->next;
            }
            if (curr == tail)
            {
                printf("VALUE NOT FOUND IN THE LINKED LIST.\n");
                return;
            }

            temp = curr->next;
            curr->next = temp->next;
            free(temp);
        }
    }
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

int main()
{
    push_mid(20);
    push_mid(25);
    push_mid(15);

    pop_mid(20);
    print_all();

    return 0;
}