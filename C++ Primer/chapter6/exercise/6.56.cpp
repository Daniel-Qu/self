#include <iostream>
#include <vector>

int addition(int a, int b)
{
  return a + b;
}
int subtraction(int a, int b)
{
  return a - b;
}
int multiplication(int a, int b)
{
  return a * b;
}
int division(int a, int b)
{
  return a / b;
}
int main (int argc, char *argv[])
{
  typedef decltype(addition) *func;
  func add = addition, sub = subtraction, multi = multiplication, div = division;
  std::vector<func> funcs{add, sub, multi, div};
  for(auto i : funcs)
  {
    std::cout << (*i)(3, 3) << std::endl;
  }
  return 0;
}

