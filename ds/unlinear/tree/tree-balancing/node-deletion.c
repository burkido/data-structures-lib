#include <tree.h>
#include <stdio.h>
#include <stdlib.h>


void node_copy (NODE parent, NODE temp);


//iterative unbalanced delete
void tree_delete_iterative_unbalanced (TREE tree, unsigned long key){
	
  printf("tree_delete_iterative_unbalanced\n\n");
  NODE parent, node;
  char last;

  last = 0;
  parent = (NODE)tree;   // tree->root  ===  parent->left
  node = tree->root;
  while(node != NULL){
	if(key < node->key){
		parent = node;
		node = node->left;
		last = 0;
		}else if(key > node->key){
	 	   parent = node;
	       node = node->right;
		   last = 1;
		}else{
			break;
		}
	}
  if(node == NULL){
	printf("The node does not exist!\n");
	return;
	}
	
  if((node->left == NULL) && (node->right == NULL)){       //No child.
	free(node->data); // May have special data deletion!!!
	tree_node_kill(node);
	if(last == 0){
		parent->left = NULL;
	}else{
		parent->right = NULL;
	}
	}else if((node->left != NULL) && (node->right == NULL)){ //Left child.
		if(last == 0){
			parent->left = node->left;
		}else{
			parent->right = node->left;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}else if((node->left == NULL) && (node->right != NULL)){ //Right child.
		if(last == 0){
			parent->left = node->right;
		}else{
			parent->right = node->right;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}else{                                                   //Two children.
		NODE min = node->right;
		while(min->left != NULL){
			min = min->left;
		}
		min->left = node->left;
		if(last == 0){
			parent->left = node->right;
		}else{
			parent->right = node->right;
		}
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
	}
}

//recursive unbalanced delete
NODE tree_delete_recursive_unbalanced (NODE root, unsigned long key){
	
  printf("tree_delete_recursive_unbalanced\n\n");
  
  if (root == NULL){
      return NULL;
    }

  if (key < root->key){
      root->left = tree_delete_recursive_unbalanced (root->left, key);
    }else if (key > root->key){
      root->right = tree_delete_recursive_unbalanced (root->right, key);
    }else{
      if ((root->left == NULL) && (root->right == NULL)){		     	//No child.
	  free(root->data);
	  tree_node_kill (root);
	  root = NULL;
	}else if ((root->left != NULL) && (root->right == NULL)){			//Left child.
	  root = root->left;
	}else if ((root->left == NULL) && (root->right != NULL)){			//Right child.
	  root = root->right;
	}else{																//Two children.
	  NODE temp = root->right;
	  while (temp->left != NULL){
	      temp = temp->left;
	    }
	 temp->left = root->left;
	 printf("here! %lu\n", temp->key);
	 root = tree_delete_recursive_unbalanced (root->right, root->key);
	}
    }

  return root;
}

//iterative balanced delete
void tree_delete_iterative_balanced(TREE tree, unsigned long key ){
	
	printf("tree_delete_iterative_balanced\n\n");
	
	NODE parent, node;
	char last;

	last = 0;
	parent = (NODE)tree;   // tree->root  ===  parent->left
	node = tree->root;
	while(node != NULL){
		if(key < node->key){
			parent = node;
			node = node->left;
			last = 0;
		}else if(key > node->key){
			parent = node;
			node = node->right;
			last = 1;
		}else{
			break;
		}
	}
	if(node == NULL){
		printf("The node does not exist!\n");
		return;
	}
	if((node->left == NULL) && (node->right == NULL)){       //No child.
		free(node->data); // May have special data deletion!!!
		tree_node_kill(node);
		if(last == 0){
			parent->left = NULL;
		}else{
			parent->right = NULL;
		}
	}else if((node->left != NULL) && (node->right == NULL)){ //Left child.
		if(last == 0){
			parent->left = node->left;
		}else{
			parent->right = node->left;
		}
		free(node->data); 
		tree_node_kill(node);
	}else if((node->left == NULL) && (node->right != NULL)){ //Right child.
		if(last == 0){
			parent->left = node->right;
		}else{
			parent->right = node->right;
		}
		free(node->data); 
		tree_node_kill(node);
	}else{                                                   //Two children.
		NODE temp = node->left;
		while(temp->right != NULL){
			temp = temp->right; 
		}
		if(last == 0){
			tree_delete_iterative_balanced(tree, temp->key);
			parent->left->key = temp->key;
			parent->left->data = temp->data;
			//node_copy_for_iterative(parent, temp, last);
		}else{
			tree_delete_iterative_balanced(tree, temp->key);
			parent->right->key = temp->key;
			parent->right->data = temp->data;
			//node_copy_for_iterative(parent, temp, last);
		}
	}
}

//recursive balanced delete
NODE tree_delete_recursive_balanced(NODE root, unsigned long key){
	
	//printf("tree_delete_recursive_balanced\n\n");
	
	if (root == NULL){
      return NULL;
    }

  if (key < root->key){
      root->left = tree_delete_recursive_balanced(root->left, key);
    }else if (key > root->key){
      root->right = tree_delete_recursive_balanced(root->right, key);
    }else{
      if ((root->left == NULL) && (root->right == NULL)){		     	//No child.
	  	free(root->data);
	  	tree_node_kill (root);
	  	root = NULL;
	}else if ((root->left != NULL) && (root->right == NULL)){			//Left child.
	  root = root->left;
	}else if ((root->left == NULL) && (root->right != NULL)){			//Right child.
	  root = root->right;
	}else{																//Two children.
    	NODE temp = root->left;
    	while(temp->right != NULL){
    		temp = temp->right;
		}
	 node_copy(root, temp);
	 root->left = tree_delete_recursive_balanced(root->left, temp->key);
	}
	}

  return root;
}

void node_copy(NODE parent, NODE temp){
	
	/*NODE swap;
	swap = parent;
	parent = temp;
	temp = swap;*/
	
	parent->key = temp->key;
    parent->data = temp->data;
}

int main (){
  TREE t1 = tree_init ();

  tree_insert (t1, 25, NULL);
  tree_insert (t1, 5, NULL);
  tree_insert (t1, 24, NULL);
  tree_insert (t1, 28, NULL);
  tree_insert (t1, 3, NULL);
  tree_insert (t1, 11, NULL);
  tree_insert (t1, 18, NULL);
  tree_insert (t1, 23, NULL);
  tree_insert (t1, 27, NULL);
  tree_insert (t1, 9, NULL);
  tree_insert (t1, 19, NULL);
  tree_insert (t1, 34, NULL);
  tree_insert (t1, 80, NULL);
  
  tree_print (t1->root, 0);

  printf ("\n\n\n\n\n");
  
  tree_delete_iterative_unbalanced(t1, 15);     
  /*tree_delete_recursive_unbalanced (t1->root, 76);
  tree_delete_iterative_balanced(t1, 21);
  tree_delete_recursive_balanced(t1->root, 25);*/
    
  tree_print (t1->root, 0);

  tree_kill (t1);

  return 0;
}