# data-structures-lib
A generic library that implements various linear and unlinear data structures in C language.

## Getting Started

To use the library, simply include the relevant .h files in your project and compile the .c files along with your own code.

### Description

This code is a simple implementation of linear and unlinear data structures. It is used to store data in a **linked list**, **stack**, **queue**, **tree**, **avl-tree** format and more including **balanced and unbalanced deletions**. It can be used to store **any type of data**, as the data is stored as a **void pointer**. 

### Example Structure of Linked List and Tree

```c
Linked List
+-----------------+    +-----------------+    +-----------------+
typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s{
	LINKED_LIST_NODE next; /* Do not change the order */
	void *data;
} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;
typedef struct LINKED_LIST_s{
  	LINKED_LIST_NODE head;
} LINKED_LIST_t[1], *LINKED_LIST;

typedef struct DATA_s{
	void *data;
} DATA_t[1], *DATA;

Tree
+-----------------+    +-----------------+    +-----------------+
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
```

### Example Usage

```c
#include "linked-list/linked_list.h"
#include "helper/helper.h"

void main() {

    LINKED_LIST list = linked_list_init();
    LINKED_LIST list2 = linked_list_init();
    DATA data1, data2, data3, data4, data5, data6, data7, data8;

    data1 = data_init((int*)2);
    data2 = data_init((int*)4);
    data3 = data_init((int*)6);
    data4 = data_init((int*)8);

    data5 = data_init((int*)1);
    data6 = data_init((int*)3);
    data7 = data_init((int*)5);
    data8 = data_init((int*)7);

    linked_list_append(list, data1);
    linked_list_append(list, data2);
    linked_list_append(list, data3);
    linked_list_append(list, data4);

    linked_list_append(list2, data5);
    linked_list_append(list2, data6);
    linked_list_append(list2, data7);
    linked_list_append(list2, data8);


    linked_list_fprint(list, stdout, integer_printer);
    linked_list_fprint(list2, stdout, integer_printer);

    linked_list_concatenate(list, list2);

    linked_list_fprint(list, stdout, integer_printer);
}