#include "library1.h"
#include "EmployeeManager.h"


/***
 * Init - initializes empty Data Structure.
 */
void * Init(){
    EmployeeManager * DS = new EmployeeManager();
    return (void*) DS;
}


/***Employee Implementations*/

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
StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade){
    if (DS==NULL || EmployeeID<=0 || CompanyID<=0 || Grade<0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);
    }
    catch (EmployeeManager::EmFailure& e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError& e) {
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
StatusType RemoveEmployee(void *DS, int EmployeeID){
    if(DS==NULL || EmployeeID<=0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->RemoveEmployee(EmployeeID);
    }
    catch (EmployeeManager::EmFailure& e) {
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}


/***Company Implementations*/


/***
 * AddCompany - Adds new company to DS, with unique ID and start Value.
 * @param DS- pointer to Data Structure
 * @param CompanyID- unique ID for the new company
 * @param Value- start Value for the company
 *
 * @return StatusType
 */

StatusType AddCompany(void * DS, int CompanyID, int Value){
    if (DS==NULL || CompanyID<=0 || Value<=0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->AddCompany(CompanyID, Value);
    }
    catch(const EmployeeManager::EmFailure & e){
        return FAILURE;
    }
    catch (EmployeeManager::EmAllocationError& e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    if (DS==NULL || EmployerID==NULL || Salary==NULL || Grade==NULL ||EmployeeID<=0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade);
    }
    catch (EmployeeManager::EmFailure& e) {
        return FAILURE;
    }
    return SUCCESS;
}



StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
    if (DS==NULL || EmployeeID<=0 || SalaryIncrease<=0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
    }
    catch (EmployeeManager::EmFailure& e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){
    if(DS==NULL || EmployeeID<=0 || NewCompanyID<=0) return INVALID_INPUT;
    try{
        ((EmployeeManager*)DS)->HireEmployee(EmployeeID, NewCompanyID);
    }

}