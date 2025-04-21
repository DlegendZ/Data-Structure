#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
    char patient_name[101];
    int prior_num;
    struct patient *next;
    struct patient *prev;
};

struct patient *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct patient *create_new_patient_node(char patient_name[], int prior_num)
{
    struct patient *new_patient = (struct patient *)malloc(sizeof(struct patient));
    if (!new_patient)
    {
        printf("FAIL TO CREATE NEW PATIENT NODE.\n");
        return NULL;
    }
    strcpy(new_patient->patient_name, patient_name);
    new_patient->prior_num = prior_num;
    new_patient->next = NULL;
    new_patient->prev = NULL;
    return new_patient;
}

void add_patient(char patient_name[], int prior_num)
{
    struct patient *new_patient = create_new_patient_node(patient_name, prior_num);

    if (!new_patient)
    {
        printf("FAIL TO CREATE ADD NEW PATIENT.\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_patient;
    }
    else if (head->prior_num < new_patient->prior_num)
    {
        new_patient->next = head;
        head->prev = new_patient;
        head = new_patient;
    }
    else if (tail->prior_num >= new_patient->prior_num)
    {
        new_patient->prev = tail;
        tail->next = new_patient;
        tail = new_patient;
    }
    else
    {
        curr = head->next;
        while (curr != NULL)
        {
            if (curr->prior_num < prior_num)
            {
                curr->prev->next = new_patient;
                new_patient->prev = curr->prev;
                curr->prev = new_patient;
                new_patient->next = curr;
                break;
            }
            curr = curr->next;
        }
    }
}

void serve_patient()
{
    if (head == NULL)
    {
        printf("QUEUE IS EMPTY.\n");
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
    printf("CALLING PATIENT: %s (PRIORITY %d).\n", temp->patient_name, temp->prior_num);
    free(temp);
}

void display_queue()
{
    if (head == NULL)
    {
        printf("QUEUE IS EMPTY.\n");
        return;
    }

    printf("CURRENT QUEUE:\n");
    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s (PRIORITY %d).\n", i, curr->patient_name, curr->prior_num);
        curr = curr->next;
        i++;
    }
}

void menu()
{
    printf("=== HOSPITAL EMERGENCY QUEUE ===\n");
    printf("1. ENQUEUE NEW PATIENT.\n");
    printf("2. DEQUEUE/SERVE PATIENT.\n");
    printf("3. DISPLAY PATIENT'S QUEUE.\n");
    printf("4. EXIT PROGRAM.\n");
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
}

int main()
{
    int input;
    char patient_name[101];
    int prior_num;

    do
    {
        system("cls");
        menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT PATIENT'S NAME : ");
            scanf("%s", patient_name);
            getchar();

            printf("PLEASE INPUT PATIENT'S PRIORITY NUMBER : ");
            scanf("%d", &prior_num);
            getchar();

            add_patient(patient_name, prior_num);
            system("pause");
            break;
        case 2:
            serve_patient();
            system("pause");
            break;
        case 3:
            display_queue();
            system("pause");
            break;
        case 4:
            printf("CLEARING MEMORIES..\n");
            clear_memories();
            printf("EXITTING..\n");
            break;
        default:
            printf("INVALID INPUT..\n");
            system("pause");
            break;
        }
    } while (input != 4);
    printf("SUCCESSFULLY EXITTING THE PROGRAM.\nENJOY YOUR DAY, SIR!\n");
    return 0;
}