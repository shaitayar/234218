#include "employee.h"
#include <iostream>


Employee::Employee(int ID, int salary, int grade): ID(ID), salary(salary), grade(grade) {

}

int Employee::getID() const {
    return this->ID;
}

int Employee::getSalary() const {
    return this->salary;
}

int Employee::getGrade() const {
    return this->grade;
}

