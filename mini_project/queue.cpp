#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int playlist_quota = 0;

struct song
{
    char song_name[101];

    struct song *next;
    struct song *prev;
};

struct song *head = NULL, *tail = NULL, *temp = NULL, *curr = NULL;

struct song *create_new_song_node(char song_name[])
{
    struct song *new_song = (struct song *)malloc(sizeof(struct song));
    if (!new_song)
    {
        printf("FAIL TO CREATE A NEW SONG NODE.\n");
        return NULL;
    }
    strcpy(new_song->song_name, song_name);
    new_song->next = NULL;
    new_song->prev = NULL;
    return new_song;
}

// push tail and pop head
void add_song(char song_name[])
{
    struct song *new_song = create_new_song_node(song_name);

    if (!new_song)
    {
        printf("FAIL TO ADD A NEW SONG.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_song;
    }
    else
    {
        tail->next = new_song;
        new_song->prev = tail;
        tail = new_song;
    }
    playlist_quota++;
}

void play_song()
{
    if (head == NULL)
    {
        printf("SONG'S LIST IS EMPTY.\n");
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

    free(temp);
    playlist_quota--;
}

void view_queue()
{
    printf("=== SONGS QUEUE ===\n");

    if (head == NULL)
    {
        printf("NO SONG IN THE QUEUE.\n");
        return;
    }

    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s.\n", i, curr->song_name);
        i++;
        curr = curr->next;
    }
}

void display_menu()
{
    printf("=== SONG PLAYLIST SYSTEM ===\n");
    printf("1. ADD SONG TO THE PLAYLIST.\n");
    printf("2. PLAY SONG FROM THE PLAYLIST.\n");
    printf("3. VIEW PLAYLIST.\n");
    printf("4. EXIT.\n");
    printf("PLAYLIST QUOTA USED : %d/10.\n", playlist_quota);
    printf("YOUR INPUT HERE >> ");
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
    playlist_quota = 0;
}

int main()
{
    int input;
    char song_name[101];

    do
    {
        system("cls");
        display_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            if (playlist_quota < 10)
            {
                printf("PLEASE INPUT THE SONG'S NAME : ");
                scanf("%s", song_name);
                getchar();

                add_song(song_name);
            }
            else
            {
                printf("SONG'S PLAYLIST HAS REACHED 10 QUOTAS. CAN'T ADD SONG TO THE PLAYLIST.\n");
            }

            system("pause");
            break;
        case 2:
            play_song();
            system("pause");
            break;
        case 3:
            view_queue();
            system("pause");
            break;
        case 4:
            clear_memories();
            break;
        }
    } while (input != 4);
    return 0;
}