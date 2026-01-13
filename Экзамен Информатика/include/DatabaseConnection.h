#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <memory>

template<typename T>
class DatabaseConnection {
private:
    pqxx::connection conn;
    std::unique_ptr<pqxx::transaction_base> transaction;
    
public:
    DatabaseConnection(const std::string& connection_string);
    ~DatabaseConnection();
    
    std::vector<std::vector<std::string>> executeQuery(const std::string& query);
    void executeNonQuery(const std::string& query);
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    void createFunction(const std::string& function_name, const std::string& function_body);
    void createTrigger(const std::string& trigger_name, const std::string& trigger_body);
    std::string getTransactionStatus();
    bool isConnected() const;
};

#endif // DATABASE_CONNECTION_H
