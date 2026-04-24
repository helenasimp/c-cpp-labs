#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

Node *empty = NULL;

Node *node(int value, Node *left, Node *right) { 
  Node *r = malloc(sizeof(Node));
  r->marked = false;
  r->value = value;
  r->left = left;
  r->right = right;
  return r;
}


/* Basic Problems */

int size(Node *node) { 
  if (node == NULL) return 0;
   if(!node->marked)
   {
    node->marked = true;
    int leftsize = size(node->left);
    int rightsize = size(node->right);
    return 1 + leftsize + rightsize;
   }
   return 0;
}


void unmark(Node *node) { 
  if (node == NULL) return;
  if(node->marked)
  {
    node->marked = false;
    unmark(node->left);
    unmark(node->right);
    
  }
  
}

bool path_from(Node *node1, Node *node2) {
  if((node1==NULL) || (node2==NULL)) return false;
  unmark(node1);
  unmark(node2);
  int _ = size(node1);
  if(node2->marked) return true;
  return false;
}

bool cyclic(Node *node) { 
  if(node==NULL) return false;
  return (path_from(node->left,node) || path_from(node->right,node));
} 


/* Challenge problems */

void get_nodes(Node *node, Node **dest) { 
  /* TODO */
}

void graph_free(Node *node) { 
  /* TODO */
}


