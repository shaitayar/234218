#include "EmployeeManager.h"

using std::exception;

EmployeeManager::~EmployeeManager() {
    employee_by_id.DestroyTree();
    employee_by_salary.DestroyTree();
    company_by_id.DestroyTree();
    company_not_empty.DestroyTree();

}

void EmployeeManager::AddCompany(int CompanyID, int Value) {
    Company *company = new Company(CompanyID, Value);
    if (!company) throw EmAllocationError();
    if (company_by_id.find(CompanyID) != NULL) throw EmFailure();
    company_by_id.insert(company);
    company_num++;
}

void EmployeeManager::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade) {
    Node<Company, CompCompanyById> *c = company_by_id.find(CompanyID);
    Employee *employee = new Employee(EmployeeID, Salary, Grade, (c->obj));
    if (!employee) throw EmAllocationError();
    if (employee_by_id.find(EmployeeID) != NULL) {
        throw EmFailure();
    }
    employee_by_id.insert(employee);
    employee_by_salary.insert(employee);
    (c->obj)->addEmployee(employee);
    employee_num++;
    max_employee = employee_by_salary.getMaxNode();
    company_not_empty.insert(c->obj);
}

void EmployeeManager::RemoveEmployee(int EmployeeID) {
    auto node = employee_by_id.find(EmployeeID);
    Employee *employee = node->obj;
    Company *company = employee->getCompany();
    employee_by_id.deleteNode(EmployeeID);
    company->RemoveEmployee(EmployeeID);

    delete employee;
    max_employee = employee_by_salary.getMaxNode();
    if (company->getSize() == 0) company_not_empty.deleteNode(company->getID());
}

void EmployeeManager::RemoveCompany(int CompanyID) {
    auto comp = company_by_id.find(CompanyID);
    if (!comp) throw EmFailure();
    Company *company = comp->obj;

    //If company has workers
    if (company->getSize() != 0) throw EmFailure();
    company_by_id.deleteNode(CompanyID);
    company_not_empty.deleteNode(CompanyID);
    delete company;
}


void EmployeeManager::GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    Company *comp = emp->getCompany();
    *EmployerID = comp->getID();
    *Salary = emp->getSalary();
    *Grade = emp->getGrade();
}

void EmployeeManager::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    emp->setSalary(SalaryIncrease);
    if (BumpGrade > 0) {
        emp->setGrade();
    }
    Company *company = emp->getCompany();
    company->RemoveEmployee(EmployeeID);
    company->addEmployee(emp);
    employee_by_salary.deleteNode(EmployeeID);
    employee_by_salary.insert(emp);
}


void EmployeeManager::HireEmployee(int EmployeeID, int NewCompanyID) {
    auto node = employee_by_id.find(EmployeeID);
    if (!node) throw EmFailure();
    Employee *emp = node->obj;
    Company *company1 = emp->getCompany();
    auto n_company = company_by_id.find(NewCompanyID);
    if (!n_company) throw EmFailure();
    Company *company2 = n_company->obj;

    //remove from company 1 and add to company 2
    emp->setCompany(company2);
    company1->RemoveEmployee(EmployeeID);
    company2->addEmployee(emp);
}


void EmployeeManager::GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees) {
    auto node = company_by_id.find(CompanyID);
    if (node == NULL) throw EmFailure();
    *Value = node->obj->getValue();
    *NumEmployees = node->obj->getSize();
}

void EmployeeManager::IncreaseCompanyValue(int CompanyID, int ValueIncrease) {
    auto node = company_by_id.find(CompanyID);
    if (node == NULL)
        throw EmFailure();
    node->obj->setValue(ValueIncrease);
}

template <class L>
void merge(Employee **X, int x_size, Employee **Y, int y_size, Employee **result, L compare) {
    int i = 0, j = 0, k = 0;
    while ((i < x_size) && (j < y_size)) {
        if (compare(X[i], Y[j]) > 0) {
            result[k] = (Y[j]);
            k++;
            j++;
        } else {
            result[k] = (X[i]);
            k++;
            i++;
        }
    }
    while (i < x_size) {
        result[k] = (X[i]);
        k++;
        i++;
    }
    while (j < y_size) {
        result[k] = (Y[j]);
        k++;
        j++;
    }
}

void update_company(Employee ** arr,int size, Company * comp){
    for (int i = 0; i < size; ++i) {
        arr[i]->setCompany(comp);
    }
}

