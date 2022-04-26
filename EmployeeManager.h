#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "employee.h"
#include "AvlTree.h"
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

    ~EmployeeManager();

    void AddCompany(int CompanyID, int Value);

    void AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

    void RemoveCompany(int EmployeeID);

    void RemoveEmployee(int EmployeeID);

    void GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

    void GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

    void print() const{
        employee_by_salary.print();
    }

    void IncreaseCompanyValue(int CompanyID, int ValueIncrease);


    void PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);


    void HireEmployee(int EmployeeID, int NewCompanyID);

    void AcquireCompany(int AcquirerID, int TargetID, double Factor);

    class EmException: public std::exception{};
    class EmFailure: public EmException{};
    class EmInvalidInput: public EmException{};
    class EmAllocationError: public EmException{};

};


#endif
