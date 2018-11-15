#include "order.h"

Order::Order()
{
    _order_number = orderid;
    ++orderid;
}

int Order::order_number()
{
    return _order_number;
}

void Order::add_product(Product *product)
{
    _products.push_back(product);
}

bool Order::paid()
{
    return _is_paid;
}

void Order::pay()
{
    _is_paid = true;
}

bool Order::filled(){
    return _is_filled;
}

void Order::fill(){
    _is_filled = true;
}