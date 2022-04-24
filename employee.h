#ifndef INC_234218_EMPLOYEE_H
#define INC_234218_EMPLOYEE_H

#include <iostream>
using std::string;
using std::ostream;

class Employee{
    int ID;
    int salary;
    int grade;

public:
    Employee(int ID, int salary, int grade): ID(ID), salary(salary), grade(grade){};
    ~Employee()=default;
    int getID() const;
    int getSalary() const;
    int getGrade() const;

    //Maybe add setters
};

class CompEmployeeById {
public:
    int operator()(Employee * e1, Employee * e2) const{
        int id1 = e1->getID();
        int id2 = e2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }
/*
    int operator()(const Employee * e1, int id2) const{
        int id1 = e1->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }
*/
};

#endif
