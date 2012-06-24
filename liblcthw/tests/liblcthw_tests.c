#include "list.h"
#include "dbg.h"
#include "minunit.h"

#include<string.h>
#include<stdlib.h>
#include <assert.h>

#define cfree(p) if ((p) != NULL) { free((p)); (p) = NULL; }
#define NL printf("\n")

List *list;
char *values[] = { "ONE", "TWO", "THREE", "FOUR", "FIVE", NULL };

void *test_list_create()
{
  list = List_create();

  check((list), "List_create returned NULL");
  check(!(list->first), "list->first invalid");
  check(!(list->last), "list->last invalid");
  check(!list->count, "list->count invalid");

  return NULL;
 error:
  return "List_create failed";
}

void *test_list_destroy()
{
  int rc = List_destroy(list);
  

  check(!rc, "List_destroy return code = %d", rc);
  return NULL;
 error:
  return "List_destroy failed";
}

void *test_list_clear()
{
  int rc = List_clear(list);
  check(!rc, "List_clear return code = %d", rc);
  return NULL;
 error:
  return "List_clear failed";
}

void *test_list_push()
{
  char **vp = values;

  while (*vp) {
    check((!(List_push(list, (void *) *vp))), "List_push failed on %s", *vp);
    vp++;
  }

  LIST_FOREACH(list, first, next, iter) {
    printf("after push %s \n", iter->value);
    //    check((!strcmp(iter->value, *(--vp))), "strcmp failed");
  }
  NL;

  return NULL;
 error:
  return "List_push failed";
}

void *test_list_pop()
{
  void *value;

 
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

  return NULL;
 error:
  return "List_pop failed";
}


void *all_tests()
{
  mu_suite_start();
  mu_run_test(test_list_create);
  mu_run_test(test_list_destroy); /* destroy empty list */
  list = NULL;
  mu_run_test(test_list_create);
  //mu_run_test(test_list_clear); /* clear empty list */
  mu_run_test(test_list_push);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_push);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_pop);
  mu_run_test(test_list_pop); /* pop until list is exhausted */
  //  mu_run_test(test_list_destroy);
  // mu_run_test(test_list_create);
  //  mu_run_test(test_list_clear);
  mu_run_test(test_list_destroy); /* destroy exhausted list */
  list = NULL;
  //mu_run_test(test_list_push); /* push creates list, if necessary */
  mu_run_test(test_list_destroy);
  list = NULL;
  /**/
  return NULL;
}

RUN_TESTS(all_tests);

