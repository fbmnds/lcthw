#include "llistalgo.h"
#include "misc/misc.h"
#include "misc/dbg.h"

#include <stdlib.h>
#include <assert.h>

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
    LIST_FOREACH(list, first, next, iter)
      *idx++ = (TYPE *) iter->value;
  }

  return listindex;
 error:
  return NULL;
}

int cmp_TYPE_lt(void *vp1, void *vp2)
{
  int v1, v2;

  if (!vp1) sentinel("received nullpointer to value 1");
  if (!vp2) sentinel("received nullpointer to value 2");

  v1 = *((TYPE *) vp1);
  v2 = *((TYPE *) vp2);
  if (v1 < v2)
    return 1;
  else
    return 0;
 error:
  return -1;
}

Index *bubble_sort(List *list, cmp_func *cmp)
{
  Index *listindex;
  TYPE *tmp;

  check(cmp, "compare function pointer is NULL");
  check(list, "received list nullpointer");
  check(cmp, "received function nullpointer");
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
    
    for (int i = 0; i < list->count; i++)
      for (int j = 0; j < list->count - 1; j++) {
	if (cmp(listindex[i],listindex[j])) {
	    tmp = listindex[i];
	    listindex[i] = listindex[j];
	    listindex[j] = tmp;
	  }
      }
    return listindex;
  }

 error:
  return NULL;
}


static void merge_queues(Index *listindex, 
			 Index **sortedlistindex, 
			 int count,
			 int idx1, int idx2,
			 cmp_func *cmp)
{
  int length = idx2 - idx1;
  int s1 = idx1 + length;
  int s2 = idx2 + length;
  int sortedidx = idx1;

  check(cmp, "compare function pointer is NULL");
  assert(length > 0);
  assert(s1 < s2);

  while ((sortedidx <= s2) && (sortedidx < count)) {
    if ((idx1 < s1) && (idx2 < s2)) {
      if (idx1 == count) break;
      if (idx2 == count) {
	for (; ((idx1 < count) && (sortedidx < count)); )
	  (*sortedlistindex)[sortedidx++] = listindex[idx1++];
	break;
      }
      if (cmp(listindex[idx1],listindex[idx2])) 
	(*sortedlistindex)[sortedidx++] = listindex[idx1++];
      else
	(*sortedlistindex)[sortedidx++] = listindex[idx2++];
    }
    if (idx1 == s1) {
      if ((sortedidx < count) && (idx2 < count))
	(*sortedlistindex)[sortedidx++] = listindex[idx2++];
    }
    if (idx2 == s2) {
      if ((sortedidx < count) && (idx1 < count))
	(*sortedlistindex)[sortedidx++] = listindex[idx1++];
    }
  }

  if (!((idx1 < count) && (idx2 < count) && (sortedidx < count)))
    assert(((idx1 == s1) || (idx1 == count)) && 
	   ((idx2 == s2) || (idx2 == count)) &&
	   ((sortedidx == s2) || (sortedidx == count)));
  assert(idx1 <= count);
  assert(idx2 <= count);
  assert(sortedidx <= count);

 error:
  return;
}

Index *merge_sort(List *list, cmp_func *cmp)
{
  Index *listindex;
  Index *sortedlistindex;
  Index *tmp;
  int idx1, idx2;
  int length;

  check(cmp, "compare function pointer is NULL");
  check(list, "received list nullpointer");
  check(cmp, "received function nullpointer");
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
    check_mem(sortedlistindex = calloc(list->count, sizeof(Index)));    

    /* init sortedlistindex */
    for (int i = 0; i < list->count; i++)
    	sortedlistindex[i] = listindex[i];

    idx1 = 0;
    length = 1;
    while (length < list->count) {
      /* swap between sortedlistindex and listindex for memory efficiency */
      tmp = listindex;
      listindex = sortedlistindex;
      sortedlistindex = tmp;
      while (idx1 < list->count) {
	idx2 = idx1 + length;
	if (idx2 > list->count) break;
	merge_queues(listindex, &sortedlistindex, list->count, idx1, idx2, cmp);
	idx1 += 2*length;
      }
      idx1 = 0;
      length *= 2;
    }

    cfree(listindex);
    return sortedlistindex;
  }

 error:
  return NULL;
}
