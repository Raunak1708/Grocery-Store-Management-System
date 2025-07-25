#include <iostream>
#include "../include/product.h"
#include "../include/inventory.h"
#include "../include/cart.h"    
#include "../include/lendingledger.h"      
using namespace std;
double totalRevenue = 0;
int orderCount = 0;
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iomanip>

std::string getCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
    return std::string(buf);
}

std::string generateOrderID(int orderCount) {
    std::ostringstream oss;
    oss << "ORD" << std::setw(3) << std::setfill('0') << orderCount + 101;
    return oss.str();
}
int main(){
    Inventory inv;
    Cart cart;
    LendingLedger ledger;
    inv.loadFromFile("data/products.txt");
    int choice;
   do {
        std::cout << "\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Remove from Cart\n5. View Total\n6. Checkout\n7.Manager Report\n8.Lend Products (Pay Later)\n9. View Borrowed Items\n10.Repay Borrowed Amount\n11.List all Borrowers\n12. Exit\nChoice: ";
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
                cart.additem(*p,qty);
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
        else if(choice==6){
            if(cart.isempty()){
                cout<<"Your Cart is Empty"<<endl;
                continue;
            }
                cout<<"Please check items on the cart";
                cart.viewcart(); 
                cout<<"Proceed to Checkout(y/n)"<<endl;
                char confirm;
                cin>>confirm;
                if(confirm!='y'&&confirm!='Y'){
                    continue;
                }
                double billamount =cart.totalamount();
                string timestamp=getCurrentTimestamp();
                string orderID=generateOrderID(orderCount);
                for(const auto &i:cart.getItems()){
                    Product *invProd=inv.searchbyId(i.getid());
                    if(invProd){
                        int updateqty=invProd->getquantity()-i.getquantity();
                        invProd->setquantity(updateqty);
                    }
                }
                inv.saveToFile("data/products.txt");
                 // Save receipt to file
    std::ofstream receiptFile("receipt_" + orderID + ".txt");
    receiptFile << " Receipt — Order ID: " << orderID << "\n";
    receiptFile << "Date/Time: " << timestamp << "\n\n";
    receiptFile << std::left << std::setw(12) << "Item"
            << std::right << std::setw(6) << "Qty"
            << std::setw(10) << "Price"
            << std::setw(12) << "Total" << "\n";
    receiptFile << "----------------------------------------------\n";

  for (const auto& item : cart.getItems()) {
    receiptFile << std::left << std::setw(12) << item.getname()
                << std::right << std::setw(6) << item.getquantity()
                << std::setw(10) << std::fixed << std::setprecision(2) << item.getprice()
                << std::setw(12) << std::fixed << std::setprecision(2)
                << (item.getprice() * item.getquantity())
                << "\n";
}

receiptFile << "----------------------------------------------\n";
receiptFile << std::right << std::setw(28) << "Grand Total: Rs. "
            << std::setw(12) << std::fixed << std::setprecision(2) << billamount << "\n";
    receiptFile << "\nThank you for shopping with us!\n";
    receiptFile.close();

    std::cout << "\nCheckout complete. Receipt saved as receipt_" << orderID << ".txt\n";

    totalRevenue += billamount;
    orderCount++;
    cart.clearCart();
        }
        else if(choice ==7){
                cout << "\n===== Manager Report =====\n";
      cout << "Total Orders Today: " << orderCount << "\n";
    std::cout << "Total Revenue: Rs. " << totalRevenue << "\n";

    std::ofstream summary("summary.txt", std::ios::app);
    summary << "\nDate: " << getCurrentTimestamp() << "\n";
    summary << "Orders: " << orderCount << ", Revenue: Rs. " << totalRevenue << "\n";
    summary.close();
        }
       else if(choice==8){
        string name;
cout << "Enter borrower name: ";
cin.ignore();
getline(cin, name);

int id, qty;
cout << "Enter product ID: ";
cin >> id;
Product* p = inv.searchbyId(id);
if (!p) { cout << "Not found\n"; continue; }

cout << "Enter quantity: ";
cin >> qty;
if (qty <= 0 || qty > p->getquantity()) {
    cout << "Invalid quantity\n";
} else {
    ledger.lendProduct(name, *p, qty);
    p->setquantity(p->getquantity() - qty);
    inv.saveToFile("products.txt");  
    cout << "Lent to " << name << ". Total due: " << ledger.getDue(name) << "\n";
}

       }
       else if(choice==9){
        string name;
cout << "Enter borrower name: ";
cin.ignore();
getline(cin, name);
ledger.viewBorrowed(name);

       }
       else if(choice==10){
        string name;
        
cout << "Enter borrower name to repay: ";
cin.ignore();
getline(cin, name);
cout<<"Amount Due: "<<ledger.getDue(name)<<endl;
int amount;
cout<<"Enter amount you are paying now: ";
cin>>amount;
if (!ledger.hasBorrowed(name)) {
    cout << "No dues.\n";
} else {
    ledger.repay(name,amount);
    if(ledger.getDue(name)){
        cout<<"Dues Left : "<<ledger.getDue(name)<<endl;
    }
    else{
    cout << " Dues cleared for " << name << "\n";
    }
}

       }
       else if(choice==11){
        for (const auto& name : ledger.getAllBorrowers()) {
    cout << name << ": Rs. " << ledger.getDue(name) << "\n";
}

       }
    } while (choice != 12);

    return 0;
}