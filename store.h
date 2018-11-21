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

  std::map<Order, Customer> orders();
  void place_order(Order order, int customer);
  int number_of_orders();
  std::string order_to_string(int order_number);

  double cash();
  
  void pay_order(int order_number);
  void fill_order(int order_number);
  void discard_order(int order_number);

  bool order_is_filled(int order_number);
  bool order_is_paid(int order_number);
  bool order_is_discarded(int order_number);
  bool order_is_completed(int order_number);
  bool order_is_pending(int order_number);

private:
  double _cash;
  std::string _name;
  std::vector<Product *> _products;
  std::vector<Customer> _customers;
  std::map<Order, Customer> _orders;
  std::map<Order, Customer>::iterator get_pair(int order_number);
};

#endif