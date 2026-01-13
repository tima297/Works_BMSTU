#include "../include/Product.h"

Product::Product(int id, const std::string& n, double p, int stock)
    : product_id(id), name(n), price(p), stock_quantity(stock) {}
