#include "../include/lendingcart.h"
#include <iostream>
#include <iomanip>

void LendingCart ::addlendingitem(Product& p,int quantity){
    lenditems.push_back(p);
    lentQuantities.push_back(quantity);
    dueAmount+=p.getprice()*quantity;
}

void LendingCart::viewlentitems() const {
    if (lenditems.empty()) {
        cout << "No borrowed items.\n";
        return;
    }

    cout << "\n Borrowed Items for: " << borrowerName << "\n";
    cout << left << setw(12) << "Item"
         << right << setw(6) << "Qty"
         << setw(10) << "Price"
         << setw(12) << "Total" << "\n";

    for (size_t i = 0; i < lenditems.size(); ++i) {
        const Product& p = lenditems[i];
        int q = lentQuantities[i];
        cout << left << setw(12) << p.getname()
             << right << setw(6) << q
             << setw(10) << fixed << setprecision(2) << p.getprice()
             << setw(12) << fixed << setprecision(2) << (p.getprice() * q)
             << "\n";
    }
    cout << "\nTotal Due: Rs. " << fixed << setprecision(2) << dueAmount << "\n";
}

double LendingCart::getdueAmount() const {
    return dueAmount;
}

void LendingCart::clearlendingcart() {
    lenditems.clear();
    lentQuantities.clear();
    dueAmount = 0;
    borrowerName = "";
}

bool LendingCart::isEmpty() const {
    return lenditems.empty();
}

void LendingCart::setborrowerName(const string& name) {
    borrowerName = name;
}

string LendingCart::getborrowerName() const {
    return borrowerName;
}