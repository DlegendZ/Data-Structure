#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
    int queue_number;
    int member_type_int;
    char member_type[10];
    char patient_name[101];
    struct patient *next;
    struct patient *prev;
};

struct patient *head = NULL, *tail = NULL, *temp = NULL, *curr = NULL;

struct patient *create_new_patient_node(char patient_name[], int *queue_number, char member_type[])
{
    struct patient *new_patient = (struct patient *)malloc(sizeof(struct patient));
    if (!new_patient)
    {
        printf("FAIL TO CREATE A NEW PATIENT NODE.\n");
        return NULL;
    }
    new_patient->queue_number = (*queue_number)++;
    strcpy(new_patient->member_type, member_type);
    strcpy(new_patient->patient_name, patient_name);
    new_patient->member_type_int = (strcmp(new_patient->member_type, "VIP") == 0) ? 1 : 2;

    new_patient->next = NULL;
    new_patient->prev = NULL;
    return new_patient;
}

void push_data(char patient_name[], int *queue_number, char member_type[])
{
    struct patient *new_patient = create_new_patient_node(patient_name, queue_number, member_type);

    if (!new_patient)
    {
        printf("FAIL TO ADD A NEW PATIENT NODE.\n");
        return;
    }

    if (!head)
    {
        head = tail = new_patient;
    }
    else
    {
        curr = head;
        while (curr && (curr->member_type_int < new_patient->member_type_int || (curr->member_type_int == new_patient->member_type_int && curr->queue_number < new_patient->queue_number)))
        {
            curr = curr->next;
        }

        if (!curr)
        {
            tail->next = new_patient;
            new_patient->prev = tail;
            tail = new_patient;
        }
        else if (!curr->prev)
        {
            head->prev = new_patient;
            new_patient->next = head;
            head = new_patient;
        }
        else
        {
            new_patient->next = curr;
            new_patient->prev = curr->prev;
            curr->prev->next = new_patient;
            curr->prev = new_patient;
        }
    }
}

void pop_data()
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
    printf("%s | PRIORITY : %s HAS BEEN REMOVED FROM THE QUEUE.\n", temp->patient_name, temp->member_type);
    free(temp);
}

void pop_all_data()
{
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}

void display_data()
{
    printf("=== QUEUE ===\n");
    if (head == NULL)
    {
        printf("QUEUE IS EMPTY.\n");
        return;
    }
    curr = head;
    int i = 1;
    while (curr != NULL)
    {
        printf("%d. %s | PRIORITY : %s.\n", i, curr->patient_name, curr->member_type);
        curr = curr->next;
        i++;
    }
}

void display_menu()
{
    printf("=== Infamous Long Queue Problem at BEE Hospital ===\n");
    printf("1. PUSH DATA.\n");
    printf("2. POP DATA.\n");
    printf("3. DISPLAY DATA.\n");
    printf("4. POP ALL DATA AND EXIT.\n");
    printf("YOUR INPUT HERE >> ");
}

int main()
{
    int input;
    char patient_name[101];
    char member_type[10];
    int queue_number = 1;

    do
    {
        system("cls");
        display_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("PLEASE INPUT THE PATIENT'S NAME >> ");
            scanf("%s", patient_name);
            getchar();

            printf("PLEASE INPUT THE PATIENT'S MEMBER TYPE >> ");
            scanf("%s", member_type);
            getchar();

            push_data(patient_name, &queue_number, member_type);
            system("pause");
            break;
        case 2:
            pop_data();
            system("pause");
            break;
        case 3:
            display_data();
            system("pause");
            break;
        case 4:
            pop_all_data();
            break;
        }
    } while (input != 4);
    return 0;
}