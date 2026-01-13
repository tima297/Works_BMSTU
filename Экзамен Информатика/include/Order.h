#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <memory>
#include <string>
#include <ctime>

class OrderItem;
class Payment;

class Order {
private:
    int order_id;
    int user_id;
    std::string status;
    double total_price;
    time_t order_date;
    std::vector<std::unique_ptr<OrderItem>> items;
    std::unique_ptr<Payment> payment;
    
public:
    Order(int id, int uid, const std::string& st, double price, time_t date);
    ~Order() = default;
    
    void addItem(std::unique_ptr<OrderItem> item);
    void removeItem(int item_index);
    void setPayment(std::unique_ptr<Payment> pay) { payment = std::move(pay); }
    void setStatus(const std::string& new_status) { status = new_status; }
    
    int getOrderId() const { return order_id; }
    int getUserId() const { return user_id; }
    std::string getStatus() const { return status; }
    double getTotalPrice() const { return total_price; }
    const std::vector<std::unique_ptr<OrderItem>>& getItems() const { return items; }
    const Payment* getPayment() const { return payment.get(); }
};

class OrderItem {
private:
    int order_item_id;
    int order_id;
    int product_id;
    int quantity;
    double price;
    
public:
    OrderItem(int iid, int oid, int pid, int qty, double p);
    
    int getOrderItemId() const { return order_item_id; }
    int getProductId() const { return product_id; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
};

#endif // ORDER_H
