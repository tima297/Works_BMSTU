#include "../include/DatabaseConnection.h"
#include <iostream>
#include <stdexcept>

template<typename T>
DatabaseConnection<T>::DatabaseConnection(const std::string& connection_string)
    : conn(connection_string), transaction(nullptr) {
    if (!conn.is_open()) {
        throw std::runtime_error("Database connection failed!");
    }
    std::cout << "Connected to PostgreSQL database successfully" << std::endl;
}

template<typename T>
DatabaseConnection<T>::~DatabaseConnection() {
    if (transaction) {
        transaction->abort();
    }
    if (conn.is_open()) {
        conn.disconnect();
    }
}

template<typename T>
std::vector<std::vector<std::string>> DatabaseConnection<T>::executeQuery(
    const std::string& query) {
    std::vector<std::vector<std::string>> result;
    try {
        pqxx::work tx(conn);
        pqxx::result res = tx.exec(query);
        
        for (auto row : res) {
            std::vector<std::string> row_data;
            for (auto field : row) {
                row_data.push_back(field.as<std::string>());
            }
            result.push_back(row_data);
        }
        tx.commit();
    } catch (const std::exception& e) {
        std::cerr << "Query execution error: " << e.what() << std::endl;
    }
    return result;
}

template<typename T>
void DatabaseConnection<T>::executeNonQuery(const std::string& query) {
    try {
        pqxx::work tx(conn);
        tx.exec(query);
        tx.commit();
    } catch (const std::exception& e) {
        std::cerr << "Non-query execution error: " << e.what() << std::endl;
        throw;
    }
}

template<typename T>
void DatabaseConnection<T>::beginTransaction() {
    transaction = std::make_unique<pqxx::transaction<>>(conn);
}

template<typename T>
void DatabaseConnection<T>::commitTransaction() {
    if (transaction) {
        transaction->commit();
        transaction = nullptr;
    }
}

template<typename T>
void DatabaseConnection<T>::rollbackTransaction() {
    if (transaction) {
        transaction->abort();
        transaction = nullptr;
    }
}

template<typename T>
void DatabaseConnection<T>::createFunction(const std::string& function_name,
                                           const std::string& function_body) {
    try {
        pqxx::work tx(conn);
        tx.exec(function_body);
        tx.commit();
        std::cout << "Function " << function_name << " created successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Function creation error: " << e.what() << std::endl;
    }
}

template<typename T>
void DatabaseConnection<T>::createTrigger(const std::string& trigger_name,
                                          const std::string& trigger_body) {
    try {
        pqxx::work tx(conn);
        tx.exec(trigger_body);
        tx.commit();
        std::cout << "Trigger " << trigger_name << " created successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Trigger creation error: " << e.what() << std::endl;
    }
}

template<typename T>
std::string DatabaseConnection<T>::getTransactionStatus() {
    if (transaction) {
        return "Transaction is active";
    }
    return "No active transaction";
}

template<typename T>
bool DatabaseConnection<T>::isConnected() const {
    return conn.is_open();
}

// Explicit instantiation for std::string
template class DatabaseConnection<std::string>;
