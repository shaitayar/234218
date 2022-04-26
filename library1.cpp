#include "library1.h"
#include "EmployeeManager.h"


/***
 * Init - initializes empty Data Structure.
 */
void *Init() {
    EmployeeManager *DS = new EmployeeManager();
    return (void *) DS;
}


/***
 * AddCompany - Adds new company to DS, with unique ID and start Value.
 * @param DS- pointer to Data Structure
 * @param CompanyID- unique ID for the new company
 * @param Value- start Value for the company
 *
 * @return StatusType
 */

StatusType AddCompany(void *DS, int CompanyID, int Value) {
    if (DS == NULL || CompanyID <= 0 || Value <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AddCompany(CompanyID, Value);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

/***
 * AddEmployee -
 * @param DS- pointer to Data Structure
 * @param EmployeeID- ID for the new employee.
 * @param CompanyID- ID of the employees' company
 * @param Salary- start salary for the new employee
 * @param Grade- start grade of the new employee
 *
 * @return StatusType
 */
StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade) {
    if (DS == NULL || EmployeeID <= 0 || CompanyID <= 0 || Grade < 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;

}

StatusType RemoveCompany(void *DS, int CompanyID) {
    if (DS == NULL || CompanyID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->RemoveCompany(CompanyID);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

/***
 * RemoveEmployee -
 * @param DS- pointer to Data Structure
 * @param EmployeeID- ID for the new employee.
 *
 * @return StatusType
 */
StatusType RemoveEmployee(void *DS, int EmployeeID) {
    if (DS == NULL || EmployeeID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->RemoveEmployee(EmployeeID);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}


StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees) {
    if (DS == NULL || CompanyID <= 0 || Value == NULL || NumEmployees == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetCompanyInfo(CompanyID, Value, NumEmployees);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    if (DS == NULL || EmployerID == NULL || Salary == NULL || Grade == NULL || EmployeeID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease) {
    if (DS == NULL || CompanyID <= 0 || ValueIncrease <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade) {
    if (DS == NULL || EmployeeID <= 0 || SalaryIncrease <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID) {
    if (DS == NULL || EmployeeID <= 0 || NewCompanyID <= 0) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->HireEmployee(EmployeeID, NewCompanyID);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor) {
    if (DS == NULL || AcquirerID <= 0 || TargetID <= 0 || Factor <= 1.00 || TargetID == AcquirerID)
        return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->AcquireCompany(AcquirerID, TargetID, Factor);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID) {
    if (DS == NULL || CompanyID == 0 || EmployeeID == NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetHighestEarner(CompanyID, EmployeeID);
    }
    catch (const EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees) {
    if (DS == NULL || CompanyID == 0 || Employees == NULL || NumOfEmployees==NULL) return INVALID_INPUT;
    try {
        ((EmployeeManager *) DS)->GetAllEmployeesBySalary(CompanyId, Employees, NumOfEmployees);
    }
    catch (EmployeeManager::EmFailure &e) {
        return FAILURE;
    }
    return SUCCESS;
}


StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

void Quit(void **DS);