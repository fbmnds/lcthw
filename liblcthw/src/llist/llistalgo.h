#ifndef LLISTALGOS_H
#define LLISTALGOS_H

#include "llist/llist.h"
#include "darray/darray.h"
#include "sort/sort.h"

#ifndef TYPE_DEFD
#define TYPE_DEFD
typedef int TYPE; /* generic value TYPE, defaults to int */
#endif
/*typedef TYPE *Index;*/

/*
  coerces List to an array of pointers to the List elements
  return NULL, if error
*/
DArray *create_index(List*);

/*
  returns the bubble-sorted array of List element pointers
  return NULL, if error
*/
DArray *bubble_sort_list(List *, cmp_func *);

/*
  returns the merge-sorted array of List element pointers
  return NULL, if error
*/
DArray *merge_sort_list(List *, cmp_func *);

#endif
