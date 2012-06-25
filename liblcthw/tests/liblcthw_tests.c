#include "list.h"
#include "list_algos.h"

#include "dbg.h"
#include "minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

#define cfree(p) if ((p) != NULL) { free((p)); (p) = NULL; }
#define NL printf("\n")

static List *list;
static char *values[] = { "ONE", "TWO", "THREE", "FOUR", "FIVE", NULL };
static Index * listindex;

void *test_list_create()
{
  printf("test_list_create()\n");
  printf("------------------\n");

  list = List_create();

  check((list), "List_create returned NULL");
  check(!(list->first), "list->first invalid");
  check(!(list->last), "list->last invalid");
  check(!list->count, "list->count invalid");

  printf("(done.)\n");
  return NULL;
 error:
  return "List_create failed";
}

void *test_list_destroy()
{
  int rc;
  printf("test_list_destroy()\n");
  printf("-------------------\n");
  
  rc = List_destroy(&list);
  check(!rc, "List_destroy return code = %d", rc);

  printf("(done.)\n");
  return NULL;
 error:
  return "List_destroy failed";
}

void *test_list_clear()
{
  int rc;

  printf("test_list_clear()\n");
  printf("-----------------\n");

  rc = List_clear(list);
  check(!rc, "List_clear return code = %d", rc);

  printf("(done.)\n");
  return NULL;
 error:
  return "List_clear failed";
}

void *test_list_push()
{
  char **vp = values;

  printf("test_list_push()\n");
  printf("----------------\n");

  while (*vp) {
    check((!(List_push(&list, (void *) *vp))), "List_push failed on %s", *vp);
    vp++;
  }

  LIST_FOREACH(list, first, next, iter) {
    printf("after push %s \n", iter->value);
    //    check((!strcmp(iter->value, *(--vp))), "strcmp failed");
  }
  NL;

  printf("(done.)\n");
  return NULL;
 error:
  return "List_push failed";
}

void *test_list_pop()
{
  void *value;

  printf("test_list_pop()\n");
  printf("---------------\n");

  value = List_pop(list);
  //  check((!strcmp((char *) value, "FIVE")), "strcmp failed");
  cfree(value);
  value = List_pop(list);
  //check((!strcmp((char *) value, "FOUR")), "strcmp failed");
  cfree(value);
  value = List_pop(list);
  //check((!strcmp((char *) value, "THREE")), "strcmp failed");
  cfree(value);

  LIST_FOREACH(list, first, next, iter) {
    printf("after pop: %s\n", iter->value);
  }
  NL;
  
  check(1, "avoid warning");

  printf("(done.)\n");
  return NULL;
 error:
  return "List_pop failed";
}

void *test_create_index()
{
  Index *idx;

  printf("test_create_index()\n");
  printf("-------------------\n");

  check((listindex = create_index(list)), "listindex invalid");
  idx = listindex;

  for(int i = 0; i < list->count; idx++, i++)
    printf("Index[%d] = %c\n", i, *((char *) *idx));

  cfree(listindex);
  printf("(done.)\n");
  return NULL;
 error:
  return "List_pop failed";
}

void *test_bubble_sort()
{
  Index *idx;

  printf("test_bubble_sort()\n");
  printf("------------------\n");

  check((listindex = bubble_sort(list, &cmp_TYPE_gt)), "listindex invalid");
  idx = listindex;

  for(int i = 0; i < list->count; idx++, i++)
    printf("Index[%d] = %c\n", i, *((char *) *idx));

  cfree(listindex);
  printf("(done.)\n");
  return NULL;
 error:
  return "List_pop failed";
}


void *all_tests()
{
  mu_suite_start();
  mu_run_test(test_list_create);
  mu_run_test(test_list_destroy); /* destroy empty list */
  if (!list) printf("list is NULL after List_destroy()\n");
  mu_run_test(test_list_create);
  //mu_run_test(test_list_clear); /* clear empty list */
  mu_run_test(test_list_push);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_push);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_pop); /* pop until list is exhausted */
  mu_run_test(test_list_destroy); /* destroy exhausted list */
  if (!list) printf("list is NULL after List_destroy()\n");
  mu_run_test(test_list_destroy); /* destroy destroyed list */
  if (!list) printf("list is NULL after List_destroy()\n");
  mu_run_test(test_list_push); /* push creates list, if necessary */
  mu_run_test(test_list_push);
  mu_run_test(test_list_push);
  mu_run_test(test_create_index);
  mu_run_test(test_bubble_sort);
  mu_run_test(test_list_destroy);
  if (!list) printf("list is NULL after List_destroy()\n");
  NL;

  return NULL;
}

RUN_TESTS(all_tests);

