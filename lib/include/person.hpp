#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>

using namespace std;

class Person {
    private:
        string name;
    
    public:
        Person() : name("") {}
        Person(const string& name){
            this->name = name;
        }
        int checkCredentials(const string& name){
            return (this->name == name);
        }
        string getName() const {
            return name;
        }

};




#endif