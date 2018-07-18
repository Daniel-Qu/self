#include <iostream>

std::string make_plural(std::size_t ctr, const std::string &word, const std::string &ending = "s");
int main(int argc, char *argv[])
{
  std::cout << make_plural(2, "success", "es") << std::endl;
  std::cout << make_plural(2, "failure") << std::endl;
  return 0;
}

std::string make_plural(std::size_t ctr, const std::string &word, const std::string &ending)
{
  return (ctr > 1) ? word + ending : word;
}
