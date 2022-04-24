#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "library1.h"
#include <stdio.h>


class EmployeeManager {
    AvlTree <shared_ptr<Company >> companies;
    AvlTree <shared_ptr<Employee>*> allEmployees;


public:
    EmployeeManager();

    StatusType AddCompany(int CompanyID, int Value);

    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveEmployee(int EmployeeID);
};

#endif
