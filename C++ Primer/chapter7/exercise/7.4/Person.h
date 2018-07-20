#ifndef PERSON_H
#define PERSON_H

#include <string>
struct Person
{
  std::string inquiryName() const { return this->name; }

  std::string name;
  std::string address;
}
