#include<iostream>

int main(int argc, char *argv[])
{
  int i1 = 1;
  const int i2 = 2, i3 = 3;

  //int const *p1 same as const int *p1
  int const *p1 = &i1;
  const int *p2 = &i1;
  // int *const p3 = &i2; /// error ,i2 is const;
  const int *const p4 = &i1;
  int const *const p5 = &i2;
  std::cout << "*p1 " << *p1 <<" *p2 " << *p2 << " *p4 " << *p4
            << " *p5 " << *p5 << std::endl;

  i1 = 0;
  std::cout<< "*p4 " << *p4 << std::endl;
 //  *p1 = 0;
 //  *p2 = 0; ///error p1 and p2 to const

  p1 = &i2;
  std::cout<< "*p1 " << *p1 << std::endl;
  p2 = &i2;
  std::cout<< "*p2 " << *p2 << std::endl;

  return 0;
}
