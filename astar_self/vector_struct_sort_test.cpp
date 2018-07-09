#include<iostream>
#include<vector>
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
};
bool mysort(Drink drink1_, Drink drink2_){ return(drink1_.total > drink2_.total) ;}
int main(int argc, char *argv[])
{
  std::vector<Drink> drinks;
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

  std::sort(drinks.begin(), drinks.end(), mysort);

  std::cout << "drinks.size: " << drinks.size() << std::endl;

  for(int i = 0; i < drinks.size(); i++)
  {
    std::cout << drinks[i].name << std::endl;
  }

  std::cout <<"\n";
  // std::reverse(drinks.begin(), drinks.end());
  // for(int i = 0; i < drinks.size(); i++)
  // {
  //   std::cout << drinks[i].name << std::endl;
  // }

  // std::cout << "The most expensive mineral drink is " << drinks[0].name << " ."
  //           << std::endl;

  std::vector<Drink>::iterator iter = drinks.begin();
  while(iter != drinks.end())
  {
    if(iter->name == "Coca Cola")
    {
      iter = drinks.erase(iter);
    }
    else
    {
      std::cout << iter->name << std::endl;
      iter++;
    }

  }
  std::cout << "drinks.size: " << drinks.size() << std::endl;

  return 0;
}
