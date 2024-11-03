#include "User.h"

User::User(const std::string& uname, const std::string& pass)
    : username(uname), password(pass) {}

void User::addIncome(const Transaction& income) {
    incomes.push_back(income);
}

void User::addExpense(const Transaction& expense) {
    expenses.push_back(expense);
}
