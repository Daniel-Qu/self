#include<iostream>

int main(int argc, char *argv[])
{
  int i = 0;
  // int *p = i;  /*p is pointer , right object must be address!*/
  int *p_ = &i;
  // std::cout<< "p: " << p << " p_: " << p_ <<std::endl;
  std::cout<<" p_: " << p_ <<std::endl;
  std::cout<<" *p_: " << *p_ <<std::endl;
  return 0;
}
