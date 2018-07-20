#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

struct Sales_data
{
  std::string isbn() const {return bookNo;}
  Sales_data& combine(const Sales_data&);
  // std::istream &read(std::istream&, Sales_data&);
  std::istream &read(std::istream&);
  Sales_data() = default;
  Sales_data(std::istream &is)
  {
    // read(is, *this);
    read(is);
  }

  double avg_price() const;

  std::string bookNo;
  unsigned int units_sold = 0;
  double revenue = 0.0;
};

// std::istream &read(std::istream&, Sales_data&);
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);

#endif //! SALES_DATA_H
