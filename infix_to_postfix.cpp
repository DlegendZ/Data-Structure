#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Untuk isdigit() & isalnum()

#define MAX_STRING 101

struct list
{
    char op;
    struct list *next;
    struct list *prev;
};

struct list *head = NULL, *tail = NULL;

// Fungsi membuat node baru
struct list *create_new_node(char value)
{
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    new_node->op = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Fungsi push ke stack (dari tail agar pop() bekerja dengan benar)
void push(char value)
{
    struct list *new_node = create_new_node(value);

    if (tail == NULL)
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

// Fungsi melihat operator di atas stack
char top()
{
    if (tail == NULL)
        return '\0';
    return tail->op;
}

// Fungsi pop dari stack
char pop()
{
    char temp = '\0';
    struct list *curr;

    if (tail != NULL)
    {
        temp = tail->op;
        curr = tail;

        if (head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;
        }

        free(curr);
    }

    return temp;
}

// Fungsi prioritas operator
int precedence(char op)
{
    if (op == '^')
        return 3; // Pangkat memiliki prioritas tertinggi
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Fungsi mengubah Infix ke Postfix
void convert_infix_to_postfix(char *infix, char *postfix)
{
    int ctr = 0;

    for (int i = 0; i < strlen(infix); i++)
    {
        if (isalnum(infix[i])) // Perbaikan: Bisa angka & variabel (A-Z, 0-9)
        {
            postfix[ctr++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top() != '(' && tail != NULL)
            {
                postfix[ctr++] = pop();
            }
            pop(); // Hapus '(' dari stack
        }
        else // Operator: +, -, *, /, ^
        {
            while (tail != NULL && precedence(top()) >= precedence(infix[i]))
            {
                postfix[ctr++] = pop();
            }
            push(infix[i]);
        }
    }

    while (tail != NULL)
    {
        postfix[ctr++] = pop();
    }

    postfix[ctr] = '\0'; // Perbaikan: Gunakan '\0' untuk string valid
}

// Fungsi utama
int main()
{
    char infix[MAX_STRING];
    char postfix[MAX_STRING];

    strcpy(infix, "4+6*(5-2)/3"); // Input ekspresi

    convert_infix_to_postfix(infix, postfix);

    printf("Infix : %s\n", infix);
    printf("Postfix : %s\n", postfix);
    return 0;
}
