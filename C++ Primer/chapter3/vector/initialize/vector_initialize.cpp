#include<iostream>
#include<vector>

int main(int argc, char *argv[])
{
  std::vector<std::vector<int> > test{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  std::cout << "test.size: " << test.size() << std::endl;
  for(decltype(test.size()) i = 0; i < test.size(); i++)
  {
    for(decltype(test[i].size()) j = 0; j < test[i].size(); j++)
    {
      std::cout << test[i][j] << std::endl;
    }
  }
  std::cout << "\n";
  for(auto i : test)
  {
    for(auto j : i)
    {
      std::cout << j << " ";
    }
  }
  std::cout<< "\n";
  return 0;
}
