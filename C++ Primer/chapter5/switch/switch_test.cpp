#include<iostream>

int main(int argc, char *argv[])
{
  int flag ;

  std::cin >> flag;
  switch(flag)
  {
    case 1:
      std::cout << "flag is 1" << std::endl;
    case 2:
      std::cout << "flag is 2" << std::endl;
    case 3:
      std::cout << "flag is 3" << std::endl;
    default:
      std::cout << "flag is other" << std::endl;
      break;
  }
  return 0;
}
