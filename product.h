#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product
{
  protected:
    std::string _name;
    double _price;
    double _cost;

  public:
    Product(std::string name, double price, double cost);
    std::string name();
    double profit();
    double price();
    double cost();
    virtual std::string to_string();
};

#endif
