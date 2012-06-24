#include <assert.h>
#include <stdlib.h>
#include "list.h"
#include "dbg.h"
 
#define cfree(p) if ((p) != NULL) { free((p)); (p) = NULL; }

List * List_create(void)
{
  return calloc(1, sizeof(List));
}

int List_destroy(List *list)
{
  if (list == NULL) return 0;

  if (list->count == 0) {
    assert((!(list->first)));
    assert((!(list->last)));
    cfree(list);
    return 0;
  }

  assert((list->count > 0));
  assert(list->first);
  assert(list->last);

  if (list->count == 1) {
    assert((list->first == list->last));
    DTOR(list->first->value);
    cfree(list->first);
    cfree(list);
  }

  assert((list->first != list->last));

  LIST_FOREACH (list, first, next, iter) {
    list->count--;
    DTOR(iter->value);
    assert((iter->value == NULL));
    if (iter != list->first) cfree(iter->prev);
  }
  DTOR(list->last->value);
  cfree(list->last);
  /* assert(!list->first); */
  /* assert(!list->last); */
  debug("list->count = %d\n", list->count);
  assert(list->count == 0);

  cfree(list);
  assert(list == NULL);

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

#define List_count(L) ((L)->count)
#define List_first(L) ((L)->first)
#define List_last(L) ((L)->last)

int List_push(List *list, void *value)
{
  ListNode *buf = calloc(1, sizeof(ListNode));
  check(buf, "failed to create a new node"); 

  if (!list) {
    printf("### create in push\n");
    list = List_create();
  }

  if(!value) log_warn("received empty value");

  buf->value = malloc(strlen(value) + 1);
  buf->value = strcpy(buf->value, value);
  //printf("buf->value = %s, value = %s\n", buf->value, value);
  
  buf->next = list->first;
  assert(buf->prev == NULL);

  list->first = buf;
  list->count++;
  if (list->count == 1) list->last = list->first;
  if (list->count > 1) list->first->next->prev = list->first;

  assert(list->first);
  assert(list->last);
  assert(list->count > 0);
  if (list->count == 1) {
    assert(list->first == list->last);
    assert(list->first->prev == NULL);
    assert(list->first->next == NULL);
  }
  if (list->count > 1) {
    assert(list->first != list->last);
    assert(list->first->prev == NULL);
    assert(list->first->next != NULL);
    assert(list->last->prev != NULL);
    assert(list->last->next == NULL);
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
  if (list->count == 1) {
    assert(list->first == list->last);
    assert(list->first->prev == NULL);
    assert(list->first->next == NULL);
  }
  if (list->count > 1) {
    assert((list->first != list->last));
    assert(list->first->prev == NULL);
    assert(list->first->next != NULL);
    assert(list->last->prev != NULL);
    assert(list->last->next == NULL);
  }

  list->count--;
  rv = list->first;
  list->first = rv->next;

  //  if (list->count < 2)
  //    assert(list->first == list->last);

  value = malloc(strlen(rv->value) + 1);
  value = strcpy(value, rv->value);
  DTOR(rv->value);
  cfree(rv);
  if (list->count == 0) {
    list->first = NULL;
    list->last = NULL;
  }
  if (list->count == 1) {
    list->first->prev = NULL;
    list->first->next = NULL;
    list->last = list->first;
  }
  if (list->count > 1) {
    list->first->prev = NULL;
    list->last->next = NULL;
  }

  if (list->count == 0) {
    assert(list->first == NULL);
    assert(list->last == NULL);
  }
  if (list->count == 1) {
    assert(list->first);
    assert(list->first == list->last);
    assert(list->first->prev == NULL);
    assert(list->first->next == NULL);
  }
  if (list->count > 1) {
    assert(list->first);
    assert(list->last);
    assert(list->first != list->last);
    assert(list->first->prev == NULL);
    assert(list->first->next != NULL);
    assert(list->last->prev != NULL);
    assert(list->last->next == NULL);
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

