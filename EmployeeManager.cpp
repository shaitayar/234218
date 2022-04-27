#include "EmployeeManager.h"
using std::exception;

EmployeeManager::~EmployeeManager(){
    employee_by_id.DestroyTree();
    employee_by_salary.DestroyTree();
    company_by_id.DestroyTree();
}

void EmployeeManager::AddCompany(int CompanyID, int Value){
    if(company_by_id.find(CompanyID)!=NULL)
        throw EmFailure();
    Company * company = new Company(CompanyID, Value);
    if (!company) throw EmAllocationError();
    company_by_id.insert(company);
}

void EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade){
    if (employee_by_id.find(EmployeeID)!=NULL)
        throw EmFailure();
    Node<Company , CompCompanyById> * c = company_by_id.find(CompanyID);
    Employee * employee = new Employee(EmployeeID, Salary, Grade, (c->obj));
    if(!employee) throw EmAllocationError();
    employee_by_id.insert(employee);
    employee_by_salary.insert(employee);
    (c->obj)->addEmployee(employee);
}

void EmployeeManager::RemoveEmployee(int EmployeeID){
    auto node = employee_by_id.find(EmployeeID);
    Employee * employee = node->obj;
    Company * company = employee->getCompany();
    employee_by_id.deleteNode(EmployeeID);
    company->RemoveEmployee(EmployeeID);

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
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee * emp = node->obj;
    Company * company1 = emp->getCompany();
    auto n_company = company_by_id.find(NewCompanyID);
    if (!n_company) throw EmFailure();
    Company * company2 = n_company->obj;

    //remove from company 1 and add to company 2
    emp->setCompany(company2);
    company1->RemoveEmployee(EmployeeID);
    company2->addEmployee(emp);
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
    auto node = company_by_id.find(CompanyID);
    if (!node)
        throw EmFailure();
    int curr_value = node->obj->getValue();
    node->obj->setValue(curr_value+ValueIncrease);
}



void EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    auto acquirer = company_by_id.find(AcquirerID);
    auto target = company_by_id.find(TargetID);
    if ((!acquirer)||(!target))
        throw EmFailure();
    int target_value = target->obj->getValue();
    int acquirer_value = acquirer->obj->getValue();
    if (acquirer_value<(10*target_value))
        throw EmFailure();
    double new_value = (acquirer->obj->getValue() +target->obj->getValue())*Factor;
    Company* temp = new Company(acquirer->obj->getID(), int(new_value));
    if (!temp)
        throw EmAllocationError();
    acquirer->obj->merge(target, temp);
    this->RemoveCompany(TargetID);
}