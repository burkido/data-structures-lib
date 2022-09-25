#include <tree.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 8




void left_rotation(NODE gparent, NODE parent, NODE child);

void tree_delete_iterative_unbalanced (TREE tree, unsigned long key){
	
  printf("tree_delete_iterative_unbalanced\n\n");
  NODE parent, node;
  char last;

  last = 0;
  parent = (NODE)tree;   // tree->root  ===  parent->right
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

void left_rotation(NODE gparent, NODE parent, NODE child){
	parent->right = child->left;
	child->left = parent;
	gparent = child;
	
}

void do_rotation(TREE tree, NODE gparent, NODE parent, NODE child, int i){
   
    gparent = NULL;		parent = tree->root;		child = parent->right;
    
    while(i > 0 && child != NULL){ // childin NULL oldugu durumda da while bitmeli
        if(gparent != NULL){ 
			gparent->right = child; // daha sonraki atamalarda bu baglantiyi unutmamaliyiz
		}
		else{
			tree->root = child; // ilk atama direkt olarak child
		}
        //left_rotation(gparent, parent, child); // function call yapildiginda pointerlarda sorun oluyor, left_rotation diye ayri fonksiyona gerek yok
        parent->right = child->left;
		child->left = parent;
		gparent = child;
        
        //printf("gparent key is: %lu\n", gparent->key);
	    //printf("parent key is: %lu\n", parent->key);
	    //printf("child key is: %lu\n", child->key);
        //tree_print(tree->root, 0);
        //gparent = child; //gereksiz, zaten yukarida yapiliyor
 
        parent = gparent->right;
		if(parent != NULL){ //parentin NULL oldugu durumda bu atama yanlis olacaktir, bu yuzden bu checke ihtiyacimiz var
        	child = parent->right;
        }
        i--;
    }
}

void balance_tree(TREE tree, NODE gparent, NODE parent, NODE child, int n){
	
	const double x = 2;
	int m = pow(x, floor(log2(n + 1))) - 1; // burada hesabin tam olarak dogru yapilabilmesi icin floor kullanmak gerekli

	do_rotation(tree, gparent, parent, child, n - m);

	while(m > 1){
	    m = m >> 1;
	    do_rotation(tree, gparent, parent, child, m);
	}
	
}

void right_rotation(NODE gparent, NODE parent, NODE child){
	
	parent->left = child->right;
    child->right = parent;
    gparent->right = child;

}

void backbone(TREE tree, NODE gparent, NODE parent, NODE child){

	while(parent != NULL){
	   if(parent->left != NULL){
	   	child = parent->left;
	    right_rotation(gparent, parent, child);
		parent = child;
	   }else{
	   	gparent = parent;
	   	parent = parent->right;
	   }
	}

    printf ("\n\n\n\n\n");
	tree_print(tree->root, 0);
	
	balance_tree(tree, gparent, parent, child, 6);
	
    printf ("\n\n\n\n\n");
	tree_print(tree->root, 0);
	
}


int main (){
  TREE t1 = tree_init ();

  tree_insert (t1, 33, NULL);
  tree_insert (t1, 21, NULL);
  tree_insert (t1, 58, NULL);
  tree_insert (t1, 9, NULL);
  tree_insert (t1, 25, NULL);
  tree_insert(t1, 45, NULL);
  tree_insert(t1, 23, NULL);
  tree_insert(t1, 51, NULL);

  tree_print (t1->root, 0);
  
  printf ("\n\n\n\n\n");
  
  NODE gparent, parent, child;

  gparent = (NODE)t1;		parent = (NODE)t1;		child = parent->left;

  backbone(t1, gparent, parent, child);

  
  //tree_print(t1->root, 0);

  tree_kill (t1);

  return 0;
}