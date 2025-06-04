#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int power_level;
    int height;
    char ancient_skill[101];
    struct node* left;
    struct node* right;
} node;

node* create_new_node(const char* ancient_skill, int power_level) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->height = 1;
    new_node->power_level = power_level;
    strcpy(new_node->ancient_skill, ancient_skill);
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

node* insert_node(node* root, const char* ancient_skill, int power_level) {
    if (!root) {
        return create_new_node(ancient_skill, power_level);
    }

    if (strcmp(ancient_skill, root->ancient_skill) < 0) {
        root->left = insert_node(root->left, ancient_skill, power_level);
    } else if (strcmp(ancient_skill, root->ancient_skill) > 0) {
        root->right = insert_node(root->right, ancient_skill, power_level);
    } else {
        printf("ERR : NOT A UNIQUE ANCIENT SKILL..\n");
        return root;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int bf = get_bf(root);

    if (bf > 1 && strcmp(ancient_skill, root->left->ancient_skill) < 0) {
        return right_rotate(root);
    }
    if (bf > 1 && strcmp(ancient_skill, root->left->ancient_skill) > 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (bf < -1 && strcmp(ancient_skill, root->right->ancient_skill) > 0) {
        return left_rotate(root);
    }
    if (bf < -1 && strcmp(ancient_skill, root->right->ancient_skill) < 0) {
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

node* delete_node(node* root, const char* ancient_skill) {
    if (!root) {
        printf("ERR : NO ANCIENT SKILL FOUND TO BE DELETED..\n");
        return NULL;
    }

    if (strcmp(ancient_skill, root->ancient_skill) < 0) {
        root->left = delete_node(root->left, ancient_skill);
    } else if (strcmp(ancient_skill, root->ancient_skill) > 0) {
        root->right = delete_node(root->right, ancient_skill);
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
            root->power_level = temp->power_level;
            strcpy(root->ancient_skill, temp->ancient_skill);
            root->left = delete_node(root->left, temp->ancient_skill);
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

void count_leaf(node* root, int* total_leaf) {
    if (!root) {
        return;
    }
    count_leaf(root->left, total_leaf);
    count_leaf(root->right, total_leaf);
    (*total_leaf)++;
}

int exist(node* root, const char* ancient_skill) {
    if (!root) {
        return 0;
    }

    if (strcmp(ancient_skill, root->ancient_skill) < 0) {
        return exist(root->left, ancient_skill);
    } else if (strcmp(ancient_skill, root->ancient_skill) > 0) {
        return exist(root->right, ancient_skill);
    } else {
        return 1;
    }
}

void find_ancient_skill(node* root, const char* ancient_skill, int* explore_total) {
    if (strcmp(ancient_skill, root->ancient_skill) == 0) {
        if (*explore_total == 0) {
            printf("Mamma Mia!\n");
        } else {
            printf("(F)\n");
        }
        return;
    }

    (*explore_total)++;
    if(strcmp(ancient_skill, root->ancient_skill) < 0) {
        printf("(L)");
        find_ancient_skill(root->left, ancient_skill, explore_total);
    } else if (strcmp(ancient_skill, root->ancient_skill) > 0) {
        printf("(R)");
        find_ancient_skill(root->right, ancient_skill, explore_total);
    }
}

void view_avl_tree(node* root) {
    if (!root) {
        return;
    }
    view_avl_tree(root->left);
    printf("%s\n", root->ancient_skill);
    view_avl_tree(root->right);
}

void exit_program(node *root)  {
    if (!root) {
        return;
    }
    exit_program(root->left);
    exit_program(root->right);
    free(root);
}

void print_menu() {
    printf("=== PAPER MARIO AND THE AVL TREE ===\n");
    printf("1. INSERT LEAF.\n");
    printf("2. DELETE LEAF.\n");
    printf("3. FIND ANCIENT SKILL.\n");
    printf("4. VIEW AVL TREE.\n");
    printf("5. EXIT PROGRAM.\n");
    printf("YOUR INPUT HERE >> ");
}

int main() {
    node* root = NULL;
    char ancient_skill[101];
    int power_level;
    int menu_option;
    do {
        system("cls");
        print_menu();
        scanf("%d", &menu_option);
        getchar();
        int explore_total = 0;
        int total_leaf = 0;
        switch(menu_option) {
            case 1 : 
                printf("PLEASE INPUT THE ANCIENT SKILL NAME TO INSERT >> ");
                scanf("%[^\n]", ancient_skill);
                getchar();

                printf("PLEASE INPUT THE POWER LEVEL OF THE ANCIENT SKILL >> ");
                scanf("%d", &power_level);
                getchar();

                root = insert_node(root, ancient_skill, power_level);
                system("pause");
                break;
            case 2 :
                printf("PLEASE INPUT THE ANCIENT SKILL NAME TO DELETE >> ");
                scanf("%[^\n]", ancient_skill);
                getchar();

                root = delete_node(root, ancient_skill);
                count_leaf(root, &total_leaf);
                printf("TOTAL LEAF : %d\n", total_leaf);
                system("pause");
                break;
            case 3 :
                printf("PLEASE INPUT THE ANCIENT SKILL NAME TO FIND >> ");
                scanf("%[^\n]", ancient_skill);
                getchar();
                if (exist(root, ancient_skill)) {
                    find_ancient_skill(root, ancient_skill, &explore_total);
                } else {
                    printf("ERR : CAN'T FIND ANCIENT SKILL.\n");
                }
                system("pause");
                break;
            case 4 :
                view_avl_tree(root);
                system("pause");
                break;
            case 5 :
                exit_program(root);
                break;
            default :
                printf("ERR : WRONG INPUT.\n");
                system("pause");
                break;
        }
    } while (menu_option != 5);

    printf("SUCCESSFULLY EXIT THE PAPER MARIO PROGRAM :).\n");
    
    return 0;
}