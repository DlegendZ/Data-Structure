#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
    int id;
    char patient_name[101];

    struct patient *next;
};

struct patient *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct patient *create_new_patient_node(char patient_name[], int id)
{
    struct patient *new_patient = (struct patient *)malloc(sizeof(struct patient));

    if (!new_patient)
    {
        printf("\033[31mFail to create new patien node.\033[0m\n");
        return NULL;
    }

    new_patient->id = id;
    strcpy(new_patient->patient_name, patient_name);
    new_patient->next = NULL;

    return new_patient;
}

void add_patient(char patient_name[], int id)
{
    struct patient *new_patient = create_new_patient_node(patient_name, id);

    if (!new_patient)
    {
        printf("\033[31mFail to add new patien data.\033[0m\n");
        return;
    }

    if (head == NULL)
    {
        head = tail = new_patient;
    }
    else
    {
        tail->next = new_patient;
        tail = new_patient;
    }
    printf("Patient (name : %s) with (ID : %d) has been successfully added to the queue.\n", new_patient->patient_name, new_patient->id);
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
}

void service_patient()
{
    if (head == NULL)
    {
        printf("Queue is empty. Please add patient!\n");
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
    }
    printf("patient (name : %s) with (ID : %d) has been served and removed from the queue.\n", temp->patient_name, temp->id);
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
    free(temp);
}

void display_all_patients()
{
    printf("Queue Status : \n");

    int i = 1;
    curr = head;
    while (curr != NULL)
    {
        printf("%d. %s | %d\n", i, curr->patient_name, curr->id);
        curr = curr->next;
        i++;
    }

    printf("%d. NULL\n", i);
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
}

void search_patient_data(int id)
{
    curr = head;
    while (curr != NULL)
    {
        if (curr->id == id)
        {
            printf("Patient found : ID: %d | Name: %s.\n", curr->id, curr->patient_name);
            break;
        }
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Patient not found. Please input the correct ID.\n");
        return;
    }
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
}

void remove_patient_data(int id)
{
    if (head == NULL)
    {
        printf("Queue is empty. No patient found.\n");
        return;
    }
    else if (head == tail && head->id == id)
    {
        temp = head;
        head = tail = NULL;
    }
    else if (head->id == id)
    {
        temp = head;
        head = head->next;
    }
    else if (tail->id == id)
    {
        curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        temp = tail;
        tail = curr;
        tail->next = NULL;
    }
    else
    {
        curr = head;
        while (curr->next != NULL)
        {
            if (curr->next->id == id)
            {
                temp = curr->next;
                curr->next = temp->next;
                break;
            }
            curr = curr->next;
        }

        if (curr->next == NULL)
        {
            printf("Patient not found. Please input the correct ID.\n");
            return;
        }
    }
    printf("patient (name : %s) with (ID: %d) has been removed from the queue.\n", temp->patient_name, temp->id);
    free(temp);
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
}

void print_menu()
{
    printf("=== Hospital Queue System ===\n");
    printf("1. Add patient to the queue.\n");
    printf("2. Service the patient.\n");
    printf("3. Display all the patients.\n");
    printf("4. Search patient based on the ID.\n");
    printf("5. Remove patient from the queue based on the ID.\n");
    printf("6. Exit.\n");
    printf("Your input here >> ");
}

void clear_all_data()
{
    while (head != NULL)
    {
        curr = head;
        head = head->next;
        free(curr);
    }
    tail = NULL;
    printf("\033[32mSuccessfully executing the program.\033[0m\n");
}

int main()
{
    int input;
    char patient_name[101];
    int id;
    do
    {
        system("cls");
        print_menu();
        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Please input the patient's name >> ");
            scanf("%[^\n]", patient_name);
            getchar();

            printf("Please input the patient's ID >> ");
            scanf("%d", &id);
            getchar();

            add_patient(patient_name, id);
            system("pause");
            break;
        case 2:
            service_patient();
            system("pause");
            break;
        case 3:
            display_all_patients();
            system("pause");
            break;
        case 4:
            printf("Please input the patient's ID >> ");
            scanf("%d", &id);
            getchar();
            search_patient_data(id);
            system("pause");
            break;
        case 5:
            printf("Please input the patient's ID >> ");
            scanf("%d", &id);
            getchar();
            remove_patient_data(id);
            system("pause");
            break;
        case 6:
            printf("Clearing all the memories..\n");
            clear_all_data();
            printf("Exitting..\n");
            break;
        }
    } while (input != 6);

    printf("\033[32mSuccessfully executing the program. Enjoy your day sir!\033[0m\n");
    return 0;
}