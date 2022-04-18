#include "library1.h"
#include "EmployeeManager.h"

void * Init(){
    EmployeeManager * DS = new EmployeeManager();
    return (void*) DS;
}
StatusType AddCompany(void * DS, int CompanyID, int Value){
    if (DS==NULL) return INVALID_INPUT;
    return ((EmployeeManager*)DS)->AddCompany(CompanyID, Value);
}

