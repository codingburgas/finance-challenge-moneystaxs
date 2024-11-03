#pragma once

#include <string>

class Transaction {
public:
    std::string date;
    std::string category;
    double amount;

    Transaction(const std::string& date, const std::string& category, double amount);
};
