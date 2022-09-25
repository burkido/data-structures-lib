#ifndef TREE_H_
#define TREE_H_

typedef struct NODE_s *NODE;
typedef struct NODE_s {
	NODE left;
	NODE right;
	unsigned long key;
	void *data;
} NODE_t[1];

typedef struct {
	NODE root;
} TREE_t[1], *TREE;

/* Function declerations*/
TREE tree_init();
void tree_kill(TREE t);
NODE tree_node_init(unsigned long key, void *data);
void tree_node_kill(NODE n);
NODE tree_insert_recursive(NODE node, unsigned long key, void *data);
void tree_insert(TREE tree, unsigned long key, void *data);
void tree_traverse_preorder(NODE node);
void tree_print(NODE node, int k);


#endif