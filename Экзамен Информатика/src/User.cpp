#include "../include/User.h"
#include "../include/Order.h"
#include "../include/DatabaseConnection.h"
#include <iostream>

// User base class
User::User(int id, const std::string& n, const std::string& e,
           const std::string& r, const std::string& ph, int ll)
    : user_id(id), name(n), email(e), role(r), password_hash(ph), 
      loyalty_level(ll) {}

// Admin implementation
Admin::Admin(int id, const std::string& n, const std::string& e,
             const std::string& ph, int ll)
    : User(id, n, e, "admin", ph, ll) {}

void Admin::addProduct(const std::string& name, double price, int stock,
                       DatabaseConnection<std::string>& db) {
    std::string query = "INSERT INTO products (name, price, stock_quantity) "
                       "VALUES ('" + name + "', " + std::to_string(price) + 
                       ", " + std::to_string(stock) + ")";
    try {
        db.executeNonQuery(query);
        std::cout << "Product added successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error adding product: " << e.what() << std::endl;
    }
}

void Admin::updateProduct(int product_id, const std::string& name,
                         double price, int stock, DatabaseConnection<std::string>& db) {
    std::string query = "UPDATE products SET name = '" + name + 
                       "', price = " + std::to_string(price) +
                       ", stock_quantity = " + std::to_string(stock) +
                       " WHERE product_id = " + std::to_string(product_id);
    try {
        db.executeNonQuery(query);
        std::cout << "Product updated successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error updating product: " << e.what() << std::endl;
    }
}

void Admin::deleteProduct(int product_id, DatabaseConnection<std::string>& db) {
    std::string query = "DELETE FROM products WHERE product_id = " + 
                       std::to_string(product_id);
    try {
        db.executeNonQuery(query);
        std::cout << "Product deleted successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error deleting product: " << e.what() << std::endl;
    }
}

void Admin::viewAllOrders(DatabaseConnection<std::string>& db) {
    auto result = db.executeQuery("SELECT * FROM orders");
    std::cout << "\n--- All Orders ---" << std::endl;
    for (const auto& row : result) {
        for (const auto& cell : row) {
            std::cout << cell << " | ";
        }
        std::cout << std::endl;
    }
}

void Admin::updateOrderStatus(int order_id, const std::string& status,
                             DatabaseConnection<std::string>& db) {
    std::string query = "CALL update_order_status(" + std::to_string(order_id) + 
                       ", '" + status + "', " + std::to_string(user_id) + ")";
    try {
        db.executeNonQuery(query);
        std::cout << "Order status updated successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error updating order status: " << e.what() << std::endl;
    }
}

void Admin::createOrder(DatabaseConnection<std::string>& db) {
    std::cout << "Admins cannot create orders" << std::endl;
}

void Admin::viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "SELECT status FROM orders WHERE order_id = " + 
                       std::to_string(order_id);
    auto result = db.executeQuery(query);
    if (!result.empty()) {
        std::cout << "Order status: " << result[0][0] << std::endl;
    }
}

void Admin::cancelOrder(int order_id, DatabaseConnection<std::string>& db) {
    updateOrderStatus(order_id, "canceled", db);
}

// Manager implementation
Manager::Manager(int id, const std::string& n, const std::string& e,
                 const std::string& ph, int ll)
    : User(id, n, e, "manager", ph, ll), manager_id(id) {}

void Manager::approveOrder(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "CALL approve_order(" + std::to_string(order_id) + 
                       ", " + std::to_string(manager_id) + ")";
    try {
        db.executeNonQuery(query);
        std::cout << "Order approved successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error approving order: " << e.what() << std::endl;
    }
}

void Manager::updateStock(int product_id, int new_quantity,
                         DatabaseConnection<std::string>& db) {
    std::string query = "UPDATE products SET stock_quantity = " + 
                       std::to_string(new_quantity) + 
                       " WHERE product_id = " + std::to_string(product_id);
    try {
        db.executeNonQuery(query);
        std::cout << "Stock updated successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error updating stock: " << e.what() << std::endl;
    }
}

void Manager::viewPendingOrders(DatabaseConnection<std::string>& db) {
    auto result = db.executeQuery("SELECT * FROM orders WHERE status = 'pending'");
    std::cout << "\n--- Pending Orders ---" << std::endl;
    for (const auto& row : result) {
        for (const auto& cell : row) {
            std::cout << cell << " | ";
        }
        std::cout << std::endl;
    }
}

