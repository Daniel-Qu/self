#include <iostream>
#include <vector>

#include <cassert>

template<typename T>
void print_vector(std::vector<T> &vec, decltype(vec.size()) size)
{

  if(size > 1)
  {
    print_vector(vec, size - 1);
  }
  if(size - 1 == vec.size() - 1)
  {
    std::cout << vec[size - 1] << std::endl;
    assert(std::cout << "vector.size: " << vec.size() << std::endl);
  }
  else
    std::cout << vec[size - 1] << " ";
  return ;
}
int main(int argc, char *argv[])
{
  std::vector<int> vec{5, 1, 2, 3};
  print_vector(vec, vec.size());
}

