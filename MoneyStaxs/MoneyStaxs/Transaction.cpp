#include "Transaction.h"

Transaction::Transaction(const std::string& date, const std::string& category, double amount)
    : date(date), category(category), amount(amount) {}
