#ifndef STORE_H
#define STORE_H
#include "product.h"
#include "java.h"
#include "donut.h"
#include "vector"

class Store
{
  public:
    Store(std::string name);
    std::string name();
    std::vector<Product *> products();
    void add_product(Product *product);
    int number_of_products();
    std::string product_to_string(int product);

  private:
    std::string _name;
    std::vector<Product *> _products;
};

#endif