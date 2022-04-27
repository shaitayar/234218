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
    this->value = new_value;
}

void Company::RemoveEmployee(int employeeID)
{
    this->c_employee_by_id.deleteNode(employeeID);
    this->c_employee_by_salary.deleteNode(employeeID);
    size--;
}


void Company::merge(Company* target,Company* temp)
{
    int new_size = this->getSize() + target->getSize();
    Employee** combined= new Employee*[new_size+1];
    if (!combined)
        throw EmAllocationError();
    treesToArray(this->c_employee_by_id, target->c_employee_by_id, combined);
    arrayToTree(combined, new_size+1, temp->c_employee_by_id);
    delete this->c_employee_by_id;
    treesToArray(this->c_employee_by_salary, target->c_employee_by_salary, combined);
    arrayToTree(combined, new_size+1, temp->c_employee_by_salary);
    delete this->c_employee_by_salary;
    this->c_employee_by_id = temp->c_employee_by_id;
    this->c_employee_by_salary = temp->c_employee_by_salary;
    this->setSize(new_size);
    this->setValue(temp->getValue());
}