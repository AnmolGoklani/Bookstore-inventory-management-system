#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>
#include <string>
#include "person.hpp"

using namespace std;

class Customer : public Person {
    private:
        string email;
        int points;
    
    public:
        Customer() : Person(), email(""), points(0) {}
        
        Customer(const string& name, const string& email, const int& points): Person(name){
            this->email = email;
            this->points = points;
        }
        
        int checkCredentials(const string& name, const string& email){
            return (Person :: checkCredentials(name) && this->email == email);
        }
        
        string getEmail() const {
            return email;
        }

        int getPoints() const {
            return points;
        }
};



#endif