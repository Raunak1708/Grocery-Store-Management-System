#ifndef PRODUCT_H
#define PRODUCT_H
// #include<iostream>
#include<string>
using namespace std;
class Product{
    private:
    int id;
    string name;
    double price;
    int stock;
    public:
        Product();
        Product(int id,string name,double price,int stock);

        // get functions
        int getid() const;
        string getname() const;
        double getprice() const;
        int getquantity() const;

        // set functions
        void setquantity(int q);
        void setprice(double p);
        void setName(const std::string& newName);
        

        // display 
        void display() const;

};

#endif