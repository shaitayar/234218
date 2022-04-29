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

void Company::TreeToArray(Employee ** empByIDTarget,Employee **empBySalaryTarget){
    c_employee_by_id.treeToArr(empByIDTarget);
    c_employee_by_salary.treeToArr(empBySalaryTarget);

}
void Company::ArrayToTree(Employee ** combinedID, Employee ** combinedSalary, int size){
    c_employee_by_id.arrToTree(combinedID, size);
    c_employee_by_salary.arrToTree(combinedSalary, size);
}