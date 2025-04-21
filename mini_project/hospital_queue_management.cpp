#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient
{
    char name[101];
    int age, priority, status; // status: 0 = waiting, 1 = processed
    struct patient *next, *prev;
} Patient;

Patient *head = NULL, *tail = NULL;

// Fungsi untuk membuat pasien baru
Patient *create_patient(const char *name, int age, int priority)
{
    Patient *p = (Patient *)malloc(sizeof(Patient));
    if (!p)
        return NULL;
    strcpy(p->name, name);
    p->age = age;
    p->priority = priority;
    p->status = 0;
    p->next = p->prev = NULL;
    return p;
}

// Fungsi untuk menambahkan pasien ke dalam list (sorting by priority)
void register_patient(const char *name, int age, int priority)
{
    Patient *p = create_patient(name, age, priority);
    if (!p)
    {
        printf("FAIL TO ADD A NEW PATIENT.\n");
        return;
    }

    // Jika linked list kosong
    if (!head)
    {
        head = tail = p;
        return;
    }

    Patient *curr = head;

    // Cari posisi yang tepat berdasarkan priority (sorting)
    while (curr && curr->priority >= priority)
        curr = curr->next;

    if (!curr)
    { // Masukkan di akhir
        tail->next = p;
        p->prev = tail;
        tail = p;
    }
    else if (!curr->prev)
    { // Masukkan di awal
        p->next = head;
        head->prev = p;
        head = p;
    }
    else
    { // Masukkan di tengah
        p->next = curr;
        p->prev = curr->prev;
        curr->prev->next = p;
        curr->prev = p;
    }
}

// Fungsi untuk memproses pasien dengan prioritas tertinggi yang belum diproses
void process_patient()
{
    Patient *curr = head;

    while (curr && curr->status == 1)
        curr = curr->next; // Cari pasien belum diproses

    if (!curr)
    {
        printf("NO PATIENT TO SERVE.\n");
        return;
    }

    curr->status = 1; // Tandai sebagai sudah diproses
    printf("Processing %s...\n", curr->name);
}

// Fungsi untuk undo pasien terakhir yang diproses
void undo_last_process()
{
    Patient *curr = tail;

    while (curr && curr->status == 0)
        curr = curr->prev; // Cari pasien yang diproses terakhir

    if (!curr)
    {
        printf("NO LAST PROCESS TO UNDO.\n");
        return;
    }

    curr->status = 0; // Tandai kembali ke antrian
    printf("UNDO LAST PROCESS (%s)...\n", curr->name);
}

// Fungsi untuk menampilkan antrian pasien
void show_queues()
{
    printf("PRIORITY QUEUE: [");
    for (Patient *p = head; p; p = p->next)
        if (p->priority >= 3 && p->status == 0)
            printf("(%s, %d, %d), ", p->name, p->age, p->priority);
    printf("(NULL)]\n");

    printf("QUEUE: [");
    for (Patient *p = head; p; p = p->next)
        if (p->priority < 3 && p->status == 0)
            printf("(%s, %d, %d), ", p->name, p->age, p->priority);
    printf("(NULL)]\n");
}

// Fungsi untuk menampilkan pasien yang telah diproses
void show_processed_patient()
{
    printf("PROCESSED PATIENTS: [");
    for (Patient *p = head; p; p = p->next)
        if (p->status == 1)
            printf("(%s, %d, %d), ", p->name, p->age, p->priority);
    printf("(NULL)]\n");
}

// Fungsi untuk membersihkan memori sebelum program berakhir
void clear_memories()
{
    while (head)
    {
        Patient *temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

// Fungsi untuk menampilkan menu
void menu()
{
    printf("=== HOSPITAL QUEUE MANAGEMENT ===\n");
    printf("1. REGISTER PATIENT\n");
    printf("2. PROCESS PATIENT\n");
    printf("3. UNDO LAST PROCESS\n");
    printf("4. SHOW PROCESSED PATIENTS\n");
    printf("5. SHOW QUEUES\n");
    printf("6. EXIT\n");
    printf("YOUR INPUT HERE >> ");
}

// Main program
int main()
{
    int input, age, priority;
    char name[101];

    do
    {
        system("cls");
        menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PATIENT NAME: ");
            scanf("%s", name);
            getchar();

            printf("PATIENT AGE: ");
            scanf("%d", &age);
            getchar();

            printf("URGENCY (1-5): ");
            scanf("%d", &priority);
            getchar();

            register_patient(name, age, priority);
            system("pause");
            break;
        case 2:
            process_patient();
            system("pause");
            break;
        case 3:
            undo_last_process();
            system("pause");
            break;
        case 4:
            show_processed_patient();
            system("pause");
            break;
        case 5:
            show_queues();
            system("pause");
            break;
        case 6:
            clear_memories();
            break;
        }
    } while (input != 6);

    return 0;
}