void Manager::createOrder(DatabaseConnection<std::string>& db) {
    std::cout << "Managers cannot create orders" << std::endl;
}

void Manager::viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "SELECT status FROM orders WHERE order_id = " + 
                       std::to_string(order_id);
    auto result = db.executeQuery(query);
    if (!result.empty()) {
        std::cout << "Order status: " << result[0][0] << std::endl;
    }
}

void Manager::cancelOrder(int order_id, DatabaseConnection<std::string>& db) {
    std::cout << "Managers cannot cancel orders" << std::endl;
}

// Customer implementation
Customer::Customer(int id, const std::string& n, const std::string& e,
                   const std::string& ph, int ll)
    : User(id, n, e, "customer", ph, ll) {}

void Customer::addToOrder(int order_id, int product_id, int quantity,
                         DatabaseConnection<std::string>& db) {
    std::string query = "INSERT INTO order_items (order_id, product_id, quantity) "
                       "VALUES (" + std::to_string(order_id) + ", " + 
                       std::to_string(product_id) + ", " + std::to_string(quantity) + ")";
    try {
        db.executeNonQuery(query);
        std::cout << "Item added to order" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error adding item: " << e.what() << std::endl;
    }
}

void Customer::removeFromOrder(int order_id, int order_item_id,
                              DatabaseConnection<std::string>& db) {
    std::string query = "DELETE FROM order_items WHERE order_item_id = " + 
                       std::to_string(order_item_id) + 
                       " AND order_id = " + std::to_string(order_id);
    try {
        db.executeNonQuery(query);
        std::cout << "Item removed from order" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error removing item: " << e.what() << std::endl;
    }
}

void Customer::makePayment(int order_id, const std::string& payment_method,
                          DatabaseConnection<std::string>& db) {
    std::string query = "UPDATE orders SET status = 'completed' "
                       "WHERE order_id = " + std::to_string(order_id);
    try {
        db.executeNonQuery(query);
        std::cout << "Payment processed via " << payment_method << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error processing payment: " << e.what() << std::endl;
    }
}

void Customer::returnOrder(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "SELECT order_date FROM orders WHERE order_id = " + 
                       std::to_string(order_id) + " AND user_id = " + 
                       std::to_string(user_id);
    auto result = db.executeQuery(query);
    
    if (!result.empty()) {
        // Check if 30 days have not passed
        time_t order_time = std::stol(result[0][0]);
        time_t now = time(nullptr);
        if ((now - order_time) <= 30 * 24 * 60 * 60) {
            std::string update_query = "UPDATE orders SET status = 'returned' "
                                      "WHERE order_id = " + std::to_string(order_id);
            try {
                db.executeNonQuery(update_query);
                std::cout << "Order returned successfully" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error returning order: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Return period expired (more than 30 days)" << std::endl;
        }
    }
}

void Customer::createOrder(DatabaseConnection<std::string>& db) {
    std::string query = "INSERT INTO orders (user_id, status, total_price, order_date) "
                       "VALUES (" + std::to_string(user_id) + ", 'pending', 0.0, NOW())";
    try {
        db.executeNonQuery(query);
        std::cout << "Order created successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error creating order: " << e.what() << std::endl;
    }
}

void Customer::viewOrderStatus(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "SELECT status FROM orders WHERE order_id = " + 
                       std::to_string(order_id) + " AND user_id = " + 
                       std::to_string(user_id);
    auto result = db.executeQuery(query);
    if (!result.empty()) {
        std::cout << "Your order status: " << result[0][0] << std::endl;
    } else {
        std::cout << "Order not found" << std::endl;
    }
}

void Customer::cancelOrder(int order_id, DatabaseConnection<std::string>& db) {
    std::string query = "UPDATE orders SET status = 'canceled' "
                       "WHERE order_id = " + std::to_string(order_id) + 
                       " AND user_id = " + std::to_string(user_id) + 
                       " AND status = 'pending'";
    try {
        db.executeNonQuery(query);
        std::cout << "Order canceled successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error canceling order: " << e.what() << std::endl;
    }
}
