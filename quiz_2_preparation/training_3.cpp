#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char character;
    int value;
    int height;
    struct node* left;
    struct node* right;
} node;

node* create_new_node(char character, int value) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->character = character;
    new_node->value = value;
    new_node->height = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int get_height(node* root) {
    if (!root) {
        return 0;
    }
    return root->height;
}

int get_bf(node* root) {
    if (!root) {
        return 0;
    }
    return get_height(root->left) - get_height(root->right);
}

node* left_rotate(node* x) {
    node* y = x->right;
    node* b = y->left;
    y->left = x;
    x->right = b;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    return y;
}

node* right_rotate(node* y) {
    node* x = y->left;
    node* b = x->right;
    x->right = y;
    y->left = b;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    return x;
}

node* insert_node(node* root, char character, int value) {
    if (!root) {
        return create_new_node(character, value);
    }

    if (value < root->value) {
        root->left = insert_node(root->left, character, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, character, value);
    } else {
        printf("ERR: UNABLE TO INSERT DUPLICATE VALUE.\n");
        return root;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int bf = get_bf(root);

    if (bf > 1 && value < root->left->value) {
        return right_rotate(root);
    }
    if (bf > 1 && value > root->left->value) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (bf < -1 && value > root->right->value) {
        return left_rotate(root);
    }
    if (bf < -1 && value < root->right->value) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

node* predecessor(node* root) {
    node* current = root->left;
    while (current->right) {
        current = current->right;
    }
    return current;
}

node* delete_node(node* root, int value) {
    if (!root) {
        printf("ERR: UNABLE TO FIND THE VALUE TO DELETE.\n");
        return NULL;
    }

    if (value < root->value) {
        root->left = delete_node(root->left, value);
    } else if (value > root->value) {
        root->right = delete_node(root->right, value);
    } else {
        if (!root->left || !root->right) {
            node* temp = (root->left) ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            
            free(temp);
        } else {
            node* temp = predecessor(root);
            root->value = temp->value;
            root->left = delete_node(root->left, temp->value);
        }
    }

    if (!root) {
        return NULL;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int bf = get_bf(root);

    if (bf > 1 && get_bf(root->left) >= 0) {
        return right_rotate(root);
    }
    if (bf > 1 && get_bf(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (bf < -1 && get_bf(root->right) <= 0) {
        return left_rotate(root);
    }
    if (bf < -1 && get_bf(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void print_in_order(node* root) {
    if (!root) {
        return;
    }
    print_in_order(root->left);
    printf("%c", root->character);
    print_in_order(root->right);
}

void print_menu() {
    printf("=== AVL TREE TEXT EDITOR ===\n");
    printf("1. INSERT NODE\n");
    printf("2. DELETE NODE\n");
    printf("3. PRINT IN ORDER TRAVERSAL\n");
    printf("4. EXIT PROGRAM.\n");
    printf("YOUR INPUT HERE >> ");
}

void clear_memories(node* root) {
    if (!root) {
        return;
    }
    clear_memories(root->left);
    clear_memories(root->right);
    free(root);
}

int main() {
    node* root = NULL;
    int menu_option;
    char character;
    int value;
    do {
        system("cls");
        print_menu();
        scanf("%d", &menu_option);
        getchar();

        switch(menu_option) {
            case 1 :
                printf("PLEASE INPUT THE CHARACTER TO STORE >> ");
                scanf("%c", &character);
                getchar();

                printf("PLEASE INPUT THE VALUE TO INSERT >> ");
                scanf("%d", &value);
                getchar();

                root = insert_node(root, character, value);
                system("pause");
                break;
            case 2 :
                printf("PLEASE INPUT THE VALUE TO DELETE >> ");
                scanf("%d", &value);
                getchar();

                root = delete_node(root, value);
                system("pause");
                break;
            case 3 :
                print_in_order(root);
                printf("\n");
                system("pause");
                break;
            case 4 :
                clear_memories(root);
                break;
            default :
                printf("ERR: WRONG INPUT.\n");
                system("pause");
                break;
        }
    } while(menu_option != 4);

    printf("THANK YOU FOR USING OUR SERVICE TODAY.\n");

    return 0;
}