#include<iostream>
#include<list>
#include<algorithm>

struct Drink
{
  public:

  std::string name;
  double unitPrice;
  double count;
  double total;

  void get_total()
  {
    total = count * unitPrice;
  }
  Drink()
  {
    name = "";
    unitPrice = 0;
    count = 0;
    total = count * unitPrice;
  }
  const bool operator <(Drink &node_)const
  {
    return this->total < node_.total;
  }
};
// bool mysort(MineralWater node1_, MineralWater node2_){ return(node1_.cost > node2_.cost) ;}
int main(int argc, char *argv[])
{
  std::list<Drink> drinks;
  Drink node1;
  node1.name = "kang shi fu";
  node1.unitPrice = 1;
  node1.count = 2;
  node1.get_total();
  drinks.push_back(node1);

  Drink node2;
  node2.name = "nong fu shan quan";
  node2.unitPrice = 2;
  node2.count = 2;
  node2.get_total();
  drinks.push_back(node2);

  Drink node3;
  node3.name = "bai sui shan";
  node3.unitPrice = 4;
  node3.count = 0;
  node3.get_total();
  drinks.push_back(node3);

  Drink node4;
  node4.name = "Coca Cola";
  node4.unitPrice = 3.5;
  node4.count = 5;
  node4.get_total();
  drinks.push_back(node4);
  // mineralWaters.sort(mineralWaters.begin(), mineralWaters.end(), mysort);
  drinks.sort();
  for(std::list<Drink>::iterator iter = drinks.begin(); iter != drinks.end(); iter++)
  {
    std::cout << iter->name << std::endl;
  }

  // drinks.reverse();
  // for(std::list<Drink>::iterator iter = drinks.begin(); iter != drinks.end(); iter++)
  // {
  //   std::cout << iter->name << std::endl;
  // }

 // for(std::list<Drink>::iterator iter = drinks.end(); iter != drinks.begin(); iter--)
 // {
 //   std::cout << iter->name << std::endl;
 // }

  // Drink node_expensive = drinks.back();

  // std::cout << "drinks.size: " << drinks.size() <<std::endl;

  // drinks.pop_back();

  // std::cout << "drinks.size: " << drinks.size() <<std::endl;

  // std::cout << "The most expensive mineral drink is " << node_expensive.name << " ."
  //           << std::endl;

  // std::cout << "The second expensive mineral drink is " << drinks.back().name << " ."
  //           << std::endl;
  std::list<Drink>::iterator iter = drinks.begin();
  while(iter != drinks.end())
  {
    if(iter->unitPrice == 3.5)
    {
      drinks.remove(*iter);
    }
    std::cout << iter->name << std::endl;
    iter++;
  }
  return 0;
}
