#include "llistalgo.h"
#include "misc/misc.h"
#include "misc/dbg.h"

#include <stdlib.h>
#include <assert.h>

DArray *create_index(List* list)
{
  DArray *listindex;
  size_t idx;

  if (!list) sentinel("received nullpointer to list");
  check(list->count, "reveived empty list");

  check_mem((listindex = DArray_create(sizeof(TYPE *), list->count)));
  
  idx = 0;
  LIST_FOREACH(list, first, next, iter)
    DArray_set(listindex, idx++, (TYPE *) iter->value);
  assert(idx == list->count);
  assert(list->count == listindex->count);

  INV_DARRAY(listindex);

  return listindex;
 error:
  /* rely on cfree() in DArray_create() */ 
  return NULL;
}

DArray *bubble_sort_list(List *list, cmp_func *cmp)
{
  DArray *listindex;
  /* TYPE *tmp; */

  check(cmp, "compare function pointer is NULL");
  check(list, "received list nullpointer");
  
  switch (list->count) {
  case 0:
    INV_COUNT_0(list);
    return NULL;
  case 1:
    INV_COUNT_1(list);
    return create_index(list);
  default:
    INV_COUNT_GT_1(list);
    check((listindex = create_index(list)), "create index failed");
    INV_DARRAY(listindex);

    check(listindex->contents = 
	  bubble_sort(listindex->contents, list->count, cmp),
	  "bubble sort failed");
    INV_DARRAY(listindex);

    return listindex;
  }

 error:
  return NULL;
}

DArray *merge_sort_list(List *list, cmp_func *cmp)
{
  DArray *listindex;
  DArray *sortedlistindex = NULL;

  check(cmp, "compare function pointer is NULL");
  check(list, "received list nullpointer");
  assert(list->count >= 0);
  
  switch (list->count) {
  case 0:
    INV_COUNT_0(list);
    return NULL;
  case 1:
    INV_COUNT_1(list);
    return create_index(list);
  default:
    INV_COUNT_GT_1(list);
    check((listindex = create_index(list)), "create index failed");
    INV_DARRAY(listindex);

    sortedlistindex = calloc(1, sizeof(struct DArray));
    sortedlistindex->count = listindex->count;
    sortedlistindex->max = listindex->max;
    sortedlistindex->element_size = listindex->element_size;
    sortedlistindex->expand_rate = listindex->expand_rate;
    /* sortedlistindex->contents == NULL */

    sortedlistindex->contents = 
      merge_sort(listindex->contents, list->count, cmp);
    sortedlistindex->count = listindex->count;

    DArray_destroy(&listindex);

    return sortedlistindex;
  }

 error:
  return NULL;
}
