#ifndef INC_234218_DS_H
#define INC_234218_DS_H

#include "company.h"
#include "library1.h"
#include <stdio.h>


class EmployeeManager {
    AvlTree<shared_ptr<Company> > companies;


public:
    EmployeeManager();
    StatusType AddCompany(int CompanyID, int Value);

};


#endif
