#include "customer.h"
Customer::Customer(): _customer{"John Smith"}, _customer_phone{"000-000-0000"} {}
Customer::Customer(const Customer &cust): _customer{cust.name()}, _customer_phone{cust.phone()} {}
Customer::Customer(std::string renter, std::string renter_phone) : _customer{renter}, _customer_phone{renter_phone} {}
std::string Customer::to_string(){ return _customer + " " + _customer_phone;}

//GETTER METHODS
std::string Customer::name() const { return _customer; }
std::string Customer::phone() const { return _customer_phone; }