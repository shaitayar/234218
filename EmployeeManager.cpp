#include "EmployeeManager.h"
using std::exception;


StatusType EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    if(company_by_id.find(CompanyID)!=NULL) return FAILURE;
    company_by_id.insert(company);

    return SUCCESS;
}

StatusType EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    Node<Company , CompCompanyById> * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, shared_ptr<struct Company>((c->obj)));
    if (employee_by_id.find(EmployeeID)!=NULL){
        return FAILURE;
    }
    employee_by_id.insert(employee);
    employee_by_salary.insert(employee);
    (c->obj)->addEmployee(employee);
    return SUCCESS;
}
