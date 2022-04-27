#include "EmployeeManager.h"
using std::exception;

EmployeeManager::~EmployeeManager(){
    employee_by_id.DestroyTree();
    employee_by_salary.DestroyTree();
    company_by_id.DestroyTree();
    company_not_empty.DestroyTree();

}

void EmployeeManager::AddCompany(int CompanyID, int Value){
    Company * company = new Company(CompanyID, Value);
    if (!company) throw EmAllocationError();
    if(company_by_id.find(CompanyID)!=NULL) throw EmFailure();
    company_by_id.insert(company);
    company_num++;
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
    employee_num++;
    max_employee = employee_by_salary.getMaxNode();
    company_not_empty.insert(c->obj);
}

void EmployeeManager::RemoveEmployee(int EmployeeID){
    auto node = employee_by_id.find(EmployeeID);
    Employee * employee = node->obj;
    Company * company = employee->getCompany();
    employee_by_id.deleteNode(EmployeeID);
    company->RemoveEmployee(EmployeeID);

    delete employee;
    max_employee = employee_by_salary.getMaxNode();
    if (company->getSize()==0) company_not_empty.deleteNode(company->getID());
}

void EmployeeManager::RemoveCompany(int CompanyID){
    auto comp = company_by_id.find(CompanyID);
    if (!comp) throw EmFailure();
    Company * company = comp->obj;

    //If company has workers
    if (company->getSize()!=0) throw EmFailure();
    company_by_id.deleteNode(CompanyID);
    company_not_empty.deleteNode(CompanyID);
    delete company;
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
    if (node==NULL) throw EmFailure();
    *Value = node->obj->getValue();
    *NumEmployees = node->obj->getSize();
}

void EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
    if ((CompanyID<=0)|| (ValueIncrease <=0))
        throw EmInvalidInput();
    auto node = company_by_id.find(CompanyID);
    if (node==NULL)
        throw EmFailure();
    int curr_value = node->obj->getValue();
    node->obj->setValue(curr_value+ValueIncrease);
}

void EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    return;
}

void EmployeeManager::GetHighestEarner(int CompanyID, int *EmployeeID){
    if (CompanyID<0){
        *EmployeeID = max_employee->obj->getID();
    }
    else if (CompanyID>0){
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company * comp = node->obj;
        *EmployeeID = comp->getMax();
    }
}

void EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees){
    if (CompanyID<0){
        *Employees = (int*)std::malloc(employee_num*sizeof(int));
        if(!Employees) throw EmAllocationError();
        employee_by_salary.printToList(Employees);
        *NumOfEmployees=employee_num;
    }
    else if(CompanyID>0){
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company * comp = node->obj;
        *Employees = (int*)std::malloc(comp->getSize()*sizeof(int));
        if(!Employees) throw EmAllocationError();
        comp->printToList(Employees);
        *NumOfEmployees = comp->getSize();
    }
}

void EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees){
    if (company_not_empty.getSize()<NumOfCompanies) throw EmFailure();
    *Employees = (int*)std::malloc(NumOfCompanies*sizeof(int));
    if(!Employees) throw EmAllocationError();

    company_not_empty.getNMax(NumOfCompanies, Employees);
}

