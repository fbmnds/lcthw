#include "ex19.h"

Room * Room_new(char * name)
{
  Room * room = malloc(sizeof(Room));
  check_mem(room);

  room->name = strdup(name);
  check_mem(room->name);

  return room;
 error:
  cfree(room->name);
  cfree(room);
  return NULL;
}

void Room_destroy(Room * self)
{
  Room * room = self;
  assert(room);
  assert(room->name);

  cfree(room->name);
  cfree(room);
}

void You_destroy(void * self)
{
  You * you = self;
  assert(you);
  
  Object_destroy(&you->proto);
}

/*
  implement, if monster may also move
void * Monster_move(void *self, Direction direction)  
  implement, if all creatures may move
void * Creature_move(void *self, Direction direction)  
*/

void * You_move(void *self, Direction direction)
{
  You * you = self;
  Room * next = NULL;

  assert(you);
  assert(you->location);

  switch (direction) {
  case NORTH:
    if (you->location->north) next = you->location->north;
    printf("You go north.\n");
    break;
  case EAST:
    if (you->location->east) next = you->location->east;
    printf("You go east.\n");
    break;
  case SOUTH:
    if (you->location->south) next = you->location->south;
    printf("You go south.\n");
    break;
  case WEST:
    if (you->location->west) next = you->location->west;
    printf("You go west.\n");
    break;    
  default:
    ;
  }

  if (next) 
    return next;
  else {
    printf("You cannot go there.\n");
    return you->location;
  }
}

int You_attack(void *self)
{
  You * you = self;
  assert(you);

  you->strength -= rand() % YOUDAMAGERATE; 

  return (you->strength > 0);
}

void Monster_destroy(void * self)
{
  Monster * monster = self;
  assert(monster);
  
  Object_destroy(&monster->proto);
}

int Monster_attack(void *self)
{
  Monster * monster = self;
  assert(monster);

  monster->strength -= rand() % MONSTERDAMAGERATE;

  return (monster->strength > 0);
}

int Map_init(void * self)
{
  Map * map = self;
  assert(map);

  map->you = NEW(You, "The Hero");
  check(map->you, "hero creation failed in map.");

  map->monster = NEW(Monster, "The Minotaur");
  check(map->monster, "monster creation failed in map.");  

  map->hall = Room_new("The Hall");
  map->throne = Room_new("The Throne");
  map->kitchen = Room_new("The Kitchen");
  map->arena = Room_new("The Arena");  

  map->hall->north = map->throne;
  
  map->throne->east = map->kitchen;
  map->throne->south = map->hall;
  map->throne->west = map->arena;

  map->arena->east = map->throne;

  map->kitchen->west = map->throne;

  map->you->location = map->hall;
  map->you->strength = 15;

  map->monster->location = map->arena;
  map->monster->strength = 13;

  return 0;
 error:
  return 1;
}

void Map_destroy(void * self)
{
  Map * map = self;
  assert(map);

  if (map->hall) Room_destroy(map->hall);
  if (map->throne) Room_destroy(map->throne);
  if (map->kitchen) Room_destroy(map->kitchen);
  if (map->arena) Room_destroy(map->arena);

  if (map->you) map->you->_(destroy)(map->you);
  if (map->monster) map->monster->_(destroy)(map->monster);

  Object_destroy(&map->proto);
}

int main(int argc, char * argv[]) 
{
  char c;

  Map * game = NEW(Map, "The Cave of the Minotaur");

  srand(time(NULL));

  while(1) {
    printf("\n>");
    c = getchar();
    c = tolower(c);
    while (getchar() != '\n');  /* eat all until (including) '\n' */
    switch (c) {
    case 'q':
      printf("Goodbye\n");
      game->_(destroy)(game);
      return 0;
    case 'a':
      if(!game->you->_(attack)(game->you)) {
	printf("You died.\n");
	game->_(destroy)(game);
	return 0;
      }
      if(!game->monster->_(attack)(game->monster)) {
	printf("The Minotaur died.\n");
	printf("You won.\n");
	game->_(destroy)(game);
	return 0;
      }
      break;
    case 'n':
      game->you->location = game->you->_(move)(game->you, NORTH);
      break;
    case 'e':
      game->you->location = game->you->_(move)(game->you, EAST);
      break;
    case 's':
      game->you->location = game->you->_(move)(game->you, SOUTH);
      break;
    case 'w':
      game->you->location = game->you->_(move)(game->you, WEST);
      break;
    case 'l':
      printf("You are in %s.\n", game->you->location->name);
      break;
    default:
      printf("You cannot do that.\n");
    }
  }

  return 0;
}
