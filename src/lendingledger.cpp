#include "../include/lendingledger.h"
#include <iostream>
#include <iomanip>

void LendingLedger::lendProduct(const std::string& borrower, const Product& p, int qty) {
    ledger[borrower].items.push_back(p);
    ledger[borrower].quantities.push_back(qty);
    ledger[borrower].dueAmount += p.getprice() * qty;
}

void LendingLedger::viewBorrowed(const std::string& borrower) const {
    auto it = ledger.find(borrower);
    if (it == ledger.end()) {
        std::cout << " No records found for borrower: " << borrower << "\n";
        return;
    }

    const auto& rec = it->second;
    std::cout << "\nBorrowed Items for: " << borrower << "\n";
    std::cout << std::left << std::setw(12) << "Item"
              << std::right << std::setw(6) << "Qty"
              << std::setw(10) << "Price"
              << std::setw(12) << "Total" << "\n";

    for (size_t i = 0; i < rec.items.size(); ++i) {
        const auto& item = rec.items[i];
        int qty = rec.quantities[i];
        std::cout << std::left << std::setw(12) << item.getname()
                  << std::right << std::setw(6) << qty
                  << std::setw(10) << std::fixed << std::setprecision(2) << item.getprice()
                  << std::setw(12) << item.getprice() * qty << "\n";
    }
    std::cout << "Total Due: Rs. " << std::fixed << std::setprecision(2) << rec.dueAmount << "\n";
}

double LendingLedger::getDue(const std::string& borrower) const {
    auto it = ledger.find(borrower);
    if (it != ledger.end()) return it->second.dueAmount;
    return 0.0;
}

bool LendingLedger::hasBorrowed(const std::string& borrower) const {
    return ledger.find(borrower) != ledger.end() && ledger.at(borrower).dueAmount > 0;
}

void LendingLedger::repay(const std::string& borrower,int amount) {
    auto it=ledger.find(borrower);
    int totaldue=it->second.dueAmount;
    if(amount==totaldue){
        ledger.erase(borrower);
    }
    else{
        ledger.find(borrower)->second.dueAmount=(totaldue-amount);
    }

     // clear due & items
}

std::vector<std::string> LendingLedger::getAllBorrowers() const {
    std::vector<std::string> names;
    for (const auto& entry : ledger) names.push_back(entry.first);
    return names;
}
