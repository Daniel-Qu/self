#include<iostream>

int main(int argc, char *argv[])
{
  int i = 2;
  double d = 3.14;
  int id = static_cast<int>(d);
  std::cout << "id " << id << std::endl;
  int multi = i * static_cast<int>(d);
  std::cout << "multi " << multi << std::endl;
  return 0;
}
