#ifndef INVENTORY_H
#define INVENTORY_H
#include "product.h" 
#include<vector>
#include<string>
using namespace std;

class Inventory{
    private:
        vector<Product>products;
    public:
        void addproduct(const Product&P);
        bool  deleteproduct(int id);
        void displayall()const;
        Product* searchbyId(int id);
        bool updateproduct(int id,const string& newname,double newprice,int newstock);
};


#endif
