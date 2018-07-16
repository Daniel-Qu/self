#include <iostream>
#include "fact.h"

int main(int argc, char *argv[])
{
  char wd;
  while(std::cin >> wd && wd != 'q')
  {
    std::cout << "static fact : " << fact_static() << std::endl;
    std::cout << "fact : " << fact() << std::endl;
  }
  return 0;
}
