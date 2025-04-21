#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct text
{
    char word[101];
    struct text *next;
    struct text *prev;
};

struct text *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct text *create_new_text_node(char word[])
{
    struct text *new_text = (struct text *)malloc(sizeof(struct text));

    if (!new_text)
    {
        printf("\033[31mFAIL TO CREATE A NEW TEXT NODE.\033[0m\n");
        return NULL;
    }

    strcpy(new_text->word, word);
    new_text->next = NULL;
    new_text->prev = NULL;
    return new_text;
}

void type_word(char word[])
{
    struct text *new_text = create_new_text_node(word);

    if (!new_text)
    {
        printf("\033[31mFAIL TO ADD NEW TEXT.\033[0m\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_text;
    }
    else
    {
        new_text->next = head;
        head->prev = new_text;
        head = new_text;
    }
    printf("\033[32mTHE WORD '%s' HAS BEEN ADDED.\033[0m\n", new_text->word);
    printf("\033[32mSUCCESSFULLY EXECUTING THE PROGRAM.\033[0m\n");
}

void undo()
{
    if (head == NULL)
    {
        printf("\033[31mSTACK IS EMPTY.\033[0m\n");
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

    printf("\033[32mUNDO SUCCEED! THE WORD '%s' HAS BEEN REMOVED.\033[0m\n", temp->word);
    free(temp);
    printf("\033[32mSUCCESSFULLY EXECUTING THE PROGRAM.\033[0m\n");
}

void display_text()
{
    if (head == NULL)
    {
        printf("\033[31mSTACK IS EMPTY.\033[0m\n");
        return;
    }

    printf("\033[34mTEXT CONTENT : \033[0m");

    curr = head;
    while (curr != NULL)
    {
        printf("%s -> ", curr->word);
        curr = curr->next;
    }
    printf("NULL\n");
    printf("\033[32mSUCCESSFULLY EXECUTING THE PROGRAM.\033[0m\n");
}

void print_menu()
{
    printf("=== \033[34mSIMPLE TEXT EDITOR\033[0m ===\n");
    printf("1. TYPE WORD.\n");
    printf("2. REMOVE LAST WORD.\n");
    printf("3. PRINT TEXT.\n");
    printf("4. EXIT.\n");
    printf("YOUR INPUR HERE >> ");
}

void clear_data()
{
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
    printf("\033[32mSUCCESSFULLY EXECUTING THE PROGRAM.\033[0m\n");
}

int main()
{
    int input;
    char word[101];
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE WORD : ");
            scanf("%s", word);
            getchar();

            type_word(word);
            system("pause");
            break;
        case 2:
            undo();
            system("pause");
            break;
        case 3:
            display_text();
            system("pause");
            break;
        case 4:
            printf("\033[32mCLEARING ALL THE MEMORIES..\033[0m\n");
            clear_data();
            printf("\033[34mEXITTING..\033[0m\n");
            break;
        }
    } while (input != 4);

    printf("\033[32mSUCCESSFULLY EXECUTING THE PROGRAM.\033[0m\n");
    return 0;
}