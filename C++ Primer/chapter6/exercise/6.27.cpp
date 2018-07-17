#include <iostream>

int addition(std::initializer_list<int> list);

int main(int argc, char *argv[])
{
  int a, b, c;
  std::cin >> a >> b >> c;
  std::cout << "The sum of " << a << "、" << b << " and " << c <<" is "
            << addition({a, b, c}) << std::endl;
  return 0;
}
int addition(std::initializer_list<int> list)
{
  int sum = 0;
  for(auto &num : list)
  {
    sum += num;
  }
  return sum;
}
