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

  v1 = **((TYPE **) vp1);
  v2 = **((TYPE **) vp2);
  if (v1 < v2)
    return 1;
  else
    return 0;
 error:
  return -1;
}

void ** bubble_sort(void **index, int count, cmp_func* cmp) 
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

/*
  return 0/1, if OK/error
 */
static int merge_queues(void **index, 
			 void **sortedindex, 
			 int count,
			 int idx1, int idx2,
			 cmp_func *cmp)
{
  int length = idx2 - idx1;
  int s1 = idx1 + length;
  int s2 = idx2 + length;
  int sortedidx = idx1;

  //printf("enter merge_queues\n");
  check(cmp, "compare function pointer is NULL");
  assert(length > 0);
  assert(s1 < s2);

  if (s2 > count) s2 = count;
  while (sortedidx < s2) {
    //printf("idx1= %d, s1 = %d, idx2 = %d, s2 = %d\n",idx1,s1,idx2,s2);
    //printf("sortedidx = %d\n", sortedidx);
    if ((idx1 < s1) && (idx2 < s2))
      if (cmp(index[idx1], index[idx2])) { 
    	sortedindex[sortedidx++] = index[idx1++];
    	continue;
      } else {
    	sortedindex[sortedidx++] = index[idx2++];
    	continue;
      }
    if (idx1 == s1) {
      while (sortedidx < s2)
	sortedindex[sortedidx++] = index[idx2++];
      break;
    }
    if (idx2 == s2) {
      while (sortedidx < s2)
	sortedindex[sortedidx++] = index[idx1++];
      break;
    }
  }
  //printf("leave merge_queues\n");
  return 0;
 error:
  return 1;
}

#define CASE_I   (idx2 + length < count)
#define CASE_II  ((idx2 >= count) && (idx1 >= count - length))
#define CASE_III ((idx2 + length >= count) && (idx2 < count))

void **merge_sort(void **index, int count, cmp_func* cmp)
{
  void **sortedindex = NULL;
  void **tmp;
  int idx1, idx2;
  int length;
  int swaps;

  check(count, "received negative element count");
  /* rely on valid index */
  if ((!count) || (count == 1)) return index;

  assert(sizeof(void*)==sizeof(void**));
  check_mem(sortedindex = (void**) calloc((size_t) count, sizeof(void*)));    
  /* init sortedindex */
  for (int i = 0; i < count; i++)
    sortedindex[i] = index[i];
  
  idx1 = 0;
  length = 1;
  swaps = 0;
  while (length < count) {
    /* swap between sortedindex and index for memory efficiency */
    swaps++;
    tmp = index;
    index = sortedindex;
    sortedindex = tmp;

    while (idx1 < count) {
  	idx2 = idx1 + length;
  	if (CASE_I) {
	  //printf("CASE I\n");
	  check((!merge_queues(index, sortedindex, count, idx1, idx2, cmp)), "merge_queues() failed"); 
	  goto next;
	}
  	if (CASE_II) {
	  //printf("CASE II\n");
	  assert((idx1 - length) >= 0);
	  if (length) break;
	  check((!merge_queues(index, sortedindex, count, idx1 - length, idx1, cmp)), "merge_queues() failed"); 
	  break;
	}
  	if (CASE_III) {
	  //printf("CASE III\n");
	  //assert((idx1 - length) >= 0);
	  check((!merge_queues(index, sortedindex, count, idx1, idx2, cmp)), "merge_queues() failed"); 
	  break;
	}
	assert(0 && "disjunct & complete cases");
    next:
	//printf("idx1 after 1 = %d\n\n",idx1);
  	idx1 += 2*length;
	//NL;
	//for (int i = 0; i < count; i++)
	//  printf("index = %d, sortedindex = %d\n",*(int*)index[i],*(int*)sortedindex[i]);
    }
    //printf("idx1 after 2 = %d\n",idx1);
    idx1 = 0;
    length *= 2;
    //for (int i = 0; i < count; i++)
    //   printf("index = %d, sortedindex = %d\n",*(int*)index[i],*(int*)sortedindex[i]);

  }
  //NL;	for (int i = 0; i < count; i++)
  //  printf("index = %d, sortedindex = %d\n",*(int*)index[i],*(int*)sortedindex[i]);
  
  if (count%4 == 2 && count > 4) {
    /* clean up last 4 elements */
    idx1 = count - 4;
    idx2 = count - 2;
    check((!merge_queues(sortedindex, index, count, idx1, idx2, cmp)), "merge_queues() failed");
  }

  /* swap back, if necessary, i.e. odd number of swaps */
  if (swaps%2 == 1) {
    tmp = index;
    index = sortedindex;
    sortedindex = tmp;
    for (int i = 0; i < count; i++)
      sortedindex[i] = index[i];
  }

  return sortedindex;
 error:
  cfree(sortedindex);
  return NULL;
}

 	    /*
count%4 == 0: gerade Anzahl von 2-Tupeln; keine Sonderbehandlung
count%4 == 2: ungerade Anzahl von 2-Tupeln; die letzen 6 Elemente sortieren
count%4 == 3: ungerade Anzahl von 2-Tupeln + 1 separates Element; die letzten 3 Elemente sortieren
count%4 == 1: gerade Anzahl von 2-Tupeln + 1 separates Element; die letzen 5 Elemente sortieren
*/

	    /*
Fallunterscheidung:
idx2 < count && idx2 + length < count: normaler symetrischer Fall
idx2 < count && idx2 + length >= count:
   der überstehende Rest wird in das vorhergehende letzte Segment mit voller Länge count hineingemergt.
idx1 < count && idx2 = idx1 + length >= count:
   die beiden letzten, unterschiedlich langen Segmente werden gemergt
*/
  /*
  if (!((idx1 < count) && (idx2 < count) && (sortedidx < count)))
    assert(((idx1 == s1) || (idx1 == count)) && 
	   ((idx2 == s2) || (idx2 == count)) &&
	   ((sortedidx == s2) || (sortedidx == count)));
  assert(idx1 <= count);
  assert(idx2 <= count);
  assert(sortedidx <= count);
  */

