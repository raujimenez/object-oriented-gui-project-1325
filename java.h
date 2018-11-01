#ifndef JAVA_H
#define JAVA_H
#include <vector>
#include "product.h"
#include "shot.h"

class Java : public Product
{
  protected:
    int _darkeness;
    std::vector<Shot> _shots;

  public:
    Java(std::string name, double price, double cost, int darkness);
    void add_shot(Shot shot);
    int darkeness();
    std::vector<Shot> shots();
    std::string to_string() override;
};

#endif