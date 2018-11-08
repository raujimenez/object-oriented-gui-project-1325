#include "customer.h"

Customer::Customer(std::string renter, std::string renter_phone) : _customer{renter}, _customer_phone{renter_phone} {}
std::string Customer::to_string()
{
    return _customer + " " + _customer_phone;
}
