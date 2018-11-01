#include "product.h"

Product::Product(std::string name, double price, double cost) : _name{name}, _price{price}, _cost{cost} {}

std::string Product::name()
{
    return _name;
}
double Product::price()
{
    return _price;
}
double Product::cost()
{
    return _cost;
}

std::string Product::to_string()
{
    return name() + " $" + std::to_string(price()) + " $" + std::to_string(cost());
}