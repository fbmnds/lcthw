#include "ex22.h"


int THE_SIZE = 1000;

int THE_EXTERN_SIZE = 1111;
  
static int THE_AGE = 37;

int get_age(void)
{
  return THE_AGE;
}

void set_age(const int age)
{
  log_info("the age before set_age() = %d", THE_AGE);
  THE_AGE = age;
  log_info("the age after set_age() = %d", THE_AGE);
}

double update_static(const double new_value)
{
  static double value = 1.0;
 
  double old_value = value;
  value = new_value;

  return old_value;
}

