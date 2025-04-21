#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

typedef struct Victim
{
    char name[101];
    int age, urgency, status; // 0 = waiting, 1 = served
    struct Victim *next, *prev;
} Victim;

Victim *head = NULL, *tail = NULL;

// Buat node korban baru
Victim *create_victim(const char *name, int age, int urgency)
{
    Victim *v = (Victim *)malloc(sizeof(Victim));
    if (!v)
        return NULL;
    strcpy(v->name, name);
    v->age = age;
    v->urgency = urgency;
    v->status = 0;
    v->next = v->prev = NULL;
    return v;
}

// Tambah korban baru berdasarkan urgensi (diurutkan dari tinggi ke rendah)
void add_victim(const char *name, int age, int urgency)
{
    Victim *v = create_victim(name, age, urgency);
    if (!v)
    {
        printf("FAILED TO ADD VICTIM.\n");
        return;
    }

    if (!head)
    {
        head = tail = v;
        return;
    }

    Victim *cur = head;
    while (cur && cur->urgency >= urgency)
        cur = cur->next;

    if (!cur)
    {
        tail->next = v;
        v->prev = tail;
        tail = v;
    }
    else if (!cur->prev)
    {
        v->next = head;
        head->prev = v;
        head = v;
    }
    else
    {
        v->next = cur;
        v->prev = cur->prev;
        cur->prev->next = v;
        cur->prev = v;
    }
}

// Layani korban berdasarkan urutan prioritas (tertinggi dulu)
void serve_victim()
{
    Victim *cur = head;
    while (cur && cur->status == 1)
        cur = cur->next;

    if (!cur)
    {
        printf("NO VICTIM TO SERVE.\n");
        return;
    }

    cur->status = 1;
    printf("SERVING %s...\n", cur->name);
}

// Undo korban terakhir yang sudah dilayani
void undo_last_serve()
{
    Victim *cur = tail;
    while (cur && cur->status == 0)
        cur = cur->prev;

    if (!cur)
    {
        printf("NO SERVED VICTIM TO UNDO.\n");
        return;
    }

    cur->status = 0;
    printf("UNDOING %s... RETURNED TO %s QUEUE.\n", cur->name, cur->urgency >= 4 ? "PRIORITY" : "NORMAL");
}

// Tampilkan semua data korban
void show_all()
{
    printf("ALL VICTIMS:\n");
    Victim *cur = head;
    while (cur)
    {
        printf("[%s, %d, URGENCY: %d, STATUS: %s]\n", cur->name, cur->age, cur->urgency,
               cur->status ? "SERVED" : "WAITING");
        cur = cur->next;
    }
    printf("[NULL]\n");
}

// Free memory
void clear_all()
{
    Victim *cur;
    while (head)
    {
        cur = head;
        head = head->next;
        free(cur);
    }
    tail = NULL;
}

// UI Menu
void menu()
{
    puts("=== NATIONAL DISASTER MANAGEMENT ===");
    puts("1. ADD VICTIM");
    puts("2. SERVE VICTIM");
    puts("3. UNDO LAST SERVE");
    puts("4. SHOW ALL DATA");
    puts("5. EXIT");
    printf("YOUR INPUT >> ");
}

int main()
{
    int choice, age, urgency, count = 0;
    char name[101];

    do
    {
        system("cls");
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            if (count < MAX)
            {
                printf("NAME: ");
                scanf("%[^\n]", name);
                getchar();
                printf("AGE: ");
                scanf("%d", &age);
                getchar();
                printf("URGENCY (1-5): ");
                scanf("%d", &urgency);
                getchar();
                add_victim(name, age, urgency);
                count++;
            }
            else
            {
                puts("QUEUE FULL.");
            }
            system("pause");
            break;
        case 2:
            serve_victim();
            system("pause");
            break;
        case 3:
            undo_last_serve();
            system("pause");
            break;
        case 4:
            show_all();
            system("pause");
            break;
        case 5:
            clear_all();
            break;
        }
    } while (choice != 5);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX 500

// typedef struct victim
// {
//     char name[101];
//     int age, prior_level, status;
//     struct victim *next, *prev;
// } victim;

// victim *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

// victim *create_new_victim_node(const char *name, int age, int prior_level)
// {
//     victim *v = (victim *)malloc(sizeof(victim));

//     if (!v)
//     {
//         printf("FAIL TO CREATE A NEW VICTIM NODE.\n");
//         return NULL;
//     }

