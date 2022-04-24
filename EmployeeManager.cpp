#include "EmployeeManager.h"

StatusType EmployeeManager::AddCompany(int CompanyID, int Value){
    StatusType *status = (StatusType *)SUCCESS;
    shared_ptr<Company> company (new Company(CompanyID, Value)) ;
    if(!company) return ALLOCATION_ERROR;

    companies.insert(company, status);
    if (*status==FAILURE){
        return *status;
    }
    return *status;
}

StatusType EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade) {
    StatusType *status = (StatusType *)SUCCESS;
    shared_ptr<Employee> employee ( new Employee(EmployeeID, Salary, Grade, CompanyID));
    if(!employee) return ALLOCATION_ERROR;
    shared_ptr<Employee> * pEmployee = &employee;

    /**find employee in AllEmployees*/
    allEmployees.insert(pEmployee,pEmployee->get()->getID(), status);
    if (*status==FAILURE){
        return *status;
    }

    /**find company in companies and insert employee*/
    shared_ptr<Company> company = *((companies.Find(CompanyID, status))->obj);
    if (*status==FAILURE){

        return *status;
    }
    else return company->addEmployee(*employee);
}

StatusType EmployeeManager::RemoveEmployee(int EmployeeID){
    return SUCCESS;
}


