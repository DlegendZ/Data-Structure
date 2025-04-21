//single linked list
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next; // Perbaikan typo: 'node' menjadi 'Node'
} *head = NULL, *tail = NULL, *curr = NULL, *temp = NULL;

struct Node* create_new_node(int value) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}

// Push head
void push_head(int value) {
    struct Node* new_node = create_new_node(value);

    if (head == NULL) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }
}

// Push mid
void push_mid(int value) {
    struct Node* new_node = create_new_node(value); // Perbaikan typo 'node' menjadi 'Node'

    if (head == NULL) {
        head = tail = new_node;
    } else if (new_node->value < head->value) { // Push head
        new_node->next = head;
        head = new_node;
    } else if (new_node->value >= tail->value) { // Push tail
        tail->next = new_node;
        tail = new_node;
    } else { // Push mid 
        curr = head;

        while (curr->next != NULL) {
            if (curr->next->value > new_node->value) {
                break;
            }
            curr = curr->next;
        }

        new_node->next = curr->next;
        curr->next = new_node;
    }
}

// Push tail
void push_tail(int value) {
    struct Node* new_node = create_new_node(value);

    if (head == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

//pop head
void pop_head() {
    if (head == NULL) {
        printf("Linked list is empty!\n");
        return;
    }

    if (head == tail) {
        temp = head;
        head = tail = NULL;
    } else {
        temp = head;
        head = head->next;
    }
    free(temp);
}

//pop tail
void pop_tail() {
    if (head == NULL) {
        printf("Linked list is empty!\n");
        return;
    }

    if (head == tail) {
        temp = tail;
        head = tail = NULL;
    } else {
        curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        temp = tail;
        tail = curr;
        tail->next = NULL;
    }
    free(temp);
}

//pop mid
void pop_mid(int value) {
    if (head == NULL) {
        printf("Linked list is empty!\n");
        return;
    }

    if (head == tail && value == head->value) {
        temp = head;
        head = tail = NULL;
    } else if (value == head->value) { //pophead
        temp = head;
        head = head->next;
    } else {
        curr = head;

        while(curr->next != NULL) {
            if (curr->next->value == value) {
                break;
            }
            curr = curr->next;
        }

        if (curr->next == NULL) {
            printf("Can't find the value\n");
            return;
        }

        if (curr->next == tail) { //poptail
            tail = curr;
        }
        temp = curr->next;
        curr->next = temp->next;
    }
    free(temp);
}

// Print semua elemen
void print_all() {
    if (head == NULL) {
        printf("Linked list is empty!\n");
        return;
    }

    curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n"); // Menambahkan indikator akhir list
}

// Main function
int main() {
    push_mid(20);
    push_mid(25);
    push_mid(15);

    pop_mid(20);
    print_all();

    return 0;
}