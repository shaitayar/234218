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

void Company::addEmployee(Employee *employee){
    c_employee_by_id.insert(employee);
    c_employee_by_salary.insert(employee);
    size++;
}

void Company::setValue(int new_value)
{
    this->value = new_value
}

void Company::RemoveEmployee(int employeeID)
{
    this->c_employee_by_id.deleteNode(employeeID);
    this->c_employee_by_salary.deleteNode(employeeID);
    size--;
}