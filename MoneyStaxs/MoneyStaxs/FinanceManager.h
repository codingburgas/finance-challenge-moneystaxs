#pragma once

#include <vector>
#include "User.h"

class FinanceManager {
private:
    User* currentUser = nullptr;
    std::vector<User> users;
    const std::string filename = "finance_data.csv";

    void loadFromCSV();
    void saveToCSV() const;
    User* findUserByUsername(const std::string& username);

public:
    FinanceManager();
    ~FinanceManager();
    void registerUser();
    void loginUser();
    void addIncome();
    void addExpense();
    void viewReport() const;
};
