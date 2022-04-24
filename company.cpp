#include "company.h"

int Company::getID() const{
    return this->ID;
}

int Company::getValue() const{
    return this->value;
}

void Company::addEmployee(Employee *employee){
    try{
        c_employee_by_id.insert(employee);
    }
    catch (std::exception & e) {

    }
    c_employee_by_salary.insert(employee);
}