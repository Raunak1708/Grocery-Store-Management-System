#include "../include/inventory.h"
// #include "product.h"
#include<iostream>
#include <fstream>
#include <sstream>
// #include <iostream>
// #include<vector>
using namespace std;

void Inventory :: addproduct(const Product&P){
    products.push_back(P);
}
// void Inventory :: displayall() const{
//     for(const auto&p:products){
//         p.display();
//     }
// }

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
            p.setquantity(newstock);
            // To update name, we’ll need to add setName() in Product class
            p.setName(newname);
            return true;
        }
    }
    return false; // Product not found
}
void Inventory::loadFromFile(const std::string& filename) {
    products.clear();
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    int id, qty;
    double price;
    std::string name;

    while (file >> id >> name >> price >> qty) {
        Product p(id, name, price, qty);
        products.push_back(p);
    }
    file.close();
}

void Inventory::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error writing to file: " << filename << '\n';
        return;
    }

    for (const auto& p : products) {
        file << p.getid() << " " << p.getname() << " " << p.getprice() << " " << p.getquantity() << '\n';
    }
    file.close();
}

void Inventory::displayall() const {
    for (const auto& p : products) {
        p.display();
        if (p.getquantity() < 50) {
            std::cout << "Low stock alert: only " << p.getquantity() << " left!\n";
        }
    }
}



