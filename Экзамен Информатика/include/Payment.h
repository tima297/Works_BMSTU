#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getPaymentMethod() const = 0;
};

class Payment {
private:
    double amount;
    std::string payment_method;
    bool is_completed;
    
public:
    Payment(double amt, const std::string& method);
    virtual ~Payment() = default;
    
    bool processPayment();
    double getAmount() const { return amount; }
    std::string getPaymentMethod() const { return payment_method; }
    bool isCompleted() const { return is_completed; }
};

class CardPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getPaymentMethod() const override { return "Card"; }
};

class WalletPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getPaymentMethod() const override { return "Wallet"; }
};

class SBPPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getPaymentMethod() const override { return "SBP"; }
};

#endif // PAYMENT_H
