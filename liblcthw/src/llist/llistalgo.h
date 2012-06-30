#ifndef LIST_ALGOS_H
#define LIST_ALGOS_H

#include "llist.h"

typedef int TYPE; /* generic value TYPE, e.g. int */
typedef TYPE *Index;

/*
  coerces List to an array of pointers to the List elements
  return NULL, if error
*/
Index *create_index(List*);

typedef int (cmp_func)(void *, void *);
/*
 returns 1/0/-1 if arg1 </>= arg2/error
*/
cmp_func cmp_TYPE_lt;
/*
  returns the bubble-sorted array of List element pointers
  return NULL, if error
*/
Index *bubble_sort(List *, cmp_func *);
/*
  returns the merge-sorted array of List element pointers
  return NULL, if error
*/
Index *merge_sort(List *, cmp_func *);


#endif
