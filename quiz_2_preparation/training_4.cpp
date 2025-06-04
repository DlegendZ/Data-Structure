#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int height;
    struct node* left;
    struct node* right;
} node;

node* create_new_node(int value) {
    node* new_node = (node*) malloc(sizeof(node));
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

node* insert_value(node* root, int value) {
    if(!root) {
        return create_new_node(value);
    }

    if (value < root->value) {
        root->left = insert_value(root->left, value);
    } else if (value > root->value) {
        root->right = insert_value(root->right, value);
    } else {
        printf("ERR : CAN'T INSERT DUPLICATED VALUE.\n");
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

node* delete_value(node* root, int value) {
    if(!root) {
        printf("ERR : CAN'T FIND THE VALUE TO DELETE.\n");
        return NULL;
    }

    if (value < root->value) {
        root->left = delete_value(root->left, value);
    } else if (value > root->value) {
        root->right = delete_value(root->right, value);
    } else {
        if (!root->right || !root->left) {
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
            root->left = delete_value(root->left, temp->value);
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
    printf("%d (BF : %d)\n", root->value, get_bf(root));
    print_in_order(root->right);
}

void free_post_order(node* root) {
    if (!root) {
        return;
    }
    free_post_order(root->left);
    free_post_order(root->right);
    free(root);
}

void print_menu() {
    printf("=== AVL TREE PROGRAM ===\n");
    printf("1. INSERT A VALUE.\n");
    printf("2. DELETE A VALUE.\n");
    printf("3. VIEW AVL TREE.\n");
    printf("4. EXIT PROGRAM.\n");
    printf("YOUR INPUT HERE >> ");
}

int main() {
    node* root = NULL;
    int menu_option;
    int value;
    do {
        system("cls");
        print_menu();
        scanf("%d", &menu_option);
        getchar();

        switch(menu_option) {
            case 1 :
                printf("PLEASE INPUT A VALUE TO INSERT >> ");
                scanf("%d", &value);
                getchar();
                
                root = insert_value(root, value);
                system("pause");
                break;
            case 2 :
                printf("PLEASE INPUT A VALUE TO DELETE >> ");
                scanf("%d", &value);
                getchar();

                root = delete_value(root, value);
                system("pause");
                break;
            case 3 :
                print_in_order(root);
                system("pause");
                break;
            case 4 :
                free_post_order(root);
                break;
            default :
                printf("ERR : WRONG INPUT.\n");
                system("pause");
                break;
        }
    } while (menu_option != 4);

    printf("THANK YOU FOR USING OUR SERVICE.\n");
    
    return 0;
}