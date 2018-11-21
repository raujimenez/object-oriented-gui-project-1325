#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer
{
  public:
    Customer();
    Customer(const Customer &cust);
    Customer(std::string renter, std::string renter_phone);
    std::string to_string();
    std::string name() const;
    std::string phone() const;
  private:
    std::string _customer;
    std::string _customer_phone;
};

#endif