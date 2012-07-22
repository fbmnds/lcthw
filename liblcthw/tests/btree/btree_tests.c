/***********************************************************************\
|									|
|	B+tree function tests						|
|									|
|									|
|	Jan Jannink	created 12/22/94	revised 1/30/95		|
|									|
\***********************************************************************/

#include "btree/btree.h"

#include "misc/misc.h"
#include "misc/dbg.h"
#include "minunit.h"

#include <stdio.h>
#include <stdlib.h>

void *test_btree_1()
{
  Tree	*Bplus;
  //Nptr	keyNode;
  int	i;

  printf("test_btree_1()\n");
  printf("--------------\n");

  Bplus = initBtree(ARRAY_SIZE, NODE_SIZE / sizeof(Entry), compareKeys);
  check_mem(Bplus);

  insert(Bplus,17);
  insert(Bplus,16);
  insert(Bplus,15);
  insert(Bplus,14);
  insert(Bplus,13);
  insert(Bplus,12);
  insert(Bplus,11);
  insert(Bplus,10);
  insert(Bplus,9);
  insert(Bplus,8);
  insert(Bplus,7);
  insert(Bplus,6);
  insert(Bplus,5);
  insert(Bplus,4);
  insert(Bplus,3);
  insert(Bplus,2);
  insert(Bplus,1);

  for (i = 1; i < 17; i++)
    (void) search(Bplus, i);


  delete(Bplus,17);
  delete(Bplus,2);
  delete(Bplus,3);
  delete(Bplus,4);
  delete(Bplus,5);
  delete(Bplus,6);
  delete(Bplus,7);
  delete(Bplus,8);

  for (i = 1; i < 17; i++)
    (void) search(Bplus, i);
  listAllBtreeValues(Bplus);

  delete(Bplus,9);
  delete(Bplus,10);
  delete(Bplus,11);
  delete(Bplus,12);
  delete(Bplus,13);
  delete(Bplus,14);
  delete(Bplus,15);
  delete(Bplus,16);
  delete(Bplus,17); 

  listAllBtreeValues(Bplus);

  freeBtree(Bplus);

  printf("(done.)\n");
  return NULL;
 error:
  return "test_btree_1() failed";
}


void *test_btree_2()
{
  Tree	*Bplus;
  //Nptr	keyNode;
  int	i, j;

  printf("test_btree_2()\n");
  printf("--------------\n");

  Bplus = initBtree(ARRAY_SIZE, NODE_SIZE / sizeof(Entry), compareKeys);

  for (i = 0; i < 48; i++) {
    j = rand() >> 3 & 255;
    if (search(Bplus, j) == Bplus->tree - 1) {
      insert(Bplus, j);
      fprintf(stderr, "XXX %d, insert %d XXX\n", i, j);
    }
    else {
      delete(Bplus, j);
      fprintf(stderr, "XXX %d, delete %d XXX\n", i, j);
    }
    if (i > 45)
      listAllBtreeValues(Bplus);
  }
  for (i = 0; i < 256; i++)
    (void) search(Bplus, i);
  listAllBtreeValues(Bplus);
  freeBtree(Bplus);

  printf("(done.)\n");
  return NULL;
 error:
  return "test_btree_2() failed";
}

void *all_tests()
{
  mu_suite_start();
  mu_run_test(test_btree_1);
  mu_run_test(test_btree_2);

  return NULL;
}

RUN_TESTS(all_tests);

