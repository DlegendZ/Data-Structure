#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next;
} *head = NULL, *tail= NULL, *curr = NULL, *temp= NULL;

struct node* create_new_node(int value) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void push_head(int value) {
    struct node* new_node = create_new_node(value);

    if (head == NULL) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head = new_node;
    }
}

void push_tail(int value) {
    struct node* new_node = create_new_node(value);

    if (head == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

void push_mid(int value) {
    struct node* new_node = create_new_node(value);

    if (head == NULL) {
        head = tail = new_node;
    }
    else if (new_node->value < head->value) {
        new_node->next = head;
        head = new_node;
    }
    else if (new_node->value >= tail->value) {
        tail->next = new_node;
        tail = new_node;
    }
    else {
        curr = head;

        while(curr != NULL) {
            if (curr->next->value > new_node->value) {
                break;
            }

            curr = curr->next;
        }

        new_node->next = curr->next;
        curr->next= new_node;
    }
}

void print_node() {
    if (head == NULL) {
        printf("Linked list is empty.\n");
    }

    curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->value);

        curr = curr->next;
    }

    printf("Null");
}

void pop_head() {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    if (head == tail) {
        temp = head;
        head = tail = NULL;
    }
    else {
        temp = head;
        head = head->next;
    }

    free(temp);
}

void pop_tail() {
    if (head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    if (head == tail) {
        temp = head;
        head = tail = NULL;
    }
    else {
        temp = tail;
        
        curr = head;
        while(curr->next != tail) {
            curr = curr->next;
        }

        tail = curr;
        tail->next = NULL;
    }

    free(temp);
}

void pop_mid(int value) {
    if (head == NULL) {
        printf("Linked list is empty.\n");
    }

    if (head == tail && head->value == value) {
        temp = head;
        head = tail = NULL;
    }
    else if (head->value == value) {
        temp = head;
        head = head->next;
    }
    else {
        curr = head;

        while (curr->next != NULL) {
            if (curr->next->value == value) {
                break;
                
            }
            curr = curr->next;
        }

        if (curr->next == NULL) {
            printf("Can't find the value.");
            return;
        }

        if (curr->next == tail) {
            tail = curr;
        }

        temp = curr->next;
        curr->next = temp->next;
    }

    free(temp);
}

int main() {
    push_head(20);
	push_head(25);
	push_head(15);

	push_tail(20);
	push_tail(25);
	push_tail(15);

    push_mid(20);
    push_mid(25);
    push_mid(15);

    pop_head();
    pop_tail();
    pop_mid(20);
	
	print_node();
    return 0;
}