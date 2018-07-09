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
  bool operator <(Drink &node_)const
  {
    return this->total < node_.total;
  }
  bool operator ==(Drink &node_)const
  {
    return this->name == node_.name;
  }
  Drink operator +(const Drink &node_)
  {
    Drink temp = *this;
    temp.count = this->count + node_.count;
    temp.total = this->total + node_.total;

    return temp;
  }
  Drink& operator =(const Drink &node_)
  {
    if(this == &node_)
      return *this;
    this->name = node_.name;
    this->unitPrice = node_.unitPrice;
    this->count = node_.count;
    this->total = node_.total;

    return *this;
  }
  // Drink& operator +=(const Drink &node_)
  // {
  //     this->count += node_.count;
  //     this->total += node_.total;
  //     return *this;
  // }
  Drink& operator +=(const Drink &node_)
  {
    *this = *this + node_;
    return *this;
  }
  friend std::ostream& operator<<(std::ostream& out, const Drink &node_)
  {
    out << node_.name << " " << node_.unitPrice
        << " " << node_.count << " " << node_.total;
    return out;
  }
};

// bool mysort(MineralWater node1_, MineralWater node2_){ return(node1_.cost > node2_.cost) ;}
int main(int argc, char *argv[])
{
  std::list<Drink> drinks;
  Drink node1;
  node1.name = "kang shi fu";
  node1.unitPrice = 1;
  node1.count = 1;
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
  node3.count = 3;
  node3.get_total();
  drinks.push_back(node3);

  Drink node4;
  node4.name = "Coca Cola";
  node4.unitPrice = 3.5;
  node4.count = 4;
  node4.get_total();
  drinks.push_back(node4);

  Drink drink5;
  drink5.name = "bai sui shan";
  drink5.unitPrice = 4;
  drink5.count = 4;
  drink5.get_total();
  // mineralWaters.sort(mineralWaters.begin(), mineralWaters.end(), mysort);
  drinks.sort();

  for(std::list<Drink>::iterator iter = drinks.begin(); iter != drinks.end(); iter++)
  {
    // std::cout << iter->name << std::endl;
    std::cout << *iter << std::endl;
  }
  Drink node_expensive = drinks.back();

  std::cout << node_expensive.name << ":" << node_expensive.total <<std::endl;
  std::cout << "\n" ;
  for(std::list<Drink>::iterator iter = drinks.begin(); iter != drinks.end(); iter++)
  {
    if(*iter == drink5)
    {
      // *iter += drink5;
      *iter = drink5;
    }
  }
  std::cout << "\n" ;
  drinks.sort();
  for(std::list<Drink>::iterator iter = drinks.begin(); iter != drinks.end(); iter++)
  {
    // std::cout << iter->name << std::endl;
    std::cout << *iter << std::endl;
  }
  node_expensive = drinks.back();
  std::cout << node_expensive.name << ":" << node_expensive.total <<std::endl;
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
  std::cout << "\n";
  std::list<Drink>::iterator iter = drinks.begin();
  while(iter != drinks.end())
  {
    Drink *dp;
    dp = &(*iter);

   // if(dp->name == "Coca Cola")
   // {
   //   iter = drinks.erase(iter);
   // }
   if((*iter).name == "Coca Cola")
   {
     iter = drinks.erase(iter);
   }
    else
    {
      // std::cout << iter->name << std::endl;
      std::cout << *iter << std::endl;
      iter++;
    }
  }
  return 0;
}
