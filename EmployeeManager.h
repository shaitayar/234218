#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "library1.h"
#include <stdio.h>


class EmployeeManager {
    AvlTree <Employee*, ID> employee_by_id;
    AvlTree <Employee*, Salary> employee_by_salary;
    AvlTree <Company*, ID> company_by_id;
    AvlTree <Company*, ID> company_not_empty_by_id;



public:
    EmployeeManager();

    StatusType AddCompany(int CompanyID, int Value);

    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveEmployee(int EmployeeID);
};

#endif
