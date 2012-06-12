#include "ex16.h"

static long md5;

Person * Person_create(const char * name, const char * address, 
		       const int age, const int gender)
{
  Person * who;

  if (!name) 
    return NULL;
  
  if ((who = malloc(sizeof(Person)))) {
    if (strlen(name) <= MAXDATA - 1) 
      strncpy(who->name, name, strlen(name)+1); 
    else {
      strncpy(who->name, name, MAXDATA-1);
      who->name[MAXDATA-1] = '\0';
    }
    if (address)
      if (strlen(address) <= MAXDATA - 1) 
	strncpy(who->address, address, strlen(address)+1); 
      else {
	strncpy(who->address, address, MAXDATA-1);
	who->address[MAXDATA-1] = '\0';
      }
    else
      (who->address[0] = '\0');
    if (age > 0) 
      who->age = age;
    else
      who->age = 0;
    switch (gender) {
    case MALE:
      who->gender = MALE;
      break;
    case FEMALE:
      who->gender = FEMALE;
      break;
    default:
      who->gender = NA;
    }
    who->id = md5++;
  }

  return who;
}

void Person_delete(Person * who)
{
  if (who) {
    /* name not allocated */
    /* address not allocated */
    /* id will be lost / not reused */
  
    free(who);

    return;
  }
}

void Person_print(Person * who)
{
  if (who) {
    printf("name: %s\n", who->name);
    printf("address: %s\n", who->address);
    printf("age: %d\n", who->age);
    printf("gender: %d\n", who->gender);
    printf("id: %ld\n", who->id);
    printf("\n");
  }
  return;
}
