#include "ex19-obj.h"

/*
  Object destructor
*/
void
Object_destroy(void *self) {
    Object         *obj = self;
    cfree(obj->description);
    cfree(obj);
}

void
Object_describe(void *self) {
    assert(self);
    assert(((Object *) self)->description);

    printf("%s\n", ((Object *) self)->description);
}

/*
  virtual initializer
  return 0/1, if OK/failure
*/
int
Object_init(void *self) {
    return 0;
}

/*
  virtual funtion
*/
void           *
Object_move(void *self, Direction direction) {
    printf("You cannot go in this direction.\n");
    return NULL;
}

/*
  virtual funtion
  return 0/1, if monster is alive/dead
*/
int
Object_attack(void *self) {
    printf("You cannot attack this.\n");
    return 0;
}

/*
  Object constructor
*/
void           *
Object_new(size_t size, Object proto, char *description) {
    Object         *obj;

    if (!proto.destroy)
        proto.destroy = Object_destroy;
    if (!proto.describe)
        proto.describe = Object_describe;
    if (!proto.init)
        proto.init = Object_init;
    if (!proto.move)
        proto.move = Object_move;
    if (!proto.attack)
        proto.attack = Object_attack;

    obj = calloc(1, size);
    check_mem(obj);
    *obj = proto;		/* deep copy */
    obj->description = strdup(description);

    check(!(obj->init(obj)), "object initialisation failed");

    return obj;
error:
    cfree(obj);
    return NULL;
}
