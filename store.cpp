#include "store.h"

Store::Store(std::string name) : _name{name} {}

// GETTER METHODS
double Store::cash(){ return _cash; }
std::string Store::name() { return _name; }
std::vector<Product *> Store::products() { return _products; }
std::vector<Customer> Store::customers() { return _customers; }
std::map<Order, Customer> Store::orders() { return _orders; }

//PRODUCT METHODS
void Store::add_product(Product *product) { _products.push_back(product); }
int Store::number_of_products() { return _products.size(); }
std::string Store::product_to_string(int product) { return _products[product]->to_string(); }

//CUSTOMER METHODS
void Store::add_customer(Customer person) { _customers.push_back(person); }
int Store::number_of_customers() { return _customers.size(); }
std::string Store::customer_to_string(int customer) { return _customers[customer].to_string(); }

//ORDER METHODS
void Store::place_order(Order order, int customer) { _orders[order] = _customers[customer]; }
int Store::number_of_orders() { return _orders.size(); }
std::string Store::order_to_string(int order_number)
{
    std::string string_to_return{""};
    auto iter = get_pair(order_number);
    auto cust = iter->second;
    auto ord = iter->first;
    std::string status{""};
    if(ord.paid() && !ord.filled()) status += "(Paid)";
    else if(ord.pending()) status += "(Pending)";
    else if (ord.filled() && !ord.paid()) status += "(Filled)";
    else status += "(Completed)";
    string_to_return += cust.to_string() + ", Order#" + std::to_string(ord.order_number()) + status +"\n" + ord.products_to_string();
    return string_to_return;
}
//CHANGE THE BOOLEANS
void Store::pay_order(int order_number){
    auto iter = get_pair(order_number);
    auto ord = iter->first; //use copy constructor
    auto cust = iter->second; 
    ord.pay();
    if(ord.completed())
        _cash += ord.profit();
    _orders.erase(iter->first);
    _orders[ord] = cust;
}
void Store::fill_order(int order_number){
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    auto cust = iter->second;
    ord.fill();
    if(ord.completed())
        _cash += ord.profit();
    _orders.erase(iter->first);
    _orders[ord] = cust;
}
void Store::discard_order(int order_number){
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    ord.discard();
    _orders.erase(iter->first);
}

//GETTERS TO STATE MACHINE (READ-ONLY)
bool Store::order_is_paid(int order_number)
{
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    return ord.paid();
}
bool Store::order_is_filled(int order_number)
{
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    return ord.filled();
}
bool Store::order_is_discarded(int order_number)
{
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    return ord.discarded();
}
bool Store::order_is_completed(int order_number)
{
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    return ord.completed();
}
bool Store::order_is_pending(int order_number)
{
    auto iter = get_pair(order_number);
    auto ord = iter->first;
    return ord.pending();
}

//Gets itterator
std::map<Order, Customer>::iterator Store::get_pair(int order_number)
{
    auto iter = _orders.begin();
    for (int i{0}; i < order_number; i++) //get current value in map
        iter++;
    return iter;
}