#ifndef LENDINGLEDGER_H
#define LENDINGLEDGER_H

#include "product.h"
#include <map>
#include <vector>
#include <string>

class LendingLedger {
private:
    struct BorrowRecord {
        std::vector<Product> items;
        std::vector<int> quantities;
        double dueAmount = 0;
    };

    std::map<std::string, BorrowRecord> ledger; // borrower name → record

public:
    void lendProduct(const std::string& borrower, const Product& p, int qty);
    void viewBorrowed(const std::string& borrower) const;
    double getDue(const std::string& borrower) const;
    bool hasBorrowed(const std::string& borrower) const;
    void repay(const std::string& borrower,int amount);
    std::vector<std::string> getAllBorrowers() const;
};

#endif
