#include<iostream>

int main(int argc, char *argv[])
{
  int array_d1[4] = {0, 1, 2, 3};
  int array_d2[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j <2; j++)
    {
      std::cout << array_d2[i][j] << " ";
    }
    std::cout << "\n";
  }
  for(auto &i : array_d2)
  {
    for(auto j : i)
      std::cout << j << " ";
  }
  std::cout << "\n";
  for(auto i : array_d1)
  {
    std::cout << i << " ";
  }
  std::cout << "\n";
  // int *pbeg = std::begin(*array_d2), *pend = std::end(array_d2[3]);
  // while(pbeg != pend)
  // {
  //   std::cout << *pbeg << " ";
  //   ++pbeg;
  // }
  // std::cout << "\n";
  int *pbeg2 = std::begin(array_d1), *pend2 = std::end(array_d1);
  while(pbeg2 != pend2)
  {
    std::cout << *pbeg2 << " ";
    ++pbeg2;
  }
  std::cout << "\n";
  return 0;
}