void EmployeeManager::AcquireCompany(int AcquirerID, int TargetID, double Factor) {
    auto acquirer = company_by_id.find(AcquirerID);
    auto target = company_by_id.find(TargetID);
    if (!acquirer || !target) throw EmFailure();
    int target_value = target->obj->getValue();
    int acquirer_value = acquirer->obj->getValue();
    if (acquirer_value < target_value * 10) throw EmFailure();
    int new_value = (acquirer_value + target_value) * Factor;
    int tsize = target->obj->getSize();
    int asize = acquirer->obj->getSize();

    Company *new_company = new Company(AcquirerID, new_value);
    if (!new_company) throw EmAllocationError();

    Employee **empByIDTarget = (Employee **) malloc(sizeof(**empByIDTarget) * tsize);
    Employee **empBySalaryTarget = (Employee **) malloc(sizeof(**empBySalaryTarget) * tsize);
    Employee **empByIDAcq = (Employee **) malloc(sizeof(**empByIDAcq) * asize);
    Employee **empBySalaryAcq = (Employee **) malloc(sizeof(**empBySalaryAcq) * asize);
    Employee **combinedID = (Employee **) malloc(sizeof(**combinedID) * (tsize + asize));
    Employee **combinedSalary = (Employee **) malloc(sizeof(**combinedSalary) * (tsize + asize));

    if(!empByIDTarget ||!empBySalaryTarget||!empByIDAcq||!empBySalaryAcq ||!combinedID ||!combinedSalary){
        free(empByIDTarget);
        free(empBySalaryTarget);
        free(empByIDAcq);
        free(empBySalaryAcq);
        free(combinedID);
        free(combinedSalary);
        delete new_company;
        throw EmAllocationError();
    }

    (target->obj)->TreeToArray(empByIDTarget, empBySalaryTarget);
    (acquirer->obj)->TreeToArray(empByIDAcq, empBySalaryAcq);

    CompEmployeeById ci;
    CompEmployeeBySalary cs;
    merge<CompEmployeeById>(empByIDTarget, tsize, empByIDAcq, asize, combinedID, ci);
    merge<CompEmployeeBySalary>(empBySalaryTarget, tsize, empBySalaryAcq, asize, combinedSalary, cs);

    update_company(combinedID,tsize+asize, new_company);

    new_company->ArrayToTree(combinedID, combinedSalary, tsize+asize);

    delete target;
    delete acquirer;

    this->company_by_id.insert(new_company);
    if (new_company->getSize()>0) this->company_not_empty.insert(new_company);

}

void EmployeeManager::GetHighestEarner(int CompanyID, int *EmployeeID) {
    if (CompanyID < 0) {
        *EmployeeID = max_employee->obj->getID();
    } else if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company *comp = node->obj;
        *EmployeeID = comp->getMax();
    }
}

void EmployeeManager::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees) {
    if (CompanyID < 0) {
        *Employees = (int *) std::malloc(employee_num * sizeof(int));
        if (!Employees) throw EmAllocationError();
        employee_by_salary.printToList(Employees);
        *NumOfEmployees = employee_num;
    } else if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company *comp = node->obj;
        *Employees = (int *) std::malloc(comp->getSize() * sizeof(int));
        if (!Employees) throw EmAllocationError();
        comp->printToList(Employees);
        *NumOfEmployees = comp->getSize();
    }
}

void EmployeeManager::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees) {
    if (company_not_empty.getSize() < NumOfCompanies) throw EmFailure();
    *Employees = (int *) std::malloc(NumOfCompanies * sizeof(int));
    if (!Employees) throw EmAllocationError();

    company_not_empty.getNMax(NumOfCompanies, Employees);
}

void EmployeeManager::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                                              int MinGrade,
                                              int *TotalNumOfEmployees, int *NumOfEmployees) {

    *TotalNumOfEmployees = 0;
    *NumOfEmployees = 0;

    if (CompanyID < 0) {
        employee_by_id.getMatch(MinEmployeeID, MaxEmployeeId, MinSalary,
                                MinGrade, TotalNumOfEmployees, NumOfEmployees);
    }
    if (CompanyID > 0) {
        auto node = company_by_id.find(CompanyID);
        if (!node) throw EmFailure();
        Company *company = node->obj;
        if (company->getSize() == 0) {
            return;
        } else {
            company->getMatchCompany(MinEmployeeID, MaxEmployeeId, MinSalary,
                                     MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
    }
}

void EmployeeManager::Quit() {

}