#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include "employee.hpp"

using namespace std;

class Manager : public Employee {
    public:
        Manager() : Employee() {}
        
        Manager(const string& name, const string& employee_id) : Employee(name, employee_id) {}
        
        
};




#endif