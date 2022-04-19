#include "EmployeeManager.h"

StatusType EmployeeManager::AddCompany(int CompanyID, int Value){
    StatusType * status;
    Company *company = new Company(CompanyID, Value);
    status = companies.insert()
}
