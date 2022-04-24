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
    AvlTree <Employee *, CompEmployeeById>  c_employee_by_id;
    AvlTree <Employee *, CompEmployeeBySalary>  c_employee_by_salary;

public:
    Company(int ID, int value): ID(ID), value(value), c_employee_by_id(CompEmployeeById()), c_employee_by_salary(CompEmployeeBySalary()){};
    ~Company()=default;
    int getID() const;
    int getValue() const;
    void setValue(int value);
    void addEmployee(Employee&);
    void RemoveEmployee(int employeeID);


};

class CompCompanyById{
public:
    int operator()(Company * c1, Company * c2) const{
        int id1 = c1->getID();
        int id2 = c2->getID();
        if (id1 > id2) return 1;
        else if (id1 < id2) return -1;
        else return 0;
    }rthgfh
};

#endif
