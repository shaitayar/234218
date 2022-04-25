#include "EmployeeManager.h"
using std::exception;

EmployeeManager::~EmployeeManager(){
    employee_by_id.DestroyTree();
    employee_by_salary.DestroyTree();
    company_by_id.DestroyTree();
}

void EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    if(company_by_id.find(CompanyID)!=NULL) throw EmFailure();
    company_by_id.insert(company);
}

void EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    Node<Company , CompCompanyById> * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, (c->obj));
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

void EmployeeManager::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees)
{
    if ((!Value)||(!NumEmployees)||(CompanyID<=0))
        throw EmInvalidInput();
    auto node = company_by_id.find(CompanyID);
    if (!node)
        throw EmFailure();
    *Value = node->obj->getValue();
    *NumEmployees = node->obj->getSize();
}

void EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
    if ((CompanyID<=0)|| (ValueIncrease <=0))
        throw EmInvalidInput();
    auto node = company_by_id.find(CompanyID)
    if (!node)
        throw EmFailure();
    int curr_value = node->obj->getValue();
    node->obj->setValue(curr_value+ValueIncrease);
}

void EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    if ((AcquirerID<=0)||(TargetID<=0)||(AcquirerID==TargetID)||(Factor<1))
        throw EmInvalidInput();
    auto acquirer = company_by_id.find(AcquirerID);
    auto target = company_by_id.find(TargetID);
    if ((!acquirer) || (!target))
        throw EmFailure();
    int condition = 10*(target->obj->getValue());
    if (acquirer < condition)
        throw EmFailure();

}