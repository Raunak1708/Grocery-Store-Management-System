#include "../include/Cart.h"
#include <iostream>

using namespace std;

void Cart::additem( Product& p,int s) {
    for (auto& item : items) {
        if (item.getid() == p.getid()) {
            // Product already in cart: increase quantity
            item.setquantity(item.getquantity() + s);
            return;
        }
    }
    Product item=p;
    p.setquantity(s);
    // Not found, add as new item
    items.push_back(p);
}

void Cart :: removeitem(int id){
    for(auto it=items.begin();it!=items.end();it++){
        if(it->getid()==id){
            items.erase(it);
            cout<<"Item removed from cart"<<endl;
            return;
        }
    }
    cout<<"item not found"<<endl;
}

void Cart :: viewcart() const{
     if (items.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }
    std::cout << "--- Your Cart ---\n";
    for (const auto& item : items) {
        item.display();
    }
}
double Cart :: totalamount() const{
    double total=0;
    for(const auto &i:items){
        total+=i.getprice()*i.getquantity();
    }
    return total;
}
bool Cart :: isempty() const{
    return items.empty();
}
void Cart::clearCart() {
    items.clear();
}

const vector<Product>& Cart::getItems() const {
    return items;
}
