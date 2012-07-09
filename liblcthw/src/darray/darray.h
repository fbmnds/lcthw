#ifndef _DArray_h 
#define _DArray_h 

#include <stdlib.h>
#include <assert.h>

#include "misc/misc.h"
#include "misc/dbg.h"

typedef struct DArray { 
  int end;              /* index + 1 of last element of darray */
  int max;              /* max number of elements, always > 0 */
  size_t element_size;  /* size of a content element */
  size_t expand_rate;
  void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

int DArray_destroy(DArray **array); 

void DArray_clear(DArray *array);

int DArray_expand(DArray **array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)       /* index + 1 of last element of darray */
#define DArray_count(A) DArray_end(A)  /* index + 1 = number of elements */
#define DArray_max(A) ((A)->max)       /* max number of elements */
#define DEFAULT_EXPAND_RATE 64
#define MAX_EXPAND_RATE 60000

inline static int DArray_set(DArray *array, int i, void *el)
{
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  assert((array->max && (array->max >= array->end)) && 
	 "inconsistent array capacity");
  
  /* allow darray to grow within capacity */
  check((i > -1 && i < array->max), "out-of-bound index for darray");
  if (i >= array->end) array->end = i + 1;

  if (!el) log_warn("received null pointer as content");
  array->contents[i] = el; /* dangerous, darray content not encapsulated */

  return 0;
 error:
  return 1; 
}

inline static void *DArray_get(DArray *array, int i)
{
  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content");
  assert((array->max && (array->max >= array->end)) && 
	 "inconsistent array capacity");
  check((i > -1 && i < array->end), "out-of-bound index for darray");

  return array->contents[i]; /* might be NULL */
error:
  return NULL; 
}

static inline void *DArray_remove(DArray *array, int i)
{
  void *el;

  check(array, "received null pointer to darray");
  check(array->contents, "received null pointer to darray content"); 
  assert((array->max && (array->max >= array->end)) && 
	 "inconsistent array capacity");
  check((i > -1 && i < array->end), "out-of-bound index for darray");

  if (!array->end) return NULL;  /* empty darray */

  el = array->contents[i];  /* might be NULL */
  array->contents[i] = NULL;

  if (i == array->end - 1) array->end--;

  return el;
 error: 
  return NULL; 
}

static inline void *DArray_new(DArray *array)
{
  check(array->element_size > 0, "received nonpositive size for darray.");
  
  return calloc(1, array->element_size);
error:
  return NULL;
}

#define DArray_free(E) cfree((E))

#endif
