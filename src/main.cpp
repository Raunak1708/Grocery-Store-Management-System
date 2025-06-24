#include <iostream>
#include "../include/product.h"
#include "../include/inventory.h"
using namespace std;
int main(){
    Inventory inv;
    inv.addproduct(Product(1,"Biscuit",25.00,500));
    inv.addproduct(Product(2,"shampoo",200,250));
    inv.addproduct(Product(3,"sugar",40.5,1000));
    cout<<"Product-List"<<endl;
    inv.displayall();

    cout<<"search for product 3\n";
    Product *P=inv.searchbyId(3);
    if(P!=nullptr){
        P->display();
    } 
    else{
        cout<<"Product not found"<<endl;
    }

    cout<<"testing the Update function\n";
    if(inv.updateproduct(2,"shampoo",300,1200)){
        cout<<"update successful \n";
    }
    else{
        cout<<"Product not found"<<endl;
    }
    cout<<"updated----list"<<endl;
    inv.displayall();

    return 0;


}