#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Untuk isalnum()

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

// Fungsi push ke stack
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
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Fungsi membalik string (untuk prefix)
void reverseString(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Fungsi mengubah Infix ke Prefix
void convert_infix_to_prefix(char *infix, char *prefix)
{
    int ctr = 0;
    char op;

    // Balik ekspresi infix
    reverseString(infix);

    for (int i = 0; i < strlen(infix); i++)
    {
        if (isalnum(infix[i])) // Operand langsung ke output
        {
            prefix[ctr++] = infix[i];
        }
        else if (infix[i] == ')') // Jika ')', push ke stack
        {
            push(infix[i]);
        }
        else if (infix[i] == '(') // Jika '(', pop semua operator sampai ')'
        {
            while (top() != ')' && tail != NULL)
            {
                prefix[ctr++] = pop();
            }
            pop(); // Hapus ')'
        }
        else // Operator: +, -, *, /, ^
        {
            while (tail != NULL && precedence(top()) > precedence(infix[i]))
            {
                prefix[ctr++] = pop();
            }
            push(infix[i]);
        }
    }

    // Pop semua operator yang tersisa di stack
    while (tail != NULL)
    {
        prefix[ctr++] = pop();
    }

    prefix[ctr] = '\0'; // Tambahkan akhir string

    // Balik kembali hasilnya untuk mendapatkan Prefix yang benar
    reverseString(prefix);
}

// Fungsi utama
int main()
{
    char infix[MAX_STRING];
    char prefix[MAX_STRING];

    strcpy(infix, "4+6*(5-2)/3"); // Input ekspresi
    printf("Infix : %s\n", infix);

    convert_infix_to_prefix(infix, prefix);
    printf("Prefix : %s\n", prefix);
    return 0;
}
