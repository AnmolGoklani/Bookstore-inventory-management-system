#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>
#include <string>

using namespace std;

class Customer{
    private:
        string name;
        string email;
        int points;
    
    public:
        Customer() : name(""), email(""), points(0) {}

        Customer(const string& name, const string& email, const int& points){
            this->name = name;
            this->email = email;
            this->points = points;
        }

        // function to handle customer login
        int checkCredentials(const string& name, const string& email){
            return (this->name == name && this->email == email);
        }

        string getEmail() const {
            return email;
        }

        string getName() const {
            return name;
        }

        int getPoints() const {
            return points;
        }

        int setPoints(const int& points){
            this->points = points;
        }
};



#endif