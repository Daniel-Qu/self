#include<iostream>
#include<vector>

int main(int argc, char *argv[])
{
  const int array[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  // const std::vector<std::vector<int> > delta({0, 1}, {0, -1}, {1, 0}, {-1, 0});
  bool visited[10][10] = {false};

  // std::cout << "array.sizes " << array.size() << std::endl;
  std::cout << "array: " << array << std::endl;
  std::cout << "*array: " << *array << std::endl;

  // std::cout << "delta: " << delta << std::endl;
  // std::cout << "delta.size: " << delta.size() << std::endl;
  visited[0][1] = true;
  std::cout << "visited: " << visited[0][0] << std::endl;
  std::cout << "visited: " << visited[9][9] << std::endl;
  std::cout << "visited: " << visited[0][1] << std::endl;

  return 0;
}
