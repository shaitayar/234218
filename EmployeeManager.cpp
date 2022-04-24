#include "EmployeeManager.h"
using std::exception;


StatusType EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    try{
        company_by_id.insert(&company);
    }
    catch (exception& e) {

    }
}

StatusType EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    auto * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, c->obj);
}
