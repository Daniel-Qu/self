#include<iostream>
#include<string>
#include<vector>

#include<cctype>

int main(int argc, char *argv[])
{
  std::string word;
  std::vector<std::string> words;
  while(std::cin >> word)
  {
    if(word == "#")
      break;
    words.push_back(word);
  }
  for(auto &i : words)
  {
    for(auto &j : i)
    {
      j = std::toupper(j);
      std::cout << j;
    }
    std::cout << " ";
  }
  std::cout << "\n";
  // for(auto i : words)
  // {
  //   for(auto j : i)
  //   {
  //     std::cout << j;
  //   }
  //   std::cout << " ";
  // }
  // std::cout << "\n";
  // std::string test{"Hello!"};
  // for(auto &i : test)
  // {
  //   i = std::toupper(i);
  //   std::cout<< i ;
  // }
  // std::cout << "\n";
  return 0;
}
