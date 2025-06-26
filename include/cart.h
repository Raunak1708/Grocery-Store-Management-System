#ifndef CART_H
#define CART_H
#include "product.h"
#include<vector>

class Cart{
    private:
        vector<Product>items;
    public:
            void additem(Product& p,int s);
            void removeitem(int id);
            void viewcart() const;
            double totalamount() const;
            bool isempty() const; 
            void clearCart();
            const vector<Product>& getItems() const;
};
#endif
