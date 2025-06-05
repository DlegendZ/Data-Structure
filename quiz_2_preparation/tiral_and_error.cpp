#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
} node;

node* create_node(int value) {
    node* new_node = (node*) malloc(sizeof(node));
    new_node->value = value;
    return new_node;
}

void function(node* root) {
    printf("%d\n", root);
}

int main() {
    node* root = create_node(90);
    printf("%d\n", root);

    function(root);
}


