#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *cons(int head, List *tail) { 
  /* malloc() will be explained in the next lecture! */
  List *cell = malloc(sizeof(List));
  cell->head = head;
  cell->tail = tail;
  return cell;
}

/* Functions for you to implement */

int sum(List *list) {
  /* TODO */
  if (list->tail != NULL) return list->head + sum(list->tail);
  else return list->head;
  
}

void iterate(int (*f)(int), List *list) {
  /* TODO */
  list->head = f(list->head);
  if(list->tail != NULL) iterate(f, list->tail);
}

void print_list(List *list) { 
  if(list->tail != NULL)
  {
    printf("%d, ", list->head);
    print_list(list->tail);
  }
  else printf("%d\n", list->head);
}

/**** CHALLENGE PROBLEMS ****/

List *merge(List *list1, List *list2) { 
  /* TODO */
  if(list1->tail == NULL) return list2;
  else if(list2->tail == NULL) return list1;
  else
  {
    if (list1->head > list2->head)
    {
      list1->tail = merge(list1->tail,list2);
      return list1;
    } 
    else
    {
      list2->tail = merge(list1,list2->tail);
      return list2;
    }
  } 
}

void split(List *list, List **list1, List **list2) { 
  /* TODO */
  list1 = &list;
  list2 = &(list->tail);
  
  List *l2pointer = list->tail;
  while(list->tail->tail->tail != NULL)
  {
    list->tail = list->tail->tail;
    l2pointer->tail = list->tail->tail;

    list = list->tail;
    l2pointer = l2pointer->tail;

  }

}

/* You get the mergesort implementation for free. But it won't
   work unless you implement merge() and split() first! */

List *mergesort(List *list) { 
  if (list == NULL || list->tail == NULL) { 
    return list;
  } else { 
    List *list1;
    List *list2;
    split(list, &list1, &list2);
    list1 = mergesort(list1);
    list2 = mergesort(list2);
    return merge(list1, list2);
  }
}
