#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "product.h"
#include "java.h"
#include "donut.h"

static int orderid = 0;

class Order
{
  public:
    Order();
    int order_number();
    void add_product(Product *product);
    bool paid();
    void pay();
    bool filled();
    void fill();
    std::string products_to_string();
  protected:
    std::vector<Product *> _products;

  private:
    int _next_order_number;
    int _order_number;
    bool _is_paid;
    bool _is_filled;
};
#endif