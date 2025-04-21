#include <stdio.h>
#include <stdlib.h>

struct character
{
    char character;

    struct character *next;
    struct character *prev;
};

struct character *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct character *create_new_character_node(char character)
{
    struct character *new_character = (struct character *)malloc(sizeof(struct character));

    if (!new_character)
    {
        printf("FAIL TO CREATE A NEW CHARACTER NODE.\n");
        return NULL;
    }

    new_character->character = character;
    new_character->next = NULL;
    new_character->prev = NULL;
    return new_character;
}

void append(char character)
{
    struct character *new_character = create_new_character_node(character);

    if (!new_character)
    {
        printf("FAIL TO ADD A NEW CHARACTER NODE.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_character;
    }
    else
    {
        tail->next = new_character;
        new_character->prev = tail;
        tail = new_character;
    }
}

void print_all()
{
    curr = head;
    while (curr != NULL)
    {
        printf("%c", curr->character);
        curr = curr->next;
    }
    printf("\n");
}

void duplicate_word()
{
    curr = head;
    while (curr != NULL)
    {
        struct character *new_character = create_new_character_node(curr->character);

        if (!new_character)
        {
            printf("FAIL TO ADD A NEW CHARACTER NODE.\n");
            return;
        }

        if (curr == tail)
        {
            tail->next = new_character;
            new_character->prev = tail;
            tail = new_character;
            break;
        }
        else
        {
            new_character->prev = curr;
            new_character->next = curr->next;
            curr->next->prev = new_character;
            curr->next = new_character;
            curr = curr->next->next;
        }
    }
}

void delete_first_half(int length)
{
    int iteration = length;
    for (int i = 0; i < iteration; i++)
    {
        temp = head;
        head = head->next;
        head->prev = NULL;
        free(temp);
    }
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

int main()
{
    int length;
    scanf("%d", &length);
    getchar();

    char word[length + 1];
    scanf("%s", word);
    getchar();

    for (int i = 0; i < length; i++)
    {
        append(word[i]);
    }

    curr = head;
    while (curr != NULL)
    {
        if (curr->character != head->character)
        {
            print_all();
            duplicate_word();
            print_all();
            delete_first_half(length);
            curr = head;
        }
        curr = curr->next;
    }

    print_all();
    clear_memories();
    return 0;
}