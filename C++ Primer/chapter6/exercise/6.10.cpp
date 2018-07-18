#include <iostream>

void swap(int *a, int *b);
int main(int argc, char *argv[])
{
  int a, b;
  std::cin >> a >> b;
  swap(&a, &b);
  std::cout << "a: " << a << " b: " << b << std::endl;

  return 0;
}
void swap(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;

  return ;
}
