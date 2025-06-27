#include <iostream>
#include <limits>
#include "inventory.h"
// #include "search.h"

void searchMenu(Inventory& inventory) {
    int choice;
    std::cout << "\n--- 🔍 Product Search Menu ---\n";
    std::cout << "1. Search by ID\n";
    std::cout << "2. Search by Name (partial)\n";
    std::cout << "3. Search by Price Range\n";
    std::cout << "4. Search by Stock Range\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(1000, '\n');
        std::cout << " Invalid input.\n";
        return;
    }

    if (choice == 1) {
        int id;
        std::cout << "Enter product ID: ";
        std::cin >> id;
        Product* p = inventory.searchbyId(id);
        if (p) p->display();
        else std::cout << "Product not found.\n";

    } else if (choice == 2) {
        std::string name;
        std::cout << "Enter name (partial): ";
        std::cin >> name;
        bool found = false;
        for (const auto& p : inventory.getAll()) {
            if (p.getname().find(name) != std::string::npos) {
                p.display(); found = true;
            }
        }
        if (!found) std::cout << "No match found.\n";

    } else if (choice == 3) {
        double minP, maxP;
        std::cout << "Enter min price: "; std::cin >> minP;
        std::cout << "Enter max price: "; std::cin >> maxP;
        for (const auto& p : inventory.getAll()) {
            if (p.getprice() >= minP && p.getprice() <= maxP)
                p.display();
        }

    } else if (choice == 4) {
        int minS, maxS;
        std::cout << "Enter min stock: "; std::cin >> minS;
        std::cout << "Enter max stock: "; std::cin >> maxS;
        for (const auto& p : inventory.getAll()) {
            if (p.getquantity() >= minS && p.getquantity() <= maxS)
                p.display();
        }

    } else {
        std::cout << "Invalid choice.\n";
    }
}

int main() {
    Inventory inventory;
    inventory.loadFromFile("data/products.txt");

    int option;
    do {
        std::cout << "\n====== Grocery Store Menu ======\n";
        std::cout << "1. View All Products\n";
        std::cout << "2. Search Products\n";
        std::cout << "3. Add Product\n";
        std::cout << "4. Delete Product\n";
        std::cout << "5. Save & Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << " Invalid input. Try again.\n";
            continue;
        }

        if (option == 1) {
            inventory.displayall();

        } else if (option == 2) {
            searchMenu(inventory);

        } else if (option == 3) {
            int id, qty;
            double price;
            std::string name;

            std::cout << "Enter product ID: ";
            std::cin >> id;
            if (inventory.searchbyId(id)) {
                std::cout << " Product ID already exists.\n";
                continue;
            }

            std::cout << "Enter name: ";
            std::cin >> name;

            std::cout << "Enter price: ";
            std::cin >> price;
            if (price < 0) { std::cout << " Price cannot be negative.\n"; continue; }

            std::cout << "Enter quantity: ";
            std::cin >> qty;
            if (qty < 0) { std::cout << " Quantity cannot be negative.\n"; continue; }

            Product p(id, name, price, qty);
            inventory.addproduct(p);
            std::cout << " Product added.\n";

        } else if (option == 4) {
            int id;
            std::cout << "Enter product ID to delete: ";
            std::cin >> id;
            if (inventory.deleteproduct(id)) {
                std::cout << " Product deleted.\n";
            } else {
                std::cout << " Product not found.\n";
            }

        } else if (option == 5) {
            inventory.saveToFile("data/products.txt");
            std::cout << " Inventory saved. Exiting...\n";

        } else {
            std::cout << " Invalid option.\n";
        }

    } while (option != 5);

    return 0;
}
