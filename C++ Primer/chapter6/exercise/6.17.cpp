#include <iostream>
#include <cctype>

bool is_supper(const std::string & s);
void to_lower(std::string &s);
int main(int argc, char *argv[])
{
  std::string s;
  std::getline(std::cin, s);
  std::cout << "Have supper : " << is_supper(s) << std::endl;
  to_lower(s);
  std::cout << s << std::endl;
  return 0;
}

bool is_supper(const std::string & s)
{
  for(auto c : s)
  {
    if(std::isupper(c))
      return true;
  }
    return false;
}
void to_lower(std::string &s)
{
  for(auto &c : s)
  {
    c = std::tolower(c);
  }
  return ;
}
