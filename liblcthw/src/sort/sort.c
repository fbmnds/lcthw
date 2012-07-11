#include "sort/sort.h"

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

void * bubble_sort(void **index, int count, cmp_func* cmp) 
{
  void **tmp;

  for (int i = 0; i < count; i++)
    for (int j = 0; j < count - 1; j++) {
      log_info("Index[i = %d] = %c, Index[j = %d] = %c", 
	     i, *((char*)(index[i])), 
	     j, *((char*)(index[j])));
      if (cmp(index[i],index[j])) {
	log_info("--  switch i = %d, j = %d", i, j);
	tmp = index[i];
	index[i] = index[j];
 	index[j] = tmp;
      }
    }
  return index;
}


