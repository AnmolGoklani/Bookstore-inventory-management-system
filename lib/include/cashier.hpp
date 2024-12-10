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
        Cashier() : Employee() {}

        Cashier(const string& name, const string& employee_id) : Employee(name, employee_id) {}

        void printBooksByAuthor(string author){
            transform(author.begin(), author.end(), author.begin(), ::toupper);
            for (Book book : Employee::books) {
                string book_author = book.getAuthor();
                transform(book_author.begin(), book_author.end(), book_author.begin(), ::toupper);
                if(book_author == author){
                    book.printCustomerInfo();
                }
            }
        }

        void printBooksByGenre(const Genre& genre){
            for (Book book : Employee::books) {
                if(book.getGenre() == genre){
                    book.printCustomerInfo();
                }
            }
        }

        void printMagazines(){
            for (Magazine magazine : Employee::magazines) {
                magazine.printCustomerInfo();
            }
        }

        void addBookToCart(const int& id){
            for(Book book : Employee::books){
                if(book.getId() == id){
                    cart.push_back(book);
                    cout << book.getTitle() << " successfully added to your cart." << endl;
                    break;
                }
            }
        }

        void addMagazineToCart(const int& id){
            for(Magazine magazine : Employee::magazines){
                if(magazine.getId() == id){
                    cart.push_back(magazine);
                    cout << magazine.getTitle() << " successfully added to your cart." << endl;
                    break;
                }
            }
        }
        
};


#endif