#ifndef CASHIER_HPP
#define CASHIER_HPP

#include <iostream>
#include <string>
#include "employee.hpp"

using namespace std;

class Cashier : public Employee {
    private:
        vector <Item> cart;
    public:
        void printBooksByAuthor(string author){
            transform(author.begin(), author.end(), author.begin(), ::toupper);
            int found = 0;
            for (Book book : Employee::books) {
                string book_author = book.getAuthor();
                transform(book_author.begin(), book_author.end(), book_author.begin(), ::toupper);
                if(book_author == author){
                    found = 1;
                    book.printCustomerInfo();
                }
            }
            if(!found){
                cout << "No books found by " << author << endl;
            }
        }

        void printBooksByGenre(const Genre& genre){
            int found = 0;
            for (Book book : Employee::books) {
                if(book.getGenre() == genre){
                    book.printCustomerInfo();
                    found = 1;
                }
            }

            if(!found){
                cout << "No books found in this genre." << endl;
            }
        }

        void addBookByIsbn(const string& isbn){
            int found = 0;
            for (Book book : Employee::books) {
                if(book.getIsbn() == isbn  && book.getStock()){
                    addBookToCart(book.getId());
                    found = 1;
                    break;
                }
            }
            if(!found){
                cout << "Book with this isbn: " << isbn << " is unavailable." << endl;
            }
        }

        void addBookByTitleAuthor(const string& title, const string& author){
            int found = 0;
            for (Book book : Employee::books) {
                if(book.getTitle() == title && book.getAuthor() == author && book.getStock()){
                    addBookToCart(book.getId());
                    found = 1;
                    break;
                }
            }
            if(!found){
                cout << title << " by " << author << " is unavailable." << endl;
            }
        }

        void printMagazines(){
            for (Magazine magazine : Employee::magazines) {
                magazine.printCustomerInfo();
            }
        }

        void addBookToCart(const int& id){
            for(Book book : Employee::books){
                if(book.getId() == id  && book.getStock()){
                    cart.push_back(book);
                    cout << book.getTitle() << " successfully added to your cart." << endl;
                    break;
                }
                else{
                    cout << book.getTitle() << " not available." << endl;
                }
            }
        }

        void addMagazineToCart(const int& id){
            for(Magazine magazine : Employee::magazines){
                if(magazine.getId() == id  && magazine.getStock()){
                    cart.push_back(magazine);
                    cout << magazine.getTitle() << " successfully added to your cart." << endl;
                    break;
                }
            }
        }

        void displayCart(){
            cout << endl << "Items in your cart: " << endl;
            for(Item item : cart){
                cout << item.getId() << " -> " << item.getTitle() <<  item.getPrice() << endl;
            }
        }

        void removeItemFromCart(const int& id){
            int found = 0;
            for(int i = 0; i < cart.size(); i++){
                if(cart[i].getId() == id){
                    cout << cart[i].getTitle() << " successfully removed from your cart." << endl;
                    cart.erase(cart.begin() + i);
                    found = 1;
                    break;
                }
            }
            if(!found){
                cout << "Item not found in cart." << endl;
            }
        }

        void checkout(Customer& customer){
            double total = 0;
            for(Item item : cart){
                total += item.getPrice();
            }
            cout << "Total amount to be paid: " << total << endl;
            cout << "Points in card: " << customer.getPoints() << endl;
            if(total >= 500.00){
                total -= (double)(customer.getPoints());
                cout << "Total after using points:" << total << endl;
            }
            else{
                cout << "Add items worth " << 500.00 - total << " to redeem your points." << endl;
            }
            cout << "Press 1 to confirm order, any other key to cancel: ";
            int opt;
            cin >> opt;
            if(opt == 1){
                cout << "Thank you for shopping with us!" << endl;
                cout << "You got " << (int)(total/100) << " points for this purchase!" << endl;
                customer.setPoints((int)(total/100));
                for(Item item : cart){
                    item.setStock(item.getStock() - 1);
                    profit += item.getPrice() - item.getCost();
                }
            }
        
            cart.clear();
        }
        
};


#endif