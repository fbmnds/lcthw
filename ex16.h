#ifndef EX16_H
#define EX16_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAXDATA    10
#define MAXRECORDS 200

#define NA     0
#define MALE   1
#define FEMALE 2

typedef struct Person {
  char name[MAXDATA];
  char address[MAXDATA];
  int age;
  int gender;
  long id;
} Person;

/*
  name is mandatory field, id will be generated, other fields will be defaulted 
  returns NULL, if an error occurs
*/
Person * Person_create(const char *, const char *, const int, const int);

void Person_delete(Person *);

void Person_print(Person *);


#endif /* EX16_H */
