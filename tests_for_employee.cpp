#include "EmployeeManager.h"

int main(){
    EmployeeManager ds;
    ds.AddCompany(1,10);
    ds.AddCompany(2,20);
    ds.AddEmployee(1,2,100,1);
    ds.AddEmployee(2,2,200,2);
    ds.AddEmployee(5,2,500,5);

    ds.print();
    return 0;
}