#include "../include/inventory.h"
// #include "product.h"
#include<iostream>
// #include<vector>
using namespace std;

void Inventory :: addproduct(const Product&P){
    products.push_back(P);
}
void Inventory :: displayall() const{
    for(const auto&p:products){
        p.display();
    }
}

bool Inventory::deleteproduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getid() == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}
Product* Inventory::searchbyId(int id) {
    for (auto& p : products) {
        if (p.getid() == id)
            return &p;
    }
    return nullptr;
}
bool Inventory::updateproduct(int id, const string& newname, double newprice, int newstock) {
    for (auto& p : products) {
        if (p.getid() == id) {
            // Direct member access is not allowed, so we add setters
            p.setprice(newprice);
            p.setstock(newstock);
            // To update name, we’ll need to add setName() in Product class
            p.setName(newname);
            return true;
        }
    }
    return false; // Product not found
}



