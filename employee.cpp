#include "employee.h"
#include <iostream>


int Employee::getID() const {
    return this->ID;
}

int Employee::getSalary() const {
    return this->salary;
}

int Employee::getGrade() const {
    return this->grade;
}


/*
class CompEmployeeById {
public:
    int operator()(Employee * e1, Employee * e2) const{
        int id1 = e1->getID();
        int id2 = e2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

    int operator()(const Employee * e1, int id2) const{
        int id1 = e1->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

};

*/