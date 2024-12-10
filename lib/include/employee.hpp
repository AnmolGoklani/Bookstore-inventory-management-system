#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <string>
#include "person.hpp"
#include "book.hpp"
#include "magazine.hpp"
#include <vector>
#include <fstream>

using namespace std;

class Employee : public Person {
    private:
        string employee_id;

    protected:
        static vector<Book> books;
        static vector<Magazine> magazines;
    
    public:
        Employee() : Person(), employee_id("") {}

        Employee(const string& name, const string& employee_id) : Person(name){
            this->employee_id = employee_id;
        }

        int checkCredentials(const string& name, const string& employee_id){
            return (Person :: checkCredentials(name) && this->employee_id == employee_id);
        }

        string getEmployeeId() const {
            return employee_id;
        }

        void save_books(ofstream& file){
            for (Book book : books) {
                file << book.getTitle() << endl;
                file << book.getPublisher() << endl;
                file << book.getCost() << endl;
                file << book.getPrice() << endl;
                file << book.getStock() << endl;
                file << book.getIsbn() << endl;
                file << book.getAuthor() << endl;
                file << book.genreToString() << endl;
                file << book.getPages() << endl;
            }
        }

        void save_magazines(ofstream& file){
            for (Magazine magazine : magazines) {
                file << magazine.getTitle() << endl;
                file << magazine.getPublisher() << endl;
                file << magazine.getCost() << endl;
                file << magazine.getPrice() << endl;
                file << magazine.getStock() << endl;
                file << magazine.getIssue() << endl;
            }
        }

        void load_books(ifstream& file){
            string title, publisher, cost, price, stock, isbn, author, genre, pages;
            while (getline(file, title) && !file.eof()) {
                getline(file, publisher);
                getline(file, cost);
                getline(file, price);
                getline(file, stock);
                getline(file, isbn);
                getline(file, author);
                getline(file, genre);
                getline(file, pages);
                books.push_back(Book(title, publisher, stod(cost), stod(price), stoi(stock), isbn, author, stringToGenre(genre), stoi(pages)));
            }
        }

        void load_magazines(ifstream& file){
            string title, publisher, cost, price, stock, issue;
            while (getline(file, title) && !file.eof()) {
                getline(file, publisher);
                getline(file, cost);
                getline(file, price);
                getline(file, stock);
                getline(file, issue);
                magazines.push_back(Magazine(title, publisher, stod(cost), stod(price), stoi(stock), issue));
            }
        }
};

vector<Book> Employee::books;
vector<Magazine> Employee::magazines;

#endif