#include "EmployeeManager.h"
using std::exception;


StatusType EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    try{
        company_by_id.insert(company);
    }
    catch (exception& e) {

    }
    return SUCCESS;
}

StatusType EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    Node<Company , CompCompanyById> * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, shared_ptr<struct Company>((c->obj)));
    try{
        employee_by_id.insert(employee);
    }
    catch (exception& e) {

    }
    employee_by_salary.insert(employee);
    (c->obj)->addEmployee(employee);

    return SUCCESS;
}
