#ifndef EX19_H
#define EX19_H

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "dbg.h"
#include "ex19-obj.h"

#define YOUDAMAGERATE 2
#define MONSTERDAMAGERATE 4

typedef struct Room {
    char           *name;
    struct Room    *north;
    struct Room    *east;
    struct Room    *south;
    struct Room    *west;
}               Room;

Room           *Room_new(char *name);

void            Room_destroy(Room * self);

void            Creature_destroy(void *self);

void            You_destroy(void *self);

void           *You_move(void *self, Direction direction);

int             You_attack(void *self);

Object          YouProto = {
    .destroy = You_destroy,
    .move = You_move,
    .attack = You_attack
};

typedef struct You {
    Object          proto;
    int             strength;
    Room           *location;
}               You;

typedef struct Monster {
    Object          proto;
    int             strength;
    Room           *location;
}               Monster;

void            Monster_destroy(void *self);

int             Monster_attack(void *self);

Object          MonsterProto = {
    .destroy = Monster_destroy,
    .attack = Monster_attack
};

typedef struct Map {
    Object          proto;
    You            *you;
    Monster        *monster;
    Room           *hall;
    Room           *throne;
    Room           *kitchen;
    Room           *arena;
}               Map;

int             Map_init(void *self);

void            Map_destroy(void *self);

Object          MapProto = {
    .init = Map_init,
    .destroy = Map_destroy
};

#endif
