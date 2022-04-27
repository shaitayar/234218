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
}

void Company::setValue(int new_value)
{
    this->value = value+new_value;
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
