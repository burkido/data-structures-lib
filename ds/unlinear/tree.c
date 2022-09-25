#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


TREE tree_init() {
	TREE t = (TREE)malloc(sizeof(TREE_t));
	t->root = NULL;

	return t;
}

void tree_kill(TREE t){
	free(t);
}

NODE tree_node_init(unsigned long key, void *data){
	NODE n = (NODE)malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

void tree_node_kill(NODE n){
	free(n);
}

NODE tree_insert_recursive(NODE node, unsigned long key, void *data){
	if(node != NULL)
		if(key < node->key)
			node->left = tree_insert_recursive(node->left, key, data);
	    else if(key > node->key) 
			node->right = tree_insert_recursive(node->right, key, data);
		else
			printf("Error! File: tree.c Line: 31 @tree_insert_recursive. Duplicate node %lu.\n", key);		
	else
		node = tree_node_init(key, data);

	return node;
}

void tree_insert(TREE tree, unsigned long key, void *data){
	if(tree->root == NULL)
		tree->root = tree_node_init(key, data);
	else
		tree->root = tree_insert_recursive(tree->root, key, data);
	
}

void tree_traverse_preorder(NODE node){
	if(node != NULL)
		printf("%lu %p %p %p \n", node->key, node, node->left, node->right);
		fflush(stdout);
		tree_traverse_preorder(node->left);
		tree_traverse_preorder(node->right);
	
}

void tree_print(NODE node, int k){
	int i;
	if(node != NULL){
		tree_print(node->right, k+3);
		for (i = 0; i < k; i++){
			printf(" ");
		}
		printf("%lu\n", node->key);
		fflush(stdout);
		tree_print(node->left, k+3);
	}
}