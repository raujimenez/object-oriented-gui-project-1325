#ifndef DONUT_H
#define DONUT_H
#include "product.h"
#include "frosting.h"
#include "filling.h"

class Donut : public Product
{
  protected:
    Frosting _frosting;
    bool _sprinkles;
    Filling _filling;

  public:
    Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
    Frosting frosting();
    bool sprinkles();
    Filling filling();
    std::string to_string() override;
}

#endif