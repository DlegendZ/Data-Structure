#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 101

typedef struct node
{
    char op;
    struct node *next;
} node;

node *head = NULL, *tail = NULL;

node *create_node(char op)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        return NULL;
    }
    new_node->op = op;
    new_node->next = NULL;
    return new_node;
};

void push_head(char op)
{
    node *new_node = create_node(op);
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

char pop_head()
{
    node *temp = head;
    char op = temp->op;
    if (head == tail)
    {
        head = tail = NULL;
    }
    else
    {
        head = head->next;
    }

    free(temp);
    return op;
}

char top()
{
    if (!head)
    {
        return '\0';
    }
    char op = head->op;
    return op;
}

void reverse_string(char *string)
{
    int len = strlen(string);
    char temp[len + 1] = {'\0'};
    for (int i = 0; i < len; i++)
    {
        temp[i] = string[len - i - 1];
    }
    strcpy(string, temp);
}

int precedence(char op)
{
    if (op == '^')
    {
        return 3;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    if (op == '+' || op == '-')
    {
        return 1;
    }
    return 0;
}

void convert_infix_to_prefix(char *infix, char *prefix)
{
    int idx = 0;
    reverse_string(infix);
    for (int i = 0; infix[i]; i++)
    {
        if (isalnum(infix[i]))
        {
            prefix[idx++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push_head(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top() != '(')
            {
                prefix[idx++] = pop_head();
            }
            pop_head();
        }
        else
        {
            while (head && precedence(top()) >= precedence(infix[i]))
            {
                prefix[idx++] = pop_head();
            }
            push_head(infix[i]);
        }
    }

    while (head)
    {
        prefix[idx++] = pop_head();
    }

    prefix[idx] = '\0';
    reverse_string(prefix);
}

int main()
{
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE INFIX FORM STRING : ");
        char infix[MAX_STRING];
        char prefix[MAX_STRING];
        scanf("%s", infix);
        getchar();

        convert_infix_to_prefix(infix, prefix);
        reverse_string(infix);
        printf("INFIX FORM : %s\n", infix);
        printf("PREFIX FORM : %s\n", prefix);
    }
    return 0;
}