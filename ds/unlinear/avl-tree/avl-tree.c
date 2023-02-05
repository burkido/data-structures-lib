#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 8

typedef struct {
	char* name;
	char* surname;
	float gpa;
} STUDENT_t[1], * STUDENT;

typedef struct NODE_s* NODE;
typedef struct NODE_s {
	NODE right;
	NODE left;
	int height;
	unsigned long key;
	void* data;
} NODE_t[1];

typedef struct {
	NODE root;
} TREE_t[1], * TREE;


int max_num(int a, int b);
int height(NODE node);

STUDENT student_init(char* name, char* surname, float gpa) {
	STUDENT s = (STUDENT)malloc(sizeof(STUDENT_t));
	s->name = name;
	s->surname = surname;
	s->gpa = gpa;
	return s;
}

void student_kill(STUDENT s) {
	free(s);
}

TREE tree_init() {
	TREE t = (TREE)malloc(sizeof(TREE_t));
	t->root = NULL;
	return t;
}

void tree_kill(TREE t) {
	free(t);
}

NODE tree_node_init(unsigned long key, void* data) {
	NODE n = (NODE)malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

void tree_node_kill(NODE n) {
	free(n);
}

NODE tree_insert_recursive(NODE node, unsigned long key, void* data) {
	if (node != NULL)
	{
		if (key < node->key) {
			node->left = tree_insert_recursive(node->left, key, data);
		}
		else if (key > node->key) {
			node->right = tree_insert_recursive(node->right, key, data);
		}
		else {
			printf("Error: duplicate node %lu.\n", key);
		}
	}
	else {
		node = tree_node_init(key, data);
	}
	return node;
}

void tree_insert(TREE tree, unsigned long key, void* data) {
	if (tree->root == NULL) {
		tree->root = tree_node_init(key, data);
	}
	else {
		tree->root = tree_insert_recursive(tree->root, key, data);
	}
}

void tree_traverse_preorder(NODE node) {

	if (node != NULL) {
		printf("%lu %p %p %p \n", node->key, node, node->left, node->right);
		fflush(stdout);
		tree_traverse_preorder(node->left);
		tree_traverse_preorder(node->right);
	}
}

//printf("%lu %p %p %p \n", node->key, node, node->left, node->right);
//fflush(stdout);

void tree_print(NODE node, int k) {
	int i;
	if (node != NULL) {
		tree_print(node->right, k + 4);
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		printf("%lu\n", node->key);
		fflush(stdout);
		tree_print(node->left, k + 4);
	}
}

void tree_delete_iterative_unbalanced(TREE tree, unsigned long key) {

	printf("tree_delete_iterative_unbalanced\n\n");
	NODE parent, node;
	char last;

	last = 0;
	parent = (NODE)tree;   // tree->root  ===  parent->right
	node = tree->root;
	while (node != NULL) {
		if (key < node->key) {
			parent = node;
			node = node->left;
			last = 0;
		}
		else if (key > node->key) {
			parent = node;
			node = node->right;
			last = 1;
		}
		else {
			break;
		}
	}
	if (node == NULL) {
		printf("The node does not exist!\n");
		return;
	}

	if ((node->left == NULL) && (node->right == NULL)) {       //No child.
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
		if (last == 0) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
	}
	else if ((node->left != NULL) && (node->right == NULL)) { //Left child.
		if (last == 0) {
			parent->left = node->left;
		}
		else {
			parent->right = node->left;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}
	else if ((node->left == NULL) && (node->right != NULL)) { //Right child.
		if (last == 0) {
			parent->left = node->right;
		}
		else {
			parent->right = node->right;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}
	else {                                                   //Two children.
		NODE min = node->right;
		while (min->left != NULL) {
			min = min->left;
		}
		min->left = node->left;
		if (last == 0) {
			parent->left = node->right;
		}
		else {
			parent->right = node->right;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}
}


NODE left_rotation(NODE node) {

	NODE node2 = node->right;
	NODE temp = node2->left;

	node2->left = node;
	node->right = temp;

	node->height = 1 + max_num(height(node->left), height(node->right));
	node2->height = 1 + max_num(height(node2->left), height(node2->right));

	return node2;

}

NODE right_rotation(NODE node) {

	NODE node2 = node->left;
	NODE temp = node2->right;

	node2->right = node;
	node->left; temp;

	node->height = 1 + max_num(height(node->left), height(node->right));
	node2->height = 1 + max_num(height(node2->left), height(node2->right));

	return node2;
}

int max_num(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}


int height(NODE node) {

	if (node == NULL) {
		return 0;
	}
	else {
		return node->height;
	}

}

NODE avl_tree_insert(NODE node, unsigned long key) {

	int isBalanced = 0;

	//NODE node = (NODE)tree;

	if (node == NULL) {
		return tree_node_init(key, NULL);
	}

	if (key < node->key) {
		node->left = avl_tree_insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = avl_tree_insert(node->right, key);
	}
	else {
		return node;
	}

	node->height = 1 + max_num(height(node->left), height(node->right));

	isBalanced = height(node->left) - height(node->right);

 
	if (isBalanced > 1 && key < node->left->key) {			// LL case
		return right_rotation(node);
	}
	if (isBalanced < -1 && key > node->right->key) {		// RR case
		return left_rotation(node);
	}
	if (isBalanced > 1 && key > node->left->key) {			//LR case
		node->left = left_rotation(node->left);
		return right_rotation(node);
	}
	if (isBalanced < -1 && key < node->right->key) {		//RL case
		node->right = right_rotation(node->right);
		return left_rotation(node);
	}

	return node;
}


int main() {
	TREE t1 = tree_init();
	

	/*node = avl_tree_insert(node, 23);
	node = avl_tree_insert(node, 26);
	node = avl_tree_insert(node, 44);
	node = avl_tree_insert(node, 9);
	node = avl_tree_insert(node, 4);
	node = avl_tree_insert(node, 15);
	node = avl_tree_insert(node, 30);
	node = avl_tree_insert(node, 17);
	node = avl_tree_insert(node, 14);
	node = avl_tree_insert(node, 11);
	node = avl_tree_insert(node, 2);
	node = avl_tree_insert(node, 3);
	node = avl_tree_insert(node, 7);*/



	/*node = avl_tree_insert(t1->root, 23);
	node = avl_tree_insert(t1->root, 26);
	node = avl_tree_insert(t1->root, 44);
	node = avl_tree_insert(t1->root, 9);
	node = avl_tree_insert(t1->root, 4);
	node = avl_tree_insert(t1->root, 15);
	node = avl_tree_insert(t1->root, 30);
	node = avl_tree_insert(t1->root, 17);
	node = avl_tree_insert(t1->root, 14);
	node = avl_tree_insert(t1->root, 11);
	node = avl_tree_insert(t1->root, 2);
	node = avl_tree_insert(t1->root, 3);
	node = avl_tree_insert(t1->root, 7);*/


	/*t1->root = avl_tree_insert(node, 23);
	t1->root = avl_tree_insert(node, 26);
	t1->root = avl_tree_insert(node, 44);
	t1->root = avl_tree_insert(node, 9);
	t1->root = avl_tree_insert(node, 4);
	t1->root = avl_tree_insert(node, 15);
	t1->root = avl_tree_insert(node, 30);
	t1->root = avl_tree_insert(node, 17);
	t1->root = avl_tree_insert(node, 14);
	t1->root = avl_tree_insert(node, 11);
	t1->root = avl_tree_insert(node, 2);
	t1->root = avl_tree_insert(node, 3);
	t1->root = avl_tree_insert(node, 7);*/



	t1->root = avl_tree_insert(t1->root, 23);
	t1->root = avl_tree_insert(t1->root, 26);
	t1->root = avl_tree_insert(t1->root, 44);
	t1->root = avl_tree_insert(t1->root, 9);
	t1->root = avl_tree_insert(t1->root, 4);
	t1->root = avl_tree_insert(t1->root, 15);
	t1->root = avl_tree_insert(t1->root, 30);
	t1->root = avl_tree_insert(t1->root, 17);
	t1->root = avl_tree_insert(t1->root, 14);
	t1->root = avl_tree_insert(t1->root, 11);
	t1->root = avl_tree_insert(t1->root, 2);
	t1->root = avl_tree_insert(t1->root, 3);
	t1->root = avl_tree_insert(t1->root, 7);
	
	tree_print(t1->root, 0);


	//tree_traverse_preorder(t1->root);
	//tree_traverse_preorder(node);
	
	tree_kill(t1);

	return 0;
}