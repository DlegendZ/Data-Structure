#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_money = 0;

struct transaction
{
    char type[50];
    int value;
    struct transaction *next;
    struct transaction *prev;
};

struct transaction *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct transaction *create_new_transaction_node(char type[], int value)
{
    struct transaction *new_transaction = (struct transaction *)malloc(sizeof(struct transaction));
    if (!new_transaction)
    {
        printf("FAIL TO CREATE NEW TRANSACTION NODE.\n");
        return NULL;
    }
    new_transaction->value = value;
    strcpy(new_transaction->type, type);
    new_transaction->next = NULL;
    new_transaction->prev = NULL;
    return new_transaction;
}

void deposit(char type[], int value)
{
    struct transaction *new_transaction = create_new_transaction_node(type, value);
    if (!new_transaction)
    {
        printf("FAIL TO ADD DEPOSIT.\n");
        return;
    }
    if (head == NULL)
    {
        head = tail = new_transaction;
    }
    else
    {
        tail->next = new_transaction;
        new_transaction->prev = tail;
        tail = new_transaction;
    }
    total_money += new_transaction->value;
    printf("SUCCESS! DEPOSITED: %d\n", new_transaction->value);
}

void withdraw(char type[], int value)
{
    if (total_money >= value)
    {
        struct transaction *new_transaction = create_new_transaction_node(type, value);
        if (!new_transaction)
        {
            printf("FAIL TO WITHDRAW.\n");
            return;
        }
        if (head == NULL)
        {
            head = tail = new_transaction;
        }
        else
        {
            tail->next = new_transaction;
            new_transaction->prev = tail;
            tail = new_transaction;
        }
        total_money -= new_transaction->value;
        printf("SUCCESS! WITHDRAWN: %d\n", value);
    }
    else
    {
        printf("MONEY DOESN'T ENOUGH. FAIL TO WITHDRAW.\n");
        return;
    }
}

void undo_transaction()
{
    if (head == NULL)
    {
        printf("FAIL TO UNDO TRANSACTION. NO TRANSACTION RECORDED.\n");
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

    if (strcmp(temp->type, "DEPOSIT") == 0)
    {
        total_money -= temp->value;
    }
    else if (strcmp(temp->type, "WITHDRAW") == 0)
    {
        total_money += temp->value;
    }
    printf("LAST TRANSACTION '%s %d' has been undone.\n", temp->type, temp->value);
    free(temp);
}

void history()
{
    if (head == NULL)
    {
        printf("HISTORY IS EMPTY.\n");
        return;
    }

    printf("TRANSACTION HISTORY:\n");

    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s %d\n", i, curr->type, curr->value);
        curr = curr->next;
        i++;
    }
}

void balance()
{
    printf("CURRENT BALANCE: %d\n", total_money);
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
    total_money = 0;
}

void menu()
{
    printf("==== ATM TRANSACTION SYSTEM ===\n");
    printf("1. DEPOSIT.\n");
    printf("2. WITHDRAW.\n");
    printf("3. UNDO.\n");
    printf("4. HISTORY.\n");
    printf("5. BALANCE.\n");
    printf("6. EXIT.\n");
    printf("YOUR INPUR HERE >> ");
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
            printf("PLEASE INPUT THE VALUE : ");
            scanf("%d", &value);
            getchar();

            deposit("DEPOSIT", value);
            system("pause");
            break;
        case 2:
            printf("PLEASE INPUT THE VALUE : ");
            scanf("%d", &value);
            getchar();

            withdraw("WITHDRAW", value);
            system("pause");
            break;
        case 3:
            undo_transaction();
            system("pause");
            break;
        case 4:
            history();
            system("pause");
            break;
        case 5:
            balance();
            system("pause");
            break;
        case 6:
            printf("CLEARING ALL THE MEMORIES USED..\n");
            clear_memories();
            printf("EXITTING..\n");
            break;
        default:
            printf("INVALID INPUT.\n");
            system("pause");
            break;
        }
    } while (input != 6);
    printf("SUCCESSFULLY EXITTING THE PROGRAM.\nENJOY YOUR DAY SIR.\n");

    return 0;
}