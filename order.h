#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <iostream>
#include <exception>
#include "product.h"
#include "java.h"
#include "donut.h"

class Order
{
public:
  static int orderid;
  Order();
  Order(const Order &ordcpy);
  int order_number() const;
  void add_product(Product *product);
  std::vector<Product *> products() const;

  bool paid() const;
  void pay();
  bool filled() const;
  void fill();
  bool discarded() const;
  void discard();
  
  bool pending();
  bool completed();
  
  double profit();

  std::string products_to_string();
  friend bool operator<(const Order &x, const Order &r);

protected:
  std::vector<Product *> _products;

private:
  int _next_order_number;
  int _order_number;
  bool _is_paid;
  bool _is_filled;
  bool _is_discarded;
};
#endif