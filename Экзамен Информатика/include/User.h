#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>

class Order;
class DatabaseConnection;

class User {
protected:
    int user_id;
    std::string name;
    std::string email;
    std::string role;
    std::string password_hash;
    int loyalty_level;
    std::vector<std::shared_ptr<Order>> orders;
    
public:
    User(int id, const std::string& n, const std::string& e, 
         const std::string& r, const std::string& ph, int ll);
    virtual ~User() = default;
    
    virtual void createOrder(DatabaseConnection<std::string>& db) = 0;
    virtual void viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) = 0;
    virtual void cancelOrder(int order_id, DatabaseConnection<std::string>& db) = 0;
    
    int getUserId() const { return user_id; }
    std::string getRole() const { return role; }
    void addOrder(std::shared_ptr<Order> order) { orders.push_back(order); }
    const std::vector<std::shared_ptr<Order>>& getOrders() const { return orders; }
};

class Admin : public User {
public:
    Admin(int id, const std::string& n, const std::string& e, 
          const std::string& ph, int ll);
    
    void addProduct(const std::string& name, double price, int stock, 
                   DatabaseConnection<std::string>& db);
    void updateProduct(int product_id, const std::string& name, 
                      double price, int stock, DatabaseConnection<std::string>& db);
    void deleteProduct(int product_id, DatabaseConnection<std::string>& db);
    void viewAllOrders(DatabaseConnection<std::string>& db);
    void updateOrderStatus(int order_id, const std::string& status, 
                          DatabaseConnection<std::string>& db);
    
    void createOrder(DatabaseConnection<std::string>& db) override;
    void viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) override;
    void cancelOrder(int order_id, DatabaseConnection<std::string>& db) override;
};

class Manager : public User {
private:
    int manager_id;
    
public:
    Manager(int id, const std::string& n, const std::string& e, 
            const std::string& ph, int ll);
    
    void approveOrder(int order_id, DatabaseConnection<std::string>& db);
    void updateStock(int product_id, int new_quantity, DatabaseConnection<std::string>& db);
    void viewPendingOrders(DatabaseConnection<std::string>& db);
    
    void createOrder(DatabaseConnection<std::string>& db) override;
    void viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) override;
    void cancelOrder(int order_id, DatabaseConnection<std::string>& db) override;
};

class Customer : public User {
public:
    Customer(int id, const std::string& n, const std::string& e, 
             const std::string& ph, int ll);
    
    void addToOrder(int order_id, int product_id, int quantity, 
                   DatabaseConnection<std::string>& db);
    void removeFromOrder(int order_id, int order_item_id, 
                        DatabaseConnection<std::string>& db);
    void makePayment(int order_id, const std::string& payment_method, 
                    DatabaseConnection<std::string>& db);
    void returnOrder(int order_id, DatabaseConnection<std::string>& db);
    
    void createOrder(DatabaseConnection<std::string>& db) override;
    void viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) override;
    void cancelOrder(int order_id, DatabaseConnection<std::string>& db) override;
};

#endif // USER_H
