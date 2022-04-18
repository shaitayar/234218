#include "employee.h"
#include <iostream>


int Employee::getID() const{
    return this->ID;
}
int Employee::getSalary() const{
    return this->salary;
}
int Employee::getGrade() const{
    return this->grade;
}