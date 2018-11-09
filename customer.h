#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
  public:
    Customer(std::string renter, std::string renter_phone);
    std::string to_string();

  private:
    std::string _customer;
    std::string _customer_phone;
};

#endif