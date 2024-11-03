#include "FinanceManager.h"
#include <iostream>
#include <limits>

int main() {
    FinanceManager financeManager;

    while (true) {
        int choice;
        std::cout << "=== Personal Finance Manager ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Add Income\n";
        std::cout << "4. Add Expense\n";
        std::cout << "5. View Report\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        while (!(std::cin >> choice) || choice < 1 || choice > 6) {
            std::cout << "Invalid choice. Please try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            financeManager.registerUser();
            break;
        case 2:
            financeManager.loginUser();
            break;
        case 3:
            financeManager.addIncome();
            break;
        case 4:
            financeManager.addExpense();
            break;
        case 5:
            financeManager.viewReport();
            break;
        case 6:
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
