#include "FinanceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

FinanceManager::FinanceManager() {
    loadFromCSV();
}

FinanceManager::~FinanceManager() {
    saveToCSV();
}

void FinanceManager::loadFromCSV() {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return;

    std::string line, section;
    User* user = nullptr;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line == "# Users") {
            section = "users";
            continue;
        }
        else if (line.find("# Incomes for ") == 0) {
            section = "incomes";
            std::string username = line.substr(13);
            user = findUserByUsername(username);
            continue;
        }
        else if (line.find("# Expenses for ") == 0) {
            section = "expenses";
            std::string username = line.substr(15);
            user = findUserByUsername(username);
            continue;
        }

        std::istringstream ss(line);
        if (section == "users") {
            std::string username, password;
            getline(ss, username, ',');
            getline(ss, password);
            users.emplace_back(username, password);
        }
        else if ((section == "incomes" || section == "expenses") && user) {
            std::string date, category;
            double amount;
            getline(ss, date, ',');
            getline(ss, category, ',');
            ss >> amount;
            Transaction transaction(date, category, amount);
            if (section == "incomes") user->addIncome(transaction);
            else if (section == "expenses") user->addExpense(transaction);
        }
    }
}

void FinanceManager::saveToCSV() const {
    std::ofstream outFile(filename);

    outFile << "# Users\n";
    for (const auto& user : users) {
        outFile << user.username << "," << user.password << "\n";
    }

    for (const auto& user : users) {
        outFile << "\n# Incomes for " << user.username << "\n";
        for (const auto& income : user.incomes) {
            outFile << income.date << "," << income.category << "," << income.amount << "\n";
        }

        outFile << "\n# Expenses for " << user.username << "\n";
        for (const auto& expense : user.expenses) {
            outFile << expense.date << "," << expense.category << "," << expense.amount << "\n";
        }
    }
}

User* FinanceManager::findUserByUsername(const std::string& username) {
    for (auto& user : users) {
        if (user.username == username) return &user;
    }
    return nullptr;
}

void FinanceManager::registerUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (findUserByUsername(username)) {
        std::cout << "Username already exists.\n";
        return;
    }

    users.emplace_back(username, password);
    std::cout << "User registered successfully!\n";
}

void FinanceManager::loginUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = &user;
            std::cout << "Login successful!\n";
            return;
        }
    }
    std::cout << "Invalid username or password.\n";
}

void FinanceManager::addIncome() {
    if (!currentUser) {
        std::cout << "Please log in first.\n";
        return;
    }
    std::string date, category;
    double amount;

    std::cout << "Enter date (DD-MM-YYYY): ";
    std::cin >> date;
    std::cout << "Enter category: ";
    std::cin >> category;
    std::cout << "Enter amount: ";
    std::cin >> amount;

    currentUser->addIncome(Transaction(date, category, amount));
    std::cout << "Income added successfully!\n";
}

void FinanceManager::addExpense() {
    if (!currentUser) {
        std::cout << "Please log in first.\n";
        return;
    }
    std::string date, category;
    double amount;

    std::cout << "Enter date (DD-MM-YYYY): ";
    std::cin >> date;
    std::cout << "Enter category: ";
    std::cin >> category;
    std::cout << "Enter amount: ";
    std::cin >> amount;

    currentUser->addExpense(Transaction(date, category, amount));
    std::cout << "Expense added successfully!\n";
}

void FinanceManager::viewReport() const {
    if (!currentUser) {
        std::cout << "Please log in first.\n";
        return;
    }

    double totalIncome = 0, totalExpense = 0;
    std::cout << "\n=== Report for " << currentUser->username << " ===\n";

    std::cout << "Incomes:\n";
    for (const auto& income : currentUser->incomes) {
        std::cout << income.date << " | " << income.category << " | " << income.amount << "\n";
        totalIncome += income.amount;
    }

    std::cout << "\nExpenses:\n";
    for (const auto& expense : currentUser->expenses) {
        std::cout << expense.date << " | " << expense.category << " | " << expense.amount << "\n";
        totalExpense += expense.amount;
    }

    std::cout << "\nTotal Income: " << totalIncome << "\n";
    std::cout << "Total Expenses: " << totalExpense << "\n";
    std::cout << "Net Balance: " << totalIncome - totalExpense << "\n";
}
