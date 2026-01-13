#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int product_id;
    std::string name;
    double price;
    int stock_quantity;
    
public:
    Product(int id, const std::string& n, double p, int stock);
    
    int getProductId() const { return product_id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stock_quantity; }
    
    void setPrice(double p) { price = p; }
    void setStockQuantity(int s) { stock_quantity = s; }
};

#endif // PRODUCT_H
