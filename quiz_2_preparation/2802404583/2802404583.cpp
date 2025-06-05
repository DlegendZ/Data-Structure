#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char p[11];
	int h;
	int height;
	struct node* left;
	struct node* right;
} node;

node* create_new_node(const char* p, int h) {
	node* new_node = (node*) malloc(sizeof(node));
	new_node->h = h;
	strcpy(new_node->p, p);
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

node* insert_node(node* root, const char* p, int h) {
	if (!root) {
		return create_new_node(p, h);
	}
	
	if (strcmp(p, root->p) < 0) {
		root->left = insert_node(root->left, p, h);
	} else if (strcmp(p, root->p) > 0) {
		root->right = insert_node(root->right, p, h);
	} else {
		printf("ERR : UNABLE TO INSERT DUPLICATED PLAYER.\n");
		return root;
	}
	
	root->height = max(get_height(root->left), get_height(root->right)) + 1;
	int bf = get_bf(root);
	
	if (bf > 1 && strcmp(p, root->p) < 0) {
		return right_rotate(root);
	}
	if (bf > 1 && strcmp(p, root->p) > 0) {
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	if (bf < -1 && strcmp(p, root->p) > 0) {
		return left_rotate(root);
	}
	if (bf < -1 && strcmp(p, root->p) < 0) {
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

node* delete_node(node* root, const char* p) {
	if (!root) {
		printf("UNABLE TO FIND A PLAYER.\n");
		return NULL;
	}
	
	if (strcmp(p, root->p) < 0) {
		root->left = delete_node(root->left, p);
	} else if (strcmp(p, root->p) > 0) {
		root->right = delete_node(root->right, p);
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
			root->h = temp->h;
			strcpy(root->p, temp->p);
			root->left = delete_node(root->left, temp->p);
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

void exist(node* root, const char* p, int x, int* is_exist) {
	if (!(*is_exist)) {
		if (!root) {
			return;
		}
		
		exist(root->left, p, x, is_exist);
		exist(root->right, p, x, is_exist);
		if (strcmp(root->p, p) == 0) {
			(*is_exist) = 1;
			root->h += x;
			printf("Heal player %s, current health: %d\n", root->p, root->h);
		}
		
	}
}

void damage_player(node* root, const char* p, int x, int* is_exist, node* origin_root) {
	if (!(*is_exist)) {
		if (!root) {
			return;
		}
		
		damage_player(root->left, p, x, is_exist, origin_root);
		damage_player(root->right, p, x, is_exist, origin_root);
		if (strcmp(root->p, p) == 0) {
			(*is_exist) = 1;
			root->h -= x;
			if (root->h <= 0) {
				printf("Player %s is removed from the game.\n", root->p);
				origin_root = delete_node(origin_root, p);
			} else {
				printf("Damage player %s, current health: %d\n", root->p, root->h);
			}
		}
	}	
}

void view_avl_tree(node* root) {
	if (!root) {
		return;
	}
	
	view_avl_tree(root->left);
	view_avl_tree(root->right);
	printf("%s\n", root->p);
}

int main() {
	node* root = NULL;
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		char scenario;
		char p[11];
		int h;
		
		int is_exist = 0;
		
		scanf("%c %s %d", &scenario, p, &h);
		getchar();
		
		if (scenario == '+') {
			exist(root, p, h, &is_exist);
			if (!is_exist || !root) {
				root = insert_node(root, p, h);
				printf("Player %s is entered to the game.\n", p);
			}
		}
		if (scenario == '-') {
			damage_player(root, p, h, &is_exist, root);
			if (!is_exist || !root) {
				printf("Player %s is not in the game.\n", p);
			}
		}
	}
	return 0;
}
