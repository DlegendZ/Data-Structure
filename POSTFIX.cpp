#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
}

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
    char op = '\0';
    if (head == tail)
    {
        head = tail = NULL;
    }
    else
    {
        head = head->next;
    }
    op = temp->op;
    free(temp);
    return op;
}

char top()
{
    char op;
    if (!head)
    {
        return '\0';
    }
    op = head->op;
    return op;
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

void convert_infix_to_postfix(char *infix, char *postfix)
{
    int index = 0;

    for (int i = 0; infix[i]; i++)
    {
        if (isalnum(infix[i]))
        {
            postfix[index++] = infix[i];
        }
        else
        {
            if (infix[i] == '(')
            {
                push_head(infix[i]);
            }
            else if (infix[i] == ')')
            {
                while (top() != '(')
                {
                    postfix[index++] = pop_head();
                }
                pop_head();
            }
            else
            {
                while (head && precedence(top()) >= precedence(infix[i]))
                {
                    postfix[index++] = pop_head();
                }
                push_head(infix[i]);
            }
        }
    }

    while (head)
    {
        postfix[index++] = pop_head();
    }
    postfix[index] = '\0';
}

int main()
{
    printf("PLEASE INPUT THE NUMBER OF THE TESTCASE : ");
    int t;
    scanf("%d", &t);
    getchar();

    while (t--)
    {
        printf("PLEASE INPUT THE INFIX : ");
        char infix[MAX_STRING];
        char postfix[MAX_STRING];
        scanf("%s", infix);
        getchar();

        convert_infix_to_postfix(infix, postfix);

        printf("INFIX FORM : %s\n", infix);
        printf("POSTFIX FORM : %s\n", postfix);
    }
    return 0;
}