#ifndef INC_234218_COMPANY_H
#define INC_234218_COMPANY_H
#include <iostream>
#include "employee.h"
#include "AvlTree.h"
#include <memory>

using std::shared_ptr;
using std::string;

class Company{
    int ID;
    int value;
    AvlTree<shared_ptr<Employee> > employees;

public:
    Company(int ID, int value): ID(ID), value(value){};
    ~Company()=default;
    int getId() const;
    int getValue() const;
    void setValue(int value);
    StatusType addEmployee(const Employee&);
    StatusType RemoveEmployee(int employeeID);

};

#endif
