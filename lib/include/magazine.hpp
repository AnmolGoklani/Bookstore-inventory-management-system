#ifndef MAGAZINE_HPP
#define MAGAZINE_HPP

#include <iostream>
#include <string>
#include "item.hpp"

using namespace std;

class Magazine : public Item {
    private:
        string issue;

    public:
        Magazine() : Item(), issue("") {}
        Magazine(const string& title, const string& publisher, const double& cost, const double& price, const int& stock, const string& issue) : Item(title, publisher, cost, price, stock) {
            this->issue = issue;
        }
        void print(){
            Item::print();
            cout << "Issue: " << this->issue << endl;
        }
        void printCustomerInfo(){
            Item::printCustomerInfo();
            if(getStock()) cout << "Issue: " << this->issue << endl;
        }
        string getIssue() const {
            return issue;
        }

        
};


#endif