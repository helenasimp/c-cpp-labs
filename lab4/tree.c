#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Tree *empty = NULL;

/* BASE EXERCISE */

int tree_member(int x, Tree *tree) { 
  if (tree==NULL) return 0;
  if(x==tree->value) return 1;
  if (x>tree->value) return tree_member(x,tree->right);
  return tree_member(x,tree->left);
  
}

Tree *tree_insert(int x, Tree *tree) { 
  if(tree==NULL) 
  {
    Tree *newTree = malloc(sizeof(Tree));
    newTree->value = x;
    return newTree;
  }
  if(x==tree->value) return tree;
  else if (x>tree->value)
  {
    tree->right = tree_insert(x,tree->right);
    return tree;
  }
  else{
    tree->left = tree_insert(x,tree->left);
    return tree;
  }
}

void tree_free(Tree *tree) { 
  if (tree !=NULL)
  {
    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
  }
 
}

/* CHALLENGE EXERCISE */ 

void pop_minimum(Tree *tree, int *min, Tree **new_tree) { 

  if(tree->left == NULL)
  {
    *min = tree->value;
     *new_tree = tree->right;
    free(tree);
    return;
  }
  if(tree->left != NULL) 
  { 
    pop_minimum(tree->left, min, new_tree);
    tree->left = *new_tree;
    return;
  }

}

Tree *tree_remove(int x, Tree *tree) 
{ 
  if(tree==NULL)
  {
    return tree;
  }
  if (tree->value == x)
  {
    if((tree->right==NULL) && (tree->left==NULL))
    {
      free(tree);
      return NULL;
    }
    if(tree->right == NULL)
    {
      tree->value = tree->left->value;
      tree->left = tree->left->left;
      tree->right = tree->left->right;
      return tree;
    }
    if(tree->left == NULL)
    {
      tree->value = tree->right->value;
      tree->left = tree->right->left;
      tree->right = tree->right->right;
      return tree;
    }

    int minvalue = 0;
    Tree **new_tree = &tree->right;
    pop_minimum(tree->right,&minvalue, new_tree);
    tree->value = minvalue;
    return tree;

  }
  else if(x>tree->value)
  {
    tree->right = tree_remove(x,tree->right);
    return tree;
  } 
  else
  {
    tree->left = tree_remove(x,tree->left);
    return tree;
  }
}

void print_tree(Tree *tree)
{
  if(tree->left !=NULL)
  {
    if (tree->right !=NULL)
    {
      printf("%d left: %d right: %d\n",tree->value,tree->left->value,tree->right->value);
      print_tree(tree->left);
      print_tree(tree->right);
    }
    else
    {
      printf("%d left: %d right: NULL\n",tree->value,tree->left->value);
      print_tree(tree->left);
    }
  }
  else if (tree->right !=NULL)
  {
    printf("%d left: NULL right: %d\n",tree->value,tree->right->value);
    print_tree(tree->right);
  }
  else
  {
    printf("%d left: NULL right: NULL\n",tree->value);
  }
}
