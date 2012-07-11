#include "sort/sort.h"
#include "misc/misc.h"

#include <stdlib.h>
#include <assert.h>

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

int cmp_pt_TYPE_lt(void **vp1, void **vp2)
{
  int v1, v2;

  if (!vp1) sentinel("received nullpointer to value 1");
  if (!vp2) sentinel("received nullpointer to value 2");

  v1 = *((TYPE **) vp1);
  v2 = *((TYPE **) vp2);
  if (v1 < v2)
    return 1;
  else
    return 0;
 error:
  return -1;
}

void * bubble_sort(void **index, int count, cmp_func* cmp) 
{
  void **tmp;

  for (int i = 0; i < count; i++)
    for (int j = 0; j < count - 1; j++) {
      /*      log_info("Index[i = %d] = %c, Index[j = %d] = %c", 
	     i, *((char*)(index[i])), 
	     j, *((char*)(index[j])));*/
      if (cmp(index[i],index[j])) {
	/*log_info("--  switch i = %d, j = %d", i, j);*/
	tmp = index[i];
	index[i] = index[j];
 	index[j] = tmp;
      }
    }
  return index;
}

static void merge_queues(void **index, 
			 void **sortedindex, 
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
	  sortedindex[sortedidx++] = index[idx1++];
	break;
      }
      if (cmp(index[idx1],index[idx2])) 
	sortedindex[sortedidx++] = index[idx1++];
      else
	sortedindex[sortedidx++] = index[idx2++];
    }
    if (idx1 == s1) {
      if ((sortedidx < count) && (idx2 < count))
	sortedindex[sortedidx++] = index[idx2++];
    }
    if (idx2 == s2) {
      if ((sortedidx < count) && (idx1 < count))
	sortedindex[sortedidx++] = index[idx1++];
    }
  }

  if (!((idx1 < count) && (idx2 < count) && (sortedidx < count)))
    assert(((idx1 == s1) || (idx1 == count)) && 
	   ((idx2 == s2) || (idx2 == count)) &&
	   ((sortedidx == s2) || (sortedidx == count)));
  assert(idx1 <= count);
  assert(idx2 <= count);
  assert(sortedidx <= count);
  
 error: /* fallthrough */
  return;
}

void *merge_sort(void **index, int count, cmp_func* cmp)
{
  void **tmp;
  int idx1, idx2;
  int length;
  
  void **sortedindex = NULL;
  check_mem(sortedindex = calloc(count, sizeof(void*)));    

  /* init sortedindex */
  for (int i = 0; i < count; i++)
  	sortedindex[i] = index[i];

  idx1 = 0;
  length = 1;
  while (length < count) {
    /* swap between sortedindex and index for memory efficiency */
    tmp = index;
    index = sortedindex;
    sortedindex = tmp;
    while (idx1 < count) {
  	idx2 = idx1 + length;
  	if (idx2 > count) break;
  	merge_queues(index, sortedindex, count, idx1, idx2, cmp);
  	idx1 += 2*length;
    }
    idx1 = 0;
    length *= 2;
  }
  
  return sortedindex;
 error:
  cfree(sortedindex);
  return NULL;
}

