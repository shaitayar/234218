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

#endif
