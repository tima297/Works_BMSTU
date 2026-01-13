#include "../include/Payment.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Payment::Payment(double amt, const std::string& method)
    : amount(amt), payment_method(method), is_completed(false) {}

bool Payment::processPayment() {
    // Simulate payment processing
    srand(time(nullptr));
    bool success = (rand() % 2 == 0);
    is_completed = success;
    return success;
}

bool CardPayment::pay(double amount) {
    std::cout << "Processing card payment of " << amount << " rubles..." << std::endl;
    // Simulate payment
    return true;
}

bool WalletPayment::pay(double amount) {
    std::cout << "Processing wallet payment of " << amount << " rubles..." << std::endl;
    // Simulate payment
    return true;
}

bool SBPPayment::pay(double amount) {
    std::cout << "Processing SBP payment of " << amount << " rubles..." << std::endl;
    // Simulate payment
    return true;
}
