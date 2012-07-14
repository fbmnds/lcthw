#ifndef SORT_H
#define SORT_H

#include "misc/dbg.h"

#ifndef TYPE_DEFD
#define TYPE_DEFD
typedef int TYPE; /* generic value TYPE, defaults to int */
#endif

typedef int (cmp_func)(void *, void *);
/*
 generic comparision for every TYPE that supports '<'
 returns 1/0/-1 if arg1 </>= arg2/error
*/
cmp_func cmp_TYPE_lt;

typedef int (cmp_pt_func)(void **, void **);
/*
 generic comparision for every TYPE that supports '<'
 returns 1/0/-1 if arg1 </>= arg2/error
*/
cmp_pt_func cmp_pt_TYPE_lt;

void ** bubble_sort(void** index, int count, cmp_func* cmp);

void ** merge_sort(void** index, int count, cmp_func* cmp);

#endif
