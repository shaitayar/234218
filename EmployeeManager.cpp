#include "EmployeeManager.h"
using std::exception;

EmployeeManager::~EmployeeManager(){
    employee_by_id.DestroyTree();
    employee_by_salary.DestroyTree();
    company_by_id.DestroyTree();
}

void EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    if (!company) throw EmAllocationError();
    if(company_by_id.find(CompanyID)!=NULL) throw EmFailure();
    company_by_id.insert(company);
}

void EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    Node<Company , CompCompanyById> * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, (c->obj));
    if(!employee) throw EmAllocationError();
    if (employee_by_id.find(EmployeeID)!=NULL){
        throw EmFailure();
    }
    employee_by_id.insert(employee);
    employee_by_salary.insert(employee);
    (c->obj)->addEmployee(employee);
}

void EmployeeManager::RemoveEmployee(int EmployeeID){
    auto node = employee_by_id.find(EmployeeID);
    Employee * employee = node->obj;
    Company * company = employee->getCompany();
    employee_by_id.deleteNode(EmployeeID);
    //company->RemoveEmployee(EmployeeID);

}

void EmployeeManager::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee * emp = node->obj;
    Company * comp = emp->getCompany();
    *EmployerID = comp->getID();
    *Salary = emp->getSalary();
    *Grade = emp->getGrade();
}

void EmployeeManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade){
    auto node = employee_by_id.find(EmployeeID);
    if(!node) throw EmFailure();
    Employee * emp = node->obj;
    emp->setSalary(SalaryIncrease);
    if (BumpGrade>0){
        emp->setGrade();
    }
}


void EmployeeManager::HireEmployee(int EmployeeID, int NewCompanyID){

}


