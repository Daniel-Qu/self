#include <iostream>

int main(int argc, char *argv[])
{
  std::string s;
  std::string temp;
  std::cout << "argc: " << argc << std::endl;
  int i = 1;
  while(i < argc - 1)
  {
    temp.assign(argv[i]).append(" ");
    s += temp;
    ++i;
  }
  temp.assign(argv[i]);
  s += temp;

  std::cout << s << std::endl;
  return 0;
}
