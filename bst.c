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
 // t -> compare = compare;
  //t -> clone = clone;
 // t -> delete = delete;
  //t -> removeData = &remove;
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
Node * searchNode(Node * n, Data d){
	if(d.value < n -> data.value){
		if(n -> left == NULL)
			return NULL;
		else
			return searchNode(n -> left, d);
	}
	else if(d.value > n -> data.value){
		if(n -> right == NULL)
			return NULL;
		else
			return searchNode(n -> right, d);
   }
	
  return n;
}

Data * search(Tree *t, Data d){
   Node * check = NULL;

   if( t -> root == NULL)
       return NULL;
   else
       check = searchNode( t -> root, d);
   if(check == NULL)
       return NULL;
}

//SORTING
Data inorder(Node * n){
  if(n -> left != NULL)
    inorder(n -> left);
    return n -> data;
  if(n -> right != NULL)
    inorder(n -> right);
  
} 
  

void sort(Tree *t, Data * d){
   Node * n = t -> root;
   * d = inorder(n);
     }

   
  
  
 

  
 