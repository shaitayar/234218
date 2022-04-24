#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "library1.h"
#include <stdio.h>
#include "exception"

class EmployeeManager {
    CompEmployeeById ed;
    CompEmployeeBySalary es;
    CompCompanyById cd;
    AvlTree <Employee, CompEmployeeById> employee_by_id;
    AvlTree <Employee, CompEmployeeBySalary> employee_by_salary;
    AvlTree <Company, CompCompanyById> company_by_id;



public:
    EmployeeManager():ed(), es(),cd(), employee_by_id(ed), employee_by_salary(es),
                       company_by_id(cd){};

    StatusType AddCompany(int CompanyID, int Value);

    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveEmployee(int EmployeeID);

    void print() const{
        employee_by_salary.print();
    }

};


#endif
