#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "library1.h"
#include <stdio.h>


class EmployeeManager {
    AvlTree <Employee*, CompEmployeeById> employee_by_id;
    AvlTree <Employee*, CompEmployeeBySalary> employee_by_salary;
    AvlTree <Company*, CompCompanyById> company_by_id;



public:
    EmployeeManager(): employee_by_id(CompEmployeeById()), employee_by_salary(CompEmployeeBySalary()),
                       company_by_id(CompCompanyById()){};

    StatusType AddCompany(int CompanyID, int Value);

    StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveEmployee(int EmployeeID);
};

#endif
