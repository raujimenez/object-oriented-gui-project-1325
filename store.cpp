#include "store.h"

Store::Store(std::string name) : _name{name} {}

std::string Store::name() { return _name; }
std::vector<Product *> Store::products()
{
    return _products;
}
void Store::add_product(Product *product)
{
    _products.push_back(product);
}
int Store::number_of_products()
{
    return _products.size();
}

std::string Store::product_to_string(int product)
{
    return _products[product]->to_string();
}

void Store::add_customer(Customer person)
{
    _customers.push_back(person);
}
int Store::number_of_customers()
{
    return _customers.size();
}
std::string Store::customer_to_string(int customer)
{
    return _customers[customer].to_string();
}
