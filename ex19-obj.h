#ifndef EX19_OBJ_H
#define EX19_OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "dbg.h"

#define cfree(p) { if ((p)) free((p)); (p) = NULL; }

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

typedef enum {
  NORTH, EAST, SOUTH, WEST
}  Direction;

typedef struct Object{
  void (* destroy)(void *);
  void (* describe)(void *);
  int (* init)(void *);
  void * (* move)(void *, Direction);
  int (* attack)(void *);
  char * description;
} Object;


void Object_destroy(void *self);

void Object_describe(void *self);

int Object_init(void *self);

void * Object_move(void *self, Direction direction);

int Object_attack(void *self);

void * Object_new(size_t size, Object proto, char *description);

#endif

