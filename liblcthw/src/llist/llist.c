#include <assert.h>
#include <stdlib.h>

#include "llist.h"
#include "misc/misc.h"
#include "misc/dbg.h"
 
List * List_create(void)
{
  return calloc(1, sizeof(List));
}

int List_destroy(List **lst)
{
  List *list = *lst;
 
  if (list == NULL) return 0;

  switch (list->count) {
  case 0:
    INV_COUNT_0(list);
    cfree(list);
    break;
  case 1:
    INV_COUNT_1(list);
    DTOR(list->first->value);
    cfree(list->first);
    cfree(list);    
    break;
  default:
    INV_COUNT_GT_1(list);
    LIST_FOREACH (list, first, next, iter) {
      list->count--;
      DTOR(iter->value);
      assert((iter->value == NULL));
      if (iter != list->first) cfree(iter->prev);
    }
    DTOR(list->last->value);
    cfree(list->last);
    cfree(list);
  }


  *lst = NULL;

  return 0;
}

int List_clear(List *list)
{
  if (!list) return 0;

  assert(list->count >= 0);
  if (!list->count) {
    cfree(list);
    return 0;
  }

  LIST_FOREACH (list, first, next, iter) {
    list->count--;
    DTOR(iter->value);
    cfree(iter->prev);
  }
  cfree(iter);

  assert(list);
  /* assert(!list->first); */
  /* assert(!list->last); */
  debug("list->count = %d\n", list->count);
  assert(list->count == 0);

  return 0;
}

int List_push(List **lst, void *value)
{
  List *list;
  ListNode *buf = calloc(1, sizeof(ListNode));
  check(buf, "failed to create a new node"); 

  if (!(*lst)) *lst = List_create();
  list = *lst;

  if (list->count == 0) INV_COUNT_0(list);
  if (list->count == 1) INV_COUNT_1(list);
  if (list->count > 1) INV_COUNT_GT_1(list);

  if(!value) log_warn("received empty value");

  buf->value = malloc(strlen(value) + 1);
  buf->value = strcpy(buf->value, value);

  buf->next = list->first;
  assert(buf->prev == NULL);

  list->first = buf;

  list->count++;
  assert(list->count > 0);

  if (list->count == 1) {
    list->last = list->first;
    INV_COUNT_1(list);
  }
  if (list->count > 1) {
    list->first->next->prev = list->first;
    INV_COUNT_GT_1(list);
  }

  return 0;
 error:
  return 1;
}

void *List_pop(List *list)
{
  ListNode *rv;
  void *value;

  if (!list || !list->count) return NULL;

  assert(list->count > 0);
  if (list->count == 1) INV_COUNT_1(list);
  if (list->count > 1) INV_COUNT_GT_1(list);

  list->count--;
  rv = list->first;
  list->first = rv->next;

  value = malloc(strlen(rv->value) + 1);
  value = strcpy(value, rv->value);
  DTOR(rv->value);
  cfree(rv);

  if (list->count == 0) {
    list->first = NULL;
    list->last = NULL;
    INV_COUNT_0(list);
  }
  if (list->count == 1) {
    list->first->prev = NULL;
    list->first->next = NULL;
    list->last = list->first;
    INV_COUNT_1(list);
  }
  if (list->count > 1) {
    list->first->prev = NULL;
    list->last->next = NULL;
    INV_COUNT_GT_1(list);
  }

  return value;
}

int List_shift(List *list, void *value)
{
  if (list) {}
  if (value) {}
  return 0;
}

void *List_unshift(List *list)
{
  if (list) {}
  return NULL;
}

int List_remove(List* list, ListNode *node)
{
  if (list) {}
  if (node) {}
  return 0;
}

