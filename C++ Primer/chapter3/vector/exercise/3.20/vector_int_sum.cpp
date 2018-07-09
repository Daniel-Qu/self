#include<iostream>
#include<vector>
#include<cctype>
int main(int argc, char *argv[])
{
  std::vector<int> arry;
  int number;
  while(std::cin >> number)
  {
    // if(!std::isdigit(number))
    //   break;
    arry.push_back(number);
  }
  for(decltype(arry.size()) i = 1; i != arry.size(); i++)
  {
    int sum1 = arry[i - 1] + arry[i];
    std::cout << "sum1: " << sum1 << std::endl;
  }
  std::cout << "\n";
  for(decltype(arry.size()) i = 0; i != (arry.size() + 1)/2; i++)
  {
    int sum2 = arry[i] + arry[arry.size() - i -1];
    std::cout << "sum2: " << sum2 << std::endl;
  }
  return 0;
}
