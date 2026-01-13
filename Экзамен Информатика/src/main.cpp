#include <iostream>
#include <memory>
#include <algorithm>
#include <numeric>
#include "include/DatabaseConnection.h"
#include "include/User.h"
#include "include/Order.h"
#include "include/Product.h"
#include "include/Payment.h"

using namespace std;

void displayMainMenu() {
    cout << "\n=== Online Store System ===" << endl;
    cout << "Please select your role:" << endl;
    cout << "1. Login as Administrator" << endl;
    cout << "2. Login as Manager" << endl;
    cout << "3. Login as Customer" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";
}

void adminMenu(shared_ptr<Admin>& admin, DatabaseConnection<string>& db) {
    int choice;
    while (true) {
        cout << "\n=== Administrator Menu ===" << endl;
        cout << "1. Add new product" << endl;
        cout << "2. Update product" << endl;
        cout << "3. Delete product" << endl;
        cout << "4. View all orders" << endl;
        cout << "5. View order details" << endl;
        cout << "6. Change order status" << endl;
        cout << "7. View order status history" << endl;
        cout << "8. View audit log" << endl;
        cout << "9. Generate CSV report" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string name;
                double price;
                int stock;
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter stock quantity: ";
                cin >> stock;
                admin->addProduct(name, price, stock, db);
                break;
            }
            case 2: {
                int product_id;
                string name;
                double price;
                int stock;
                cout << "Enter product ID: ";
                cin >> product_id;
                cin.ignore();
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new price: ";
                cin >> price;
                cout << "Enter new stock: ";
                cin >> stock;
                admin->updateProduct(product_id, name, price, stock, db);
                break;
            }
            case 3: {
                int product_id;
                cout << "Enter product ID to delete: ";
                cin >> product_id;
                admin->deleteProduct(product_id, db);
                break;
            }
            case 4: {
                admin->viewAllOrders(db);
                break;
            }
            case 5: {
                int order_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                admin->viewOrderStatus(order_id, db);
                break;
            }
            case 6: {
                int order_id;
                string status;
                cout << "Enter order ID: ";
                cin >> order_id;
                cin.ignore();
                cout << "Enter new status (pending/completed/canceled/returned): ";
                getline(cin, status);
                admin->updateOrderStatus(order_id, status, db);
                break;
            }
            case 7: {
                int order_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                auto result = db.executeQuery("SELECT * FROM get_order_status_history(" + 
                                             to_string(order_id) + ")");
                cout << "\n--- Order Status History ---" << endl;
                for (const auto& row : result) {
                    for (const auto& cell : row) {
                        cout << cell << " | ";
                    }
                    cout << endl;
                }
                break;
            }
            case 8: {
                auto result = db.executeQuery("SELECT * FROM audit_log ORDER BY performed_at DESC");
                cout << "\n--- Audit Log ---" << endl;
                for (const auto& row : result) {
                    for (const auto& cell : row) {
                        cout << cell << " | ";
                    }
                    cout << endl;
                }
                break;
            }
            case 9: {
                cout << "Report generation would save data to CSV file" << endl;
                break;
            }
            case 10: {
                return;
            }
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void managerMenu(shared_ptr<Manager>& manager, DatabaseConnection<string>& db) {
    int choice;
    while (true) {
        cout << "\n=== Manager Menu ===" << endl;
        cout << "1. View pending orders" << endl;
        cout << "2. Approve order" << endl;
        cout << "3. Update product stock" << endl;
        cout << "4. View order details" << endl;
        cout << "5. Change order status" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                manager->viewPendingOrders(db);
                break;
            }
            case 2: {
                int order_id;
                cout << "Enter order ID to approve: ";
                cin >> order_id;
                manager->approveOrder(order_id, db);
                break;
            }
            case 3: {
                int product_id, quantity;
                cout << "Enter product ID: ";
                cin >> product_id;
                cout << "Enter new quantity: ";
                cin >> quantity;
                manager->updateStock(product_id, quantity, db);
                break;
            }
            case 4: {
                int order_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                manager->viewOrderStatus(order_id, db);
                break;
            }
            case 5: {
                int order_id;
                string status;
                cout << "Enter order ID: ";
                cin >> order_id;
                cin.ignore();
                cout << "Enter new status: ";
                getline(cin, status);
                auto result = db.executeQuery("CALL update_order_status(" + 
                                             to_string(order_id) + ", '" + status + "', " + 
                                             to_string(manager->getUserId()) + ")");
                break;
            }
            case 6: {
                return;
            }
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void customerMenu(shared_ptr<Customer>& customer, DatabaseConnection<string>& db) {
    int choice;
    while (true) {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. Create new order" << endl;
        cout << "2. Add item to order" << endl;
        cout << "3. Remove item from order" << endl;
        cout << "4. View my orders" << endl;
        cout << "5. View order status" << endl;
        cout << "6. Make payment" << endl;
        cout << "7. Return order" << endl;
        cout << "8. View order status history" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                customer->createOrder(db);
                break;
            }
            case 2: {
                int order_id, product_id, quantity;
                cout << "Enter order ID: ";
                cin >> order_id;
                cout << "Enter product ID: ";
                cin >> product_id;
                cout << "Enter quantity: ";
                cin >> quantity;
                customer->addToOrder(order_id, product_id, quantity, db);
                break;
            }
            case 3: {
                int order_id, order_item_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                cout << "Enter order item ID: ";
                cin >> order_item_id;
                customer->removeFromOrder(order_id, order_item_id, db);
                break;
            }
            case 4: {
                auto result = db.executeQuery("SELECT * FROM orders WHERE user_id = " + 
                                             to_string(customer->getUserId()));
                cout << "\n--- My Orders ---" << endl;
                for (const auto& row : result) {
                    for (const auto& cell : row) {
                        cout << cell << " | ";
                    }
                    cout << endl;
                }
                break;
            }
            case 5: {
                int order_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                customer->viewOrderStatus(order_id, db);
                break;
            }
            case 6: {
                int order_id;
                string payment_method;
                cout << "Enter order ID: ";
                cin >> order_id;
                cin.ignore();
                cout << "Enter payment method (Card/Wallet/SBP): ";
                getline(cin, payment_method);
                customer->makePayment(order_id, payment_method, db);
                break;
            }
            case 7: {
                int order_id;
                cout << "Enter order ID to return: ";
                cin >> order_id;
                customer->returnOrder(order_id, db);
                break;
            }
            case 8: {
                int order_id;
                cout << "Enter order ID: ";
                cin >> order_id;
                auto result = db.executeQuery("SELECT * FROM get_order_status_history(" + 
                                             to_string(order_id) + ")");
                cout << "\n--- Order Status History ---" << endl;
                for (const auto& row : result) {
                    for (const auto& cell : row) {
                        cout << cell << " | ";
                    }
                    cout << endl;
                }
                break;
            }
            case 9: {
                return;
            }
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

int main() {
    try {
        // Connect to PostgreSQL
        DatabaseConnection<string> db("host=localhost user=postgres password=password dbname=online_store");
        
        if (!db.isConnected()) {
            cerr << "Failed to connect to database!" << endl;
            return 1;
        }
        
        int choice;
        while (true) {
            displayMainMenu();
            cin >> choice;
            cin.ignore();
            
            switch (choice) {
                case 1: {
                    // Admin login
                    auto admin = make_shared<Admin>(1, "Admin User", "admin@store.com", "hash", 1);
                    adminMenu(admin, db);
                    break;
                }
                case 2: {
                    // Manager login
                    auto manager = make_shared<Manager>(2, "Manager User", "manager@store.com", "hash", 0);
                    managerMenu(manager, db);
                    break;
                }
                case 3: {
                    // Customer login
                    auto customer = make_shared<Customer>(3, "Customer User", "customer@store.com", "hash", 0);
                    customerMenu(customer, db);
                    break;
                }
                case 4: {
                    cout << "Goodbye!" << endl;
                    return 0;
                }
                default:
                    cout << "Invalid choice" << endl;
            }
        }
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
