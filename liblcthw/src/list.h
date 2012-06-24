#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
  struct ListNode *prev;
  struct ListNode *next;
  void * value;
} ListNode;

#define DTOR(P) cfree(P)
 
/*
  provide destructor for compound value types: 

extern void (*dtor) (valuetype *); 
#define DTOR(P) dtor(P)
*/

typedef struct List {
  int count;
  ListNode *first;
  ListNode *last;
} List;

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
