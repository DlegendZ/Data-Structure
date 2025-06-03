#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26

typedef struct node
{
    struct node *children[ALPHABET_SIZE];
    int is_end_word;
    char slang_word[100];
    char description[1000];
} node;

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        new_node->children[i] = NULL;
    }
    new_node->is_end_word = 0;
    strcpy(new_node->slang_word, "");
    strcpy(new_node->description, "");
    return new_node;
}

void insert(node *root, const char *word, const char *desc)
{
    node *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (!current->children[index])
        {
            current->children[index] = create_node();
        }

        current = current->children[index];
    }
    current->is_end_word = 1;
    strcpy(current->slang_word, word);
    if (strcmp(current->description, "") == 0)
    {
        printf("\nSuccessfully released new slang word.\n");
    }
    else
    {
        printf("\nSuccessfully updated a slang word.\n");
    }
    strcpy(current->description, desc);
}

void search(node *root, const char *word)
{
    node *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (!current->children[index])
        {
            printf("\nThere is no word \"%s\" in the dictionary.\n", word);
            return;
        }

        current = current->children[index];
    }
    if (current->is_end_word)
    {
        printf("\nSlang word : %s\n", current->slang_word);
        printf("Description : %s\n\n", current->description);
    }
    else
    {
        printf("\nThere is no word \"%s\" in the dictionary.\n", word);
        return;
    }
}

void print_data(node *current, int *num)
{
    if (current->is_end_word)
    {
        printf("%d. %s\n", *num, current->slang_word);
        (*num)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (current->children[i])
        {
            print_data(current->children[i], num);
        }
    }
}

void show_based_prefix(node *root, const char *word)
{
    node *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if (!current->children[index])
        {
            printf("\nThere is no prefix \"%s\" in the dictionary.\n", word);
            return;
        }

        current = current->children[index];
    }
    int num = 1;
    printf("\nWords starts with \"%s\":\n", word);
    print_data(current, &num);
    printf("\n");
}

void show_all(node *root)
{
    node *current = root;
    int is_empty = 1;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (current->children[i])
        {
            is_empty = 0;
            break;
        }
    }
    if (!is_empty)
    {
        printf("List of all slang words in the dictionary:\n");
        int num = 1;
        print_data(current, &num);
        printf("\n");
    }
    else
    {
        printf("There is no slang word yet in the dictionary.\n");
    }
}

void exit_trie(node *root)
{
    node *current = root;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (current->children[i])
        {
            exit_trie(current->children[i]);
        }
    }
    free(current);
}

void print_menu()
{
    printf("====BOOGLE APPLICATION MENU====\n");
    printf("1. RELEASE A NEW SLANG WORD.\n");
    printf("2. SEARCH A SLANG WORD.\n");
    printf("3. VIEW ALL SLANG WORDS STARTING WITH A CERTAIN PREFIX WORD.\n");
    printf("4. VIEW ALL SLANG WORDS.\n");
    printf("5. EXIT.\n");
    printf("YOUR INPUT HERE >> ");
}

int first_verif(const char *word)
{
    if (strlen(word) <= 1)
    {
        return 0;
    }

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == ' ')
        {
            return 0;
        }
    }

    return 1;
}

int second_verif(const char *word)
{
    int space = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == ' ')
        {
            space++;
        }
    }

    return space >= 2;
}

int main()
{
    node *root = create_node();
    char word[100];
    char word_desc[1000];
    int menu_option;
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &menu_option);
        getchar();

        switch (menu_option)
        {
        case 1:
            do
            {
                printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", word);
                getchar();
            } while (!first_verif(word));
            do
            {
                printf("Input a new slang word description [Must be more than 2 words]: ");
                scanf("%[^\n]", word_desc);
                getchar();
            } while (!second_verif(word_desc));
            insert(root, word, word_desc);
            system("pause");
            break;
        case 2:
            do
            {
                printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
                scanf("%[^\n]", word);
                getchar();
            } while (!first_verif(word));
            search(root, word);
            system("pause");
            break;
        case 3:
            printf("Input a prefix to be searched: ");
            scanf("%s", word);
            getchar();
            show_based_prefix(root, word);
            system("pause");
            break;
        case 4:
            show_all(root);
            system("pause");
            break;
        case 5:
            exit_trie(root);
            printf("Thank you... Have a nice day :)");
            break;
        }
    } while (menu_option != 5);

    return 0;
}