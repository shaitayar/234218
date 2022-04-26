#ifndef INC_234218_COMPANY_H
#define INC_234218_COMPANY_H

#include <iostream>
#include "employee.h"
#include "AvlTree.h"
#include <memory>

using std::shared_ptr;
using std::string;


class Company {
    int ID;
    int value;
    int size;
    CompEmployeeById ed;
    CompEmployeeBySalary es;
    AvlTree<Employee, CompEmployeeById> c_employee_by_id;
    AvlTree<Employee, CompEmployeeBySalary> c_employee_by_salary;

public:
    Company(int ID, int value) : ID(ID), value(value), size(0), ed(), es(), c_employee_by_id(ed),
                                 c_employee_by_salary(es) {};

    ~Company();

    int getID() const;

    int getValue() const;

    int getSize() const;

    void setValue(int value);

    void addEmployee(Employee *);

    void RemoveEmployee(int employeeID);

    void print() const{
        std::cout<<getID()<<std::endl;
    }
};

class CompCompanyById {
public:
    int operator()(Company *c1, Company *c2) const {
        int id1 = c1->getID();
        int id2 = c2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }

    int operator()(Company *c1, int id2) const {
        int id1 = c1->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }
};

#endif
