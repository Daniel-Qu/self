#include "Sales_data.h"

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    this->units_sold += rhs.units_sold;
    this->revenue += rhs.revenue;
    return *this;
}

double Sales_data::avg_price() const
{
  if(this->units_sold != 0)
    return this->revenue / units_sold;
  else
    return 0;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
  Sales_data sum = lhs;
  sum.combine(rhs);
  return sum;
}

// std::istream& read(std::istream &is, Sales_data &item)
// {
//   double price = 0;
//   is >> item.bookNo >> item.units_sold >> price;
//   item.revenue = price * item.units_sold;
//   return is;
// }

// std::istream& Sales_data::read(std::istream &is, Sales_data &item)
// {
//   double price = 0;
//   is >> item.bookNo >> item.units_sold >> price;
//   item.revenue = price * item.units_sold;
//   return is;
// }

std::istream& Sales_data::read(std::istream &is)
{
  double price = 0;
  is >> this->bookNo >> this->units_sold >> price;
  this->revenue = price * this->units_sold;
  return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
  os << item.isbn() << " " << item.units_sold << " "
     << item.revenue << " " << item.avg_price();
  return os;
}

