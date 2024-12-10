#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include "employee.hpp"

using namespace std;

class Manager : public Employee {
    private:
        string name;
        string manager_id;
    public:
        Manager() {}

        Manager(const string& name, const string& manager_id) : name(name) , manager_id(manager_id) {}

        // function to handle manager login
        int checkCredentials(const string& name, const string& manager_id){
            return (this->name == name && this->manager_id == manager_id);
        }

        string getName() const {
            return name;
        }

        string getManagerId() const {
            return manager_id;
        }

        // restock an existing book
        void restockBook(const int& id, const int& stock){
            bool found = false;
            for(Book& book : Employee::books){
                if(book.getId() == id){
                    book.setStock(stock);
                    cout << book.getTitle() << " : " << book.getStock() << " copies" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Book with ID " << id << " not found." << endl;
            }
        }


        // restock an existing magazine
        void restockMagazine(const int& id, const int& stock){
            bool found = false;
            for(Magazine& magazine : Employee::magazines){
                if(magazine.getId() == id){
                    magazine.setStock(stock);
                    cout << magazine.getTitle() << " : " << magazine.getStock() << " copies" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Magazine with ID " << id << " not found." << endl;
            }
        }

        // add a new magazine
        void addMagazine(){
            string title, publisher, issue;
            double cost, price;
            int stock;
            cout << "Enter the title of the magazine: ";
            getline(cin >> ws, title);
            cout << "Enter the publisher of the magazine: ";
            getline(cin >> ws, publisher);
            cout << "Enter the cost of the magazine: ";
            cin >> cost;
            cout << "Enter the price of the magazine: ";
            cin >> price;
            cout << "Enter the number of copies to be added: ";
            cin >> stock;
            cout << "Enter the issue of the magazine: ";
            cin >> issue;
            Employee::magazines.push_back(Magazine(title, publisher, cost, price, stock, issue));
        }


        // add a new book
        void addBook(){
            string title, publisher, isbn, author;
            double cost, price;
            int stock, pages;
            Genre genre;
            cout << "Enter the title of the book: ";
            getline(cin >> ws, title);
            cout << "Enter the publisher of the book: ";
            getline(cin >> ws, publisher);
            cout << "Enter the cost of the book: ";
            cin >> cost;
            cout << "Enter the price of the book: ";
            cin >> price;
            cout << "Enter the number of copies to be added: ";
            cin >> stock;
            cout << "Enter the isbn of the book: ";
            cin >> isbn;
            cout << "Enter the author of the book: ";
            getline(cin >> ws, author);
            cout << "Enter the genre of the book( Fantasy, Horror, Mystery, Non Fiction, Science Fiction, Romance, Other ): ";
            string g;
            cin >> g;
            genre = stringToGenre(g);
            cout << "Enter the number of pages of the book: ";
            cin >> pages;
            for (const Book& book : Employee::books) {
                if (book.getIsbn() == isbn) {
                    cout << "Error: Book" << isbn << " already exists." << endl;
                    return;
                }
            }
            Employee::books.push_back(Book(title, publisher, cost, price, stock, isbn, author, genre, pages));
        }
        

        //delete a book
        void deleteBook(const int& id){
            bool found = false;
            for(int i = 0; i < Employee::books.size(); i++){
                if(Employee::books[i].getId() == id){
                    cout << Employee::books[i].getTitle() << " successfully deleted." << endl;
                    Employee::books.erase(Employee::books.begin() + i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Book with ID " << id << " not found." << endl;
            }
        }


        //delete a magazine
        void deleteMagazine(const int& id){
            bool found = false;
            for(int i = 0; i < Employee::magazines.size(); i++){
                if(Employee::magazines[i].getId() == id){
                    cout << Employee::magazines[i].getTitle() << " successfully deleted." << endl;
                    Employee::magazines.erase(Employee::magazines.begin() + i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Error: Magazine with ID " << id << " not found." << endl;
            }
        }
        
        //print all items in detail
        void printItems(){
            cout << "Books: " << endl;
            for(Book book : Employee::books){
                book.print();
            }
            cout << "Magazines: " << endl;
            for(Magazine magazine : Employee::magazines){
                magazine.print();
            }
        }

        //print all items with low stock so that the manager can restock them
        void printLowStock(){
            cout << "Books: " << endl;
            for(Book book : Employee::books){
                if(book.getStock() <= 5){
                    book.printManagerinfo();
                }
            }
            cout << "Magazines: " << endl;
            for(Magazine magazine : Employee::magazines){
                if(magazine.getStock() <= 5){
                    magazine.printManagerinfo();
                }
            }
        }

    
        void changeCost(int id, double cost){
            int found = 0;
            for(Book book : Employee::books){
                if(book.getId() == id){
                    //we do this instead of making a setter function because
                    // I didn't want cashier to be able to change the cost or price of any item 
                    // He has access to the items but he can't access the private attributes
                    // because Cashier is not a friend class of Item like Manager is
                    book.cost = cost;  
                    found = 1;
                    break;
                }
            }
            if(!found){
                for(Magazine magazine : Employee::magazines){
                    if(magazine.getId() == id){
                        magazine.cost = cost;
                        found = 1;
                        break;
                    }
                }
            }

            if(!found){
                cout << "Item with id " << id << " not found." << endl;
            }
        }

        void changePrice(int id, double price){
            int found = 0;
            for(Book book : Employee::books){
                if(book.getId() == id){
                    book.price = price;  
                    found = 1;
                    break;
                }
            }
            if(!found){
                for(Magazine magazine : Employee::magazines){
                    if(magazine.getId() == id){
                        magazine.price = price;
                        found = 1;
                        break;
                    }
                }
            }

            if(!found){
                cout << "Item with id " << id << " not found." << endl;
            }
        }
        
};




#endif