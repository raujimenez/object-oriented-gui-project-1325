#ifndef STORE_H
#define STORE_H
#include "product.h"
#include "java.h"
#include "donut.h"
#include "order.h"
#include <vector>
#include <map>
#include "customer.h"
class Store
{
public:
  Store(std::string name);
  std::string name();
  std::vector<Product *> products();
  std::vector<Customer> customers();
  void add_product(Product *product);
  int number_of_products();
  std::string product_to_string(int product);
  void add_customer(Customer person);
  int number_of_customers();
  std::string customer_to_string(int customer);

  void place_order(Order order, int customer);
  int number_of_orders();
  std::string order_to_string(int order_number);

private:
  std::string _name;
  std::vector<Product *> _products;
  std::vector<Customer> _customers;
  std::map<Order, Customer> _orders;
};

#endif