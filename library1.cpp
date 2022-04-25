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
    return ((EmployeeManager*)DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade);

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
    return ((EmployeeManager*)DS)->RemoveEmployee(EmployeeID);


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
    return ((EmployeeManager*)DS)->AddCompany(CompanyID, Value);
}




