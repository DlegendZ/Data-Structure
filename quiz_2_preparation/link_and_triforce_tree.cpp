#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    char virtue[10];
    int height;
    struct node* left;
    struct node* right;
} node;

node* create_new_node(const char* virtue, int value) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->height = 1;
    new_node->value = value;
    strcpy(new_node->virtue, virtue);
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

node* insert_node(node* root, const char* virtue, int value) {
    if (!root) {
        return create_new_node(virtue, value);
    }

    if (value < root->value) {
        root->left = insert_node(root->left, virtue, value);
    } else if (value > root->value) {
        root->right = insert_node(root->right, virtue, value);
    } else {
        printf("ERR : UNABLE TO INSERT DUPLICATED VALUE.\n");
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

void update_virtue(node* root, int* power, int* wisdom, int* courage) {
    if (!root) {
        return;
    }
    update_virtue(root->left, power, wisdom, courage);
    update_virtue(root->right, power, wisdom, courage);
    if (strcmp(root->virtue, "Power") == 0) {
        (*power)++;
    }
    if (strcmp(root->virtue, "Wisdom") == 0) {
        (*wisdom)++;
    }
    if (strcmp(root->virtue, "Courage") == 0) {
        (*courage)++;
    }
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
        printf("ERR : UNABLE TO FIND THE ANCIENT NUMBER TO DELETE.\n");
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
            strcpy(root->virtue, temp->virtue);
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

void update_total_leaf(node* root, int* total_leaf) {
    if (!root) {
        return;
    }
    update_total_leaf(root->left, total_leaf);
    update_total_leaf(root->right, total_leaf);
    (*total_leaf)++;
}

void check_triforce(node* root, int* is_triforce) {
    if (!(*is_triforce)) {
        if (!root) {
            return;
        }
        
        if (root->left && root->right) {
            if ((strcmp(root->virtue, "Power") == 0) && (strcmp(root->left->virtue, "Wisdom") == 0) && (strcmp(root->right->virtue, "Courage") == 0)) {
                *is_triforce = 1;
                return;
            }
        }

        check_triforce(root->left, is_triforce);
        check_triforce(root->right, is_triforce);
    }
}

void view_avl_tree(node* root) {
    if (!root) {
        return;
    }
    view_avl_tree(root->left);
    printf("%s (ANCIENT NUMBER : %d)\n", root->virtue, root->value);
    view_avl_tree(root->right);
}

void free_all(node* root) {
    if (!root) {
        return;
    }
    free_all(root->left);
    free_all(root->right);
    free(root);
}

void print_menu() {
    printf("=== LINK AND TRIFORCE TREE ===\n");
    printf("1. INSERT A FRAGMENT.\n");
    printf("2. DELETE A FRAGMENT.\n");
    printf("3. FIND A TRIFORCE.\n");
    printf("4. VIEW AVL TREE STRUCTURE.\n");
    printf("5. EXIT PROGRAM.\n");
    printf("YOUR INPUT HERE >> ");
}

int main() {
    node* root = NULL;
    int menu_option;
    char virtue[10];
    int value;
    do {
        int power = 0;
        int wisdom = 0;
        int courage = 0;
        int total_leaf = 0;
        int is_triforce = 0;
        system("cls");
        print_menu();
        scanf("%d", &menu_option);
        getchar();

        switch(menu_option) {
            case 1 :
                printf("PLEASE INSERT VIRTUE TO INSERT >> ");
                scanf("%s", virtue);
                getchar();

                printf("PLEASE INSERT THE ANCIENT VALUE OF THIS VIRTUE >> ");
                scanf("%d", &value);
                getchar();

                root = insert_node(root, virtue, value);
                update_virtue(root, &power, &wisdom, &courage);
                printf("%d %d %d\n", power, wisdom, courage);
                system("pause");
                break;
            case 2 :
                printf("PLEASE INSERT THE ANCIENT VALUE TO DELETE >> ");
                scanf("%d", &value);
                getchar();

                root = delete_node(root, value);
                update_total_leaf(root, &total_leaf);
                printf("TOTAL LEAF : %d\n", total_leaf);
                system("pause");
                break;
            case 3 :
                check_triforce(root, &is_triforce);
                if (is_triforce) {
                    printf("MAY YOUR COURAGE TO SEEK WISDOM GRANT YOU POWER.\n");
                } else {
                    printf("TRIFORCE NOT FOUND.\n");
                }
                system("pause");
                break;
            case 4 :
                view_avl_tree(root);
                system("pause");
                break;
            case 5 :
                free_all(root);
                break;
            default :
                printf("ERR : WRONG INPUT.\n");
                system("pause");
                break;
        }
    } while (menu_option != 5);

    printf("THANK YOU FOR PLAYING WITH ZELDA.\n");

    return 0;
}