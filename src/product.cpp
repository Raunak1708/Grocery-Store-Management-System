#include "../include/product.h"
#include <iostream>
using namespace std;


Product::Product() : id(0), name(""), price(0.0), stock(0) {}

Product::Product(int id, std::string name, double price, int quantity)
    : id(id), name(name), price(price), stock(quantity) {}

int Product :: getid() const{
    return id;
}
string Product :: getname() const{
    return name;
}
double Product :: getprice() const{
    return price;
}
int Product :: getstock() const{
    return stock;
}

// setters
void Product :: setstock(int q){
    stock=q;
    return;
}
void Product :: setprice(double p){
    price=p;
    return;
}
void Product::setName(const std::string& newName) {
    name = newName;
}
void Product::display() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | Price: Rs " << price
              << " | Qty: " << stock << std::endl;
}
