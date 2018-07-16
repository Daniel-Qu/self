#include "fact.h"

int fact_static(void)
{
  static unsigned int key = 0;
  if(key++ != 0)
    return 1;
  else
    return 0;
}

int fact(void)
{
  unsigned int key = 0;
  if(key++ != 0)
    return 1;
  else
    return 0;
}
