#include "customer.h"
Customer::Customer()
{
    _customer = "John Smith";
    _customer_phone = "000-000-0000";
}
Customer::Customer(std::string renter, std::string renter_phone) : _customer{renter}, _customer_phone{renter_phone} {}
std::string Customer::to_string(){ return _customer + " " + _customer_phone;}
