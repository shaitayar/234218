#include "company.h"

Company::~Company(){
    c_employee_by_id.DestroyTree();
    c_employee_by_salary.DestroyTree();
}

int Company::getID() const{
    return this->ID;
}

int Company::getValue() const{
    return this->value;
}
int Company::getSize() const{
    return this->size;
}

int Company::getMax(){
    return max_sal_emp->obj->getID();
}


void Company::addEmployee(Employee *employee){
    c_employee_by_id.insert(employee);
    c_employee_by_salary.insert(employee);
    max_sal_emp = c_employee_by_salary.getMaxNode();
    size++;
}

void Company::setValue(int new_value)
{
    this->value += new_value;
}

void Company::setSize(int new_size)
{
    this->size += new_size;
}


void Company::RemoveEmployee(int employeeID)
{
    this->c_employee_by_id.deleteNode(employeeID);
    this->c_employee_by_salary.deleteNode(employeeID);
    size--;
    max_sal_emp = c_employee_by_salary.getMaxNode();

}

void Company::printToList(int ** arr){
    c_employee_by_salary.printToList(arr);
}

void Company::getMatchCompany(int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                              int MinGrade,
                              int *TotalNumOfEmployees, int *NumOfEmployees){
    c_employee_by_id.getMatch(MinEmployeeID, MaxEmployeeId, MinSalary,
                              MinGrade,TotalNumOfEmployees, NumOfEmployees);
}

void Company::EmptyCompany()
{
    this->c_employee_by_id.emptyTree();
    this->c_employee_by_salary.emptyTree();
    this->size = 0;
}


void Company::merge(Company** target,int new_value)
{
    int new_size = this->getSize() + (*target)->getSize();
    Employee** id_combined= new Employee*[new_size+1];
    Employee** salary_combined= new Employee*[new_size+1];
    if ((!id_combined)|| (!salary_combined))
        throw CmAllocationError();
    twoTreesToArray(&(this->c_employee_by_id), &((*target)->c_employee_by_id), &id_combined);
    twoTreesToArray(&(this->c_employee_by_salary), &((*target)->c_employee_by_salary), &salary_combined);
    this->c_employee_by_id.emptyTree();
    this->c_employee_by_salary.emptyTree();
    this->c_employee_by_id.arrayToTree(&id_combined,new_size+1);
    this->c_employee_by_salary.arrayToTree(&salary_combined,new_size+1);
    this->setSize(new_size);
    this->setValue(new_value);
}