//     strcpy(v->name, name);
//     v->age = age;
//     v->prior_level = prior_level;
//     v->status = 0;
//     v->next = v->prev = NULL;
//     return v;
// }

// void add_victim(const char *name, int age, int prior_level)
// {
//     victim *v = create_new_victim_node(name, age, prior_level);

//     if (!v)
//     {
//         printf("FAIL TO ADD A NEW VICTIM.\n");
//         return;
//     }

//     if (!head)
//     {
//         head = tail = v;
//     }
//     else
//     {
//         if (head->prior_level < v->prior_level)
//         {
//             v->next = head;
//             head->prev = v;
//             head = v;
//         }
//         else if (tail->prior_level >= v->prior_level)
//         {
//             tail->next = v;
//             v->prev = tail;
//             tail = v;
//         }
//         else
//         {
//             curr = head;
//             while (curr)
//             {
//                 if (curr->prior_level < v->prior_level)
//                 {
//                     v->next = curr;
//                     v->prev = curr->prev;
//                     curr->prev->next = v;
//                     curr->prev = v;
//                     break;
//                 }
//                 curr = curr->next;
//             }
//         }
//     }
// }

// void serve_victim()
// {
//     curr = head;
//     while (curr)
//     {
//         if (curr->status == 0)
//         {
//             printf("SERVING %s...\n", curr->name);
//             curr->status = 1;
//             return;
//         }
//         curr = curr->next;
//     }

//     printf("NO VICTIM TO SERVE.\n");
// }

// void undo_last_serve()
// {
//     curr = tail;
//     while (curr)
//     {
//         if (curr->status == 1)
//         {
//             if (curr->prior_level >= 4)
//             {
//                 printf("UNDOING %s... RETURNED TO PRIORITY QUEUE.\n", curr->name);
//             }
//             else if (curr->prior_level < 4)
//             {
//                 printf("UNDOING %s... RETURNED TO NORMAL QUEUE.\n", curr->name);
//             }
//             curr->status = 0;
//             return;
//         }
//         curr = curr->prev;
//     }
//     printf("UNDO IS NOT AVAILABLE.\n");
// }

// void show_all_data()
// {
//     printf("ALL VICTIM DATA:\n");
//     curr = head;
//     while (curr)
//     {
//         if (curr->status == 1)
//         {
//             printf("[%s, %d, URGENCY: %d, STATUS: SERVED]\n", curr->name, curr->age, curr->prior_level);
//         }
//         else
//         {
//             printf("[%s, %d, URGENCY: %d, STATUS: WAITING.]\n", curr->name, curr->age, curr->prior_level);
//         }
//         curr = curr->next;
//     }
//     printf("[NULL]\n");
// }

// void clear_memories()
// {
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp);
//     }
//     tail = NULL;
// }

// void menu()
// {
//     printf("=== NATIONAL DISASTER MANAGEMENT ===\n");
//     printf("1. ADD VICTIM.\n");
//     printf("2. SERVE VICTIM.\n");
//     printf("3. UNDO LAST SERVE.\n");
//     printf("4. SHOW ALL DATA.\n");
//     printf("5. EXIT.\n");
//     printf("YOUR INPUT HERE >> ");
// }

// int main()
// {
//     char name[101];
//     int input, age, prior_level;
//     int victim_count = 0;

//     do
//     {
//         system("cls");
//         menu();
//         scanf("%d", &input);
//         getchar();

//         switch (input)
//         {
//         case 1:
//             if (victim_count < MAX)
//             {
//                 printf("PLEASE INPUT THE VICTIM'S NAME : ");
//                 scanf("%[^\n]", name);
//                 getchar();

//                 printf("PLEASE INPUT THE VICTIM'S AGE : ");
//                 scanf("%d", &age);
//                 getchar();

//                 printf("PLEASE INPUT THE VICTIM'S URGENCY LEVEL : ");
//                 scanf("%d", &prior_level);
//                 getchar();

//                 add_victim(name, age, prior_level);
//                 victim_count++;
//             }
//             else
//             {
//                 printf("QUEUE IS FULL. CAN'T ADD MORE VICTIM.\n");
//             }
//             system("pause");
//             break;
//         case 2:
//             serve_victim();
//             system("pause");
//             break;
//         case 3:
//             undo_last_serve();
//             system("pause");
//             break;
//         case 4:
//             show_all_data();
//             system("pause");
//             break;
//         case 5:
//             clear_memories();
//             break;
//         }
//     } while (input != 5);

//     return 0;
// }