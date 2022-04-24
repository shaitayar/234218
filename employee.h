#ifndef INC_234218_EMPLOYEE_H
#define INC_234218_EMPLOYEE_H

#include <iostream>
using std::string;
using std::ostream;

class Employee{
    int ID;
    int salary;
    int grade;
    int CompanyID;

public:
    Employee(int ID, int salary, int grade, int CompanyID): ID(ID), salary(salary), grade(grade),CompanyID(CompanyID){};
    ~Employee()=default;
    int getID() const;
    int getSalary() const;
    int getGrade() const;
    int getCompany() const;

    //Maybe add setters
};

#endif
