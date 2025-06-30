#ifndef LENDINGCART_H
#define LENDINGCART_H
#include <iostream>
#include <vector>   
#include "product.h"

using namespace std;
class LendingCart {
private:
    vector<Product> lenditems;
    string borrowerName;
    vector<int> lentQuantities;
    double dueAmount=0;
public:
    void addlendingitem( Product& p,int quantity);
    void viewlentitems() const;
    double getdueAmount() const;
    void clearlendingcart();
    bool isEmpty() const;
    void setborrowerName(const string& name);
    string getborrowerName() const;
} ;

#endif