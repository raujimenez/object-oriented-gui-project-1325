#ifndef STORE_H
#define STORE_H
#include "product.h"

class Store{
    public:
        Store(std::string name);
        std::string name();
        std::vector<Products*> products();
        void add_product(product* product);
        int number_of_products();
        std::string product_to_string(int product);
    private:
        std::string _name;
        std::vector<Products*> _products;
};

#endif