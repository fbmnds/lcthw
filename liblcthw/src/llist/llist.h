#ifndef LIST_H
#define LIST_H

#ifdef DTOR 
/*
  if user provides destructor for compound value types: 
*/
extern void (dtor_for_valuetype) (void *); 
/*
  then user provides this makro:
#define DTOR(P) dtor_for_valuetype(P)
*/
#else
#define DTOR(P) cfree(P)
#endif

typedef struct ListNode {
  struct ListNode *prev;
  struct ListNode *next;
  void * value;
} ListNode;

typedef struct List {
  int count;
  ListNode *first;
  ListNode *last;
} List;

#define INV_COUNT_0(list) { assert((list)->count == 0);\
    assert((list)->first == NULL);\
    assert((list)->last == NULL);\
} 
 
#define INV_COUNT_1(list) { assert((list)->count == 1);\
    assert((list)->first);\
    assert((list)->first == (list)->last);\
    assert((list)->first->prev == NULL);\
    assert((list)->first->next == NULL);\
}

#define INV_COUNT_GT_1(list) { assert((list)->count > 1);\
    assert((list)->first);\
    assert((list)->last);\
    assert((list)->first != (list)->last);\
    assert((list)->first->prev == NULL);\
    assert((list)->first->next != NULL);\
    assert((list)->last->prev != NULL);\
    assert((list)->last->next == NULL);\
}

List * List_create(void);
/*
  return 0/1, if ok/error
*/
int List_destroy(List **list);
/*
  return 0/1, if ok/error
*/
int List_clear(List *list);

#define List_count(L) ((L)->count)
#define List_first(L) ((L)->first)
#define List_last(L)  ((L)->last)

/*
  return 0/1, if ok/error
*/
int List_push(List **list, void *value);
void *List_pop(List *list);

/*
  return 0/1, if ok/error
*/
int List_shift(List *list, void *value);
void *List_unshift(List *list);

/*
  return 0/1, if ok/error
*/
int List_remove(List* list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
