#pragma once

#include <string>
#include <vector>
#include "Transaction.h"

class User {
public:
    std::string username, password;
    std::vector<Transaction> incomes, expenses;

    User(const std::string& uname, const std::string& pass);
    void addIncome(const Transaction& income);
    void addExpense(const Transaction& expense);
};
