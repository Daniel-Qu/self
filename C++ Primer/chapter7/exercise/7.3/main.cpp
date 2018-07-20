
#include "Sales_data.h"

int main(int argc, char *argv[])
{
  Sales_data total;
  // if (total.read(std::cin, total))
  if(total.read(std::cin))
  {
    Sales_data trans;
   // while(trans.read(std::cin, trans))
    while(trans.read(std::cin))
    {
      if(total.isbn() == trans.isbn())
        total.combine(trans);
      else
      {
        print(std::cout, total) << std::endl;
        total = trans;
      }
    }
    print(std::cout, total) << std::endl;
  }
  else
  {
    std::cerr << "No data?" << std::endl;
  }
  return 0;
}


