#include "library1.h"
#include "EmployeeManager.h"

int main(){
    EmployeeManager * DS = static_cast<EmployeeManager *>(Init());

    AddCompany(DS ,1, 100);
    AddCompany(DS, 2, 200);
    AddEmployee(DS,10,1,10,1);
    AddEmployee(DS, 20, 2, 20, 2);


    return 0;
}