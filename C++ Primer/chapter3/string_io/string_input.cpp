#include<iostream>
#include<string>
int main(int argc, char *argv[])
{
  std::string sentence;
  while(std::getline(std::cin, sentence))
  {
    if(sentence.empty())
      break;
    std::cout << sentence << std::endl;
  }
  std::cout << "next" << std::endl;
  std::string words;
  while(std::cin >> words)
  {
    if(words == "#")
      break;
    std::cout << words << std::endl;
  }
  return 0;
}

