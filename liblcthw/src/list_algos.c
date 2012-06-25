#include "list_algos.h"
#include "dbg.h"

#include <stdlib.h>

Index *create_index(List* list)
{
  Index *listindex;
  Index *idx;

  if (!list) sentinel("received nullpointer to list");
  if (list->count < 0) sentinel("reveived invalid list count < 0");
  if (!list->count) sentinel("reveived empty list");
  
  check_mem(listindex = calloc(list->count, sizeof(Index)));
  
  if (list->count == 1)
    *listindex = (TYPE *)list->first->value;
  else { /* list->count > 1 */
    idx = listindex;
    LIST_FOREACH(list, first, next, iter)// {
      //printf("create_index %c  ", *((char*)iter->value));
      *idx++ = (TYPE *) iter->value;
      //printf(" idx = %c\n",*((char*)*idx));
      //idx++;
      //}
  }

  return listindex;
 error:
  return NULL;
}

int cmp_TYPE_gt(void *vp1, void *vp2)
{
  int v1, v2;

  if (!vp1) sentinel("received nullpointer to value 1");
  if (!vp2) sentinel("received nullpointer to value 2");

  v1 = *((int*) vp1);
  v2 = *((int*) vp2);
  if (v1 > v2)
    return 1;
  else
    return 0;
 error:
  return -1;
}

Index *bubble_sort(Index listindex, cmp_func *cmp)
{
  if (listindex) {}
  if (cmp) {}

  return NULL;
}

Index *merge_sort(Index listindex, cmp_func *cmp)
{
  if (listindex) {}
  if (cmp) {}

  return NULL;
}
