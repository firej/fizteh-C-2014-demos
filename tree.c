#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct trnode{
	int data;
	struct trnode* left;
	struct trnode* right;
} node;

#define ARR_SIZE	15

node* find_node(node* root, int data);
void add_node(node** root, node* n);
void remove_node(node** root, int data);

int main(int argc, char ** argv) {
	node* root = NULL;
    srand((unsigned int)time(NULL));

	for (unsigned int i = 0; i < ARR_SIZE; i++) {
		node* n = (node *)calloc(1, sizeof(node));
		n->data = rand() % 100;
        add_node(&root, n);
    }

	return 0;
}

node* find_node(node* root, int data) {
	if (root) {
		if (root->data == data)
			return root;
		else if (root->data > data)
				return find_node(root->right, data);
			else
				return find_node(root->left, data);
	}
	else
		return NULL;
}

void add_node(node** root, node* n) {
	if (!(*root)) {
		*root = n;
		return;
	}
	if ((*root)->data > n->data)
		add_node(&((*root)->left), n);
	else
		add_node(&((*root)->right), n);
}


void remove_node(node **root, int data) {
	if (*root == NULL)
		return;
	if ((*root)->data < data) {
		remove_node(&((*root)->right), data);
	}
	else if ((*root)->data > data) {
		remove_node(&((*root)->left), data);
	}
	else {
		if ((*root)->left == NULL && (*root)->right == NULL){
			free(*root);
			*root = NULL;
		}
		else if ((*root)->right == NULL) {
			node * tmp = (*root)->left;
			free(*root);
			*root = tmp;
		}
		else if ((*root)->left == NULL) {
			node * tmp = (*root)->right;
			free(*root);
			*root = tmp;
		}
		else if ((*root)->right->left == NULL) {
			(*root)->right->left = (*root)->left;
			node * tmp = (*root)->right;
			free(*root);
			*root = tmp;
		}
		else {
			node * tmp = (*root)->left;
			node * r = (*root)->right;
			free(*root);
			*root = r;
			node * most_left = (*root)->left;
			for (;most_left->left;)
				most_left = most_left->left;
			most_left->left = tmp;
		}
	}
}













// node* find_parent(node* root, node* n) {
// 	if (root) {
// 		if (root->left == n || root->right == n)
// 			return root;
// 		else if (root->data > n->data)
// 				return find_parent(root->right, n);
// 			else
// 				return find_parent(root->left, n);
// 	}
// 	else
// 		return NULL;
// }

// void remove_node(node** root, node* n) {
// 	if (*root == n && *root->left == NULL && *root->right == NULL){
// 		*root = NULL;
// 		return;
// 	}
// 	node * parent = find_parent(*root, n);
// 	if (parent){
// 		if (parent->left == n) {
// 			parent->left = n->left;
// 		}
// 		else {
// 			parent->right = n->left;
// 		}
// 	}
// 	else {
// 		*root = n->left;
// 	}
// }












