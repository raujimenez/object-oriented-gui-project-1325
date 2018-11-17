#include "store.h"

Store::Store(std::string name) : _name{name} {}

std::string Store::name() { return _name; }
std::vector<Product *> Store::products()
{
    return _products;
}
std::vector<Customer> Store::customers()
{
    return _customers;
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

void Store::place_order(Order order, int customer)
{
    _orders[order] = _customers[customer];
}

int Store::number_of_orders()
{
    return _orders.size();
}

std::string Store::order_to_string(int order_number)
{
    std::string string_to_return{""};
    auto iter = _orders.begin();
    for (int i{0}; i < order_number; i++) //get current value in map
    {
        iter++;
    }
    //iter now contains point to current key
    auto cust = iter->second;
    auto ord = iter->first;
    string_to_return += cust.to_string() + ", Order#" + std::to_string(ord.order_number()) + "\n";
    string_to_return += ord.products_to_string();
    return string_to_return;
}