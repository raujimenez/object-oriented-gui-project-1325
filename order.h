#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "product.h"
#include "java.h"
#include "donut.h"


class Order
{
  public:
    static int orderid;
    Order();
    int order_number() const;
    void add_product(Product *product);
    bool paid();
    void pay();
    bool filled();
    void fill();
    std::string products_to_string();
    friend bool operator< (const Order& x, const Order& r);

  protected:
    std::vector<Product *> _products;

  private:
    int _next_order_number;
    int _order_number;
    bool _is_paid;
    bool _is_filled;
};
#endif