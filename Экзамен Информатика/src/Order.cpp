#include "../include/Order.h"

Order::Order(int id, int uid, const std::string& st, double price, time_t date)
    : order_id(id), user_id(uid), status(st), total_price(price), 
      order_date(date), payment(nullptr) {}

void Order::addItem(std::unique_ptr<OrderItem> item) {
    items.push_back(std::move(item));
}

void Order::removeItem(int item_index) {
    if (item_index >= 0 && item_index < items.size()) {
        items.erase(items.begin() + item_index);
    }
}

OrderItem::OrderItem(int iid, int oid, int pid, int qty, double p)
    : order_item_id(iid), order_id(oid), product_id(pid), 
      quantity(qty), price(p) {}
