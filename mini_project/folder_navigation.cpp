#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dir
{
    char dir_name[101];
    struct dir *next;
    struct dir *prev;
};

struct dir *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct dir *create_new_dir_node(char dir_name[])
{
    struct dir *new_dir = (struct dir *)malloc(sizeof(struct dir));

    if (!new_dir)
    {
        printf("ERROR! FAIL TO CREATE NEW DIR NODE.\n");
        return NULL;
    }

    strcpy(new_dir->dir_name, dir_name);
    new_dir->next = NULL;
    new_dir->prev = NULL;
    return new_dir;
}

void nav_dir(char dir_name[])
{ // add_dir
    struct dir *new_dir = create_new_dir_node(dir_name);

    if (!new_dir)
    {
        printf("ERROR! FAIL TO ADD NEW DIR.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_dir;
    }
    else
    {
        tail->next = new_dir;
        new_dir->prev = tail;
        tail = new_dir;
    }
}

void nav_back()
{
    if (head == NULL)
    {
        printf("ERROR! STACK IS EMPTY.\n");
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

    free(temp);
}

void print_dir()
{
    curr = head;
    while (curr != NULL)
    {
        printf("/%s", curr->dir_name);
        curr = curr->next;
    }
    printf("\n");
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
    char input[101];
    char dir[101];

    while (1)
    {
        scanf("%[^\n]", input);
        getchar();

        if (strcmp(input, "pwd") == 0)
        {
            print_dir();
        }
        else if (strcmp(input, "cd ..") == 0)
        {
            nav_back();
        }
        else if (strcmp(input, "cd exit") == 0)
        {
            clear_memories();
            break;
        }
        else
        {
            if (strncmp(input, "cd ", 3) == 0)
            {
                if (strlen(input) > 3)
                {
                    strcpy(dir, input + 3);
                    nav_dir(dir);
                }
                else
                {
                    printf("INPUT IS EMPTY.\n");
                }
            }
            else
            {
                printf("WRONG INPUT.\n");
            }
        }
    }
    return 0;
}