#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

//NODE CONSTRUCTOR
Node * newNode(Data d, Node * parent){
  Node * n = malloc(sizeof(Node));
  n -> data = d;
  n -> left = n -> right = NULL;
  n -> parent = parent;
  return n;
}

//TREE CONSTRUCTOR  
Tree * newTree(){
  Tree * t = malloc( sizeof(Tree) );
  t -> root = NULL;
  t -> insert = insert;
  t -> search = search;
  t -> sort = sort;
  t -> compare = compare;
  t -> clone = clone;
  t -> delete = delete;
  t -> removeData = remove_Node;
  return t;
}

//INSERTION
Data * insertNode(Node * n, Data d){
  Data * r = &d;
  if( d.value < n -> data.value){
      if(n -> left == NULL)
          n -> left = newNode(d , n);
      else
          return insertNode( n -> left ,d);
  }
  else if( d.value > n -> data.value){
      if(n -> right == NULL)
          n -> right = newNode(d , n);
      else
          return insertNode( n -> right ,d);
  }
  else
        return NULL;
  return r;
  
}
      
Data * insert(Tree *t, Data d){
  Data * check ;
  if( t -> root == NULL)
      t -> root = newNode(d, NULL);
  else
      check = insertNode(t -> root, d);
  if(check == NULL)
      return NULL;
  return check ;
}

//SEARCHING
Node * searchHelp(Node * n, Data d){
	if(d.value < n -> data.value){
		if(n -> left == NULL)
			return NULL;
		else
			return searchHelp(n -> left, d);
	}
	else if(d.value > n -> data.value){
		if(n -> right == NULL)
			return NULL;
		else
			return searchHelp(n -> right, d);
   }
	
  return n;
}

Data * search(Tree *t, Data d){
   Node * check = NULL;

   if( t -> root == NULL)
       return NULL;
   else
       check = searchHelp( t -> root, d);
   if(check == NULL)
       return NULL;
   return &check ->data;
}

//SORTING
int i = 0;
void inorder(Node * n, Data * d){
  if(n -> left != NULL)
    inorder(n -> left, d);
    d[i] = n -> data;
    i++;
  if(n -> right != NULL)
    inorder(n -> right, d);
  
} 
  
void sort(Tree *t, Data * d){
   Node * n = t -> root;
   inorder(n, d);
}

//COPY
void preOrderClone(Node * n, Tree * t){
  if(n== NULL){
    return;
  }
  t -> insert(t , n -> data);
  preOrderClone(n -> left, t);
  preOrderClone(n -> right, t);
}

Tree * clone(Tree * t){
  if(t->root == NULL){
    return NULL;
  }
  Node * n = t -> root;
  Tree * new_tree = newTree();
  preOrderClone(n, new_tree);
  return new_tree;
}

void preOrderCompare(Node * n1, Node * n2, int * value){
  if(n1 == NULL && n2 == NULL){
    return;
  }
  else if(n1 == NULL || n2 == NULL){
    * value = 1;
     return;
  }
  if(n1 -> data.value != n2 -> data.value){
    * value = 1;
  }
  preOrderCompare(n1 -> left, n2 -> left, value);
  preOrderCompare(n1 -> right, n2 -> right, value);
}

int compare(Tree * t1, Tree * t2){
  if(t1 == NULL && t2 == NULL){
    return 1;
  }
  else if(t1 == NULL || t2 == NULL){
    return 0;
  }
  Node * n1 = t1 -> root;
  Node * n2 = t2 -> root;
  int val = 0;
  preOrderCompare(n1 , n2, &val);
  
   if(val == 0){
     return 1;
   }
  return 0;
}

//REMOVE
Node * searchNodeHelper(Node * n, Data d){
  if( n -> data.value == d.value){
    return n;
  }
  else if(n -> data.value < d.value){
    if(n -> right == NULL){
      return NULL;
    }
    else{
      return searchNodeHelper(n -> right, d);
    }
  }
  else if(n -> data.value > d.value){
    if(n -> left == NULL){
      return NULL;
    }
    else{
      return searchNodeHelper(n -> left, d);
    }
  }  
}

Node * searchNode(Tree * t, Data value){
  if(t -> root == NULL){
    return NULL;
  }
  return searchNodeHelper(t -> root,value);
}



void freeNode(Node * n){

  n -> left = NULL;
  n -> right = NULL;
  n -> parent = NULL;
  
  free(n);
}

