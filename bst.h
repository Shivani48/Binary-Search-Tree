#include<stdio.h>
#ifndef BST
#define BST

//DATA STRUCTURE
typedef struct Data{
	int value;
} Data;

//NODE STRUCTURE
typedef struct Node{
	Data data;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
} Node;

//TREE STRUCTURE
typedef struct Tree{
	Node * root;
	Data * (* insert)(struct Tree *, Data);
	Data * (* search)(struct Tree * bst, Data value);
	void (* sort)(struct Tree *, Data *);
	int (* compare)(struct Tree *t, struct Tree * copy);
	struct Tree * (*clone)(struct Tree * t);
	void (* delete)(struct Tree * bst);
	void (* removeData)(struct Tree * bst, Data value);
} Tree;

//FUNCTIONS
Node * newNode(Data d, Node * parent);
Tree * newTree();
Data * insert(Tree *t, Data d);
Data * search(Tree *t, Data d);
//void remove(Tree *t, Data d);
void sort(Tree *t, Data * d);
int compare(Tree *t, Tree *copy);
Tree * clone(Tree *t );
void delete(Tree *bst);

#endif




