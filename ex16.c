#include "ex16.h"

int main (int argc, char * argv[])
{
  Person * person1 = Person_create("Hans", "Dorf, Brunnenplatz 1", 5, MALE);
  Person * person2 = Person_create("Gretel", NULL, 4, FEMALE);
  
  Person_print(person1);
  Person_print(person2);
  
  Person_delete(person1);
  Person_delete(person2);

  return 0;
}
