#include <iostream>
#include "../include/product.h"
#include "../include/inventory.h"
#include "../include/cart.h"          
using namespace std;
int main(){
    Inventory inv;
    Cart cart;
    inv.addproduct(Product(1,"Biscuit",25.00,500));
    inv.addproduct(Product(2,"shampoo",200,250));
    inv.addproduct(Product(3,"sugar",40.5,1000));

    int choice;
   do {
        std::cout << "\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Remove from Cart\n5. View Total\n6. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            inv.displayall();
        } else if (choice == 2) {
            int id, qty;
            std::cout << "Enter Product ID: ";
            std::cin >> id;
            Product* p = inv.searchbyId(id);
            if (!p) {
                std::cout << "Product not found!\n";
                continue;
            }

            std::cout << "Enter Quantity: ";
            std::cin >> qty;

            if (qty <= 0) {
                std::cout << "Invalid quantity.\n";
            } else if (qty > p->getquantity()) {
                std::cout << "Insufficient stock. Available: " << p->getquantity() << "\n";
            } else {
                cart.additem(*p, qty);
                std::cout << "Item added to cart.\n";
            }

        } else if (choice == 3) {
            cart.viewcart();
        } else if (choice == 4) {
            int id;
            std::cout << "Enter Product ID to remove: ";
            std::cin >> id;
            cart.removeitem(id);
        } else if (choice == 5) {
            std::cout << "Total: Rs. " << cart.totalamount() << "\n";
        }
    } while (choice != 6);

    return 0;
}