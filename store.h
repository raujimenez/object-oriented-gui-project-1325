#ifndef STORE_H
#define STORE_H
#include "product.h"
#include "java.h"
#include "donut.h"
#include "vector"
#include "customer.h"
class Store
{
public:
  Store(std::string name);
  std::string name();
  std::vector<Product *> products();
  void add_product(Product *product);
  int number_of_products();
  std::string product_to_string(int product);
  void add_customer(Customer person);
  int number_of_customers();
  std::string customer_to_string(int customer);
private:
  std::string _name;
  std::vector<Product *> _products;
  std::vector<Customer> _customers;
};

#endif