void removeLeaf(Tree * t, Node * n){
  if(n == t -> root){
    t -> root = NULL;
  }
  else if(n == n -> parent -> left){
    n -> parent -> left = NULL;
    n -> parent = NULL;
  }
  else{
    n -> parent -> right = NULL;
    n -> parent = NULL;
  }
  freeNode(n);
}


void shortCircuit(Tree * t, Node * n){
  if(n == t -> root){
    if(n -> left != NULL){
      t -> root = n -> left;
      freeNode(n);
    }
    else{
      t -> root = n -> right;
      freeNode(n);
    }
  }
  else if(n == n -> parent -> left){
    if(n -> left != NULL){
      n -> parent -> left = n -> left;
      n -> left -> parent = n -> parent;
    }
    else{
      n -> parent -> left = n -> right;
      n -> right -> parent = n -> parent;
    }
    freeNode(n);
  }
  else{
    if(n -> left != NULL){
      n -> parent -> right = n -> left;
      n -> left -> parent = n -> parent;
    }
    else{
      n -> parent -> right = n -> right;
      n -> right -> parent = n -> parent;
    }
    freeNode(n);
  } 
}

Node * searchRightMin( Node * n){
  n = n -> right ;
  while(n -> left != NULL){
    n = n -> left;
  }
  return n;
} 

void promotion(Tree * t, Node * n){
  Node * rightMin = searchRightMin(n);
  n -> data.value = rightMin -> data.value;
  if(rightMin -> left == NULL && rightMin -> right == NULL){
    removeLeaf(t,rightMin);
  }
  else 
    shortCircuit(t,rightMin);
}


void postOrderDeletion(Tree * tree, Node * n){
  if(n == NULL){
    return;
  }
  postOrderDeletion(tree,n -> left);
  postOrderDeletion(tree,n -> right);
  removeLeaf(tree,n);
}

void delete(Tree * tree){
  while(tree -> root != NULL){
    postOrderDeletion(tree,tree -> root);
  }
  free(tree -> root);
  free(tree);
}






void remove_Node(Tree * bst, Data value){
  Node * del = searchNode(bst,value);  
  if(del != NULL){
    
    if(del -> left == NULL && del -> right == NULL){
      removeLeaf(bst, del); 
    }
    else if(del -> left == NULL || del -> right == NULL){
      shortCircuit(bst, del);
    }else{
      promotion(bst, del);
    }    
  }
}






/*
  preoder(c -> root);
}


//REMOVE
Node * searchDel(Tree *t, Data d){
  if(t -> root == NULL)
      return NULL;
  Node * n = t -> root;
  if(d < n -> data){
    if(n->left == NULL)
        return NULL;
    else
        return searchNode(n -> left , d);
    }
  else if(d > n -> data){
    if(n -> right == NULL){
        return NULL;
    }
    else
      return searchNode(n -> right, d);
    }
  else
    return n;
  }
}

Node * findMaxLeft(Node * n){
	if(n->right ==NULL){
		return n;
	}
	else{
		return findMaxLeft(n->right);
	}
}

Node * findMinRight(Node * n){
	n=n->right;
	while(n->left!=NULL)
		n=n->left;
	return n;
}

void promotion(Node * n){
	Node * promote=findMaxLeft(n->left);
	n->data=promote->data;
	if(promote->left==NULL && promote->right==NULL){
		deleteLeaf(n);
	}
	else{
		shortCircuit(n);	
	}
}

void shortCircuit(Node *n){
	if(n->parent->left==n){	
		if(n->left!=NULL){
			parent->left = n->left;
			n->left->parent=n->parent;
			}
		else{
			parent->left = n->right;
			n->right->parent=n->parent;	
		}
	}
	else{
			
	}		

}

void deleteLeaf(Node *n){
	if(n->parent->left ==n){
		n->parent->left=NULL;	
	}
	else{
		n->parent->right=NULL;
	}
	free(n);
}

 
 
 
 
 
 
  
void remove_Node(Tree *t, Data d){
  Node * del = searchDel(t, d); 
  if(del != NULL){
    if(del -> left == NULL && del -> right == NULL){
        deleteLeaf(del);
    }
    else if(del -> left != NULL || del -> right == NULL)
        shortCircuit(n);
    else
        promotion(n);
    }
}
  
  
  
  
   
//DELETE
void delete(Tree *bst){
    
  
  
 */

  
 