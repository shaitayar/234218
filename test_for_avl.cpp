#include "iostream"
#include "EmployeeManager.h"

using std::string;


int main() {
    EmployeeManager em1;
    Company c1(10,100);
    Company c2 (20,200);
    Employee e1(1, 100, 1, (&c1));
    Employee e2(2, 100, 2, (&c1));
    Employee e3(3, 100, 2, (&c1));
    Employee e4(4, 100, 2, (&c1));
    Employee e5(5, 200, 5, (&c1));
    Employee e6(6, 200, 6, (&c1));
    Employee e7(7, 700, 7, (&c1));
    Employee e8(8, 1000, 8, (&c1));
    Employee e9(9, 1000, 9, (&c1));
    Employee e10(10, 1000, 10, (&c1));

    em1.AddCompany(10,100);
    em1.AddCompany(20,1500);
    em1.AddEmployee(1,10,100,1);


    em1.AddEmployee(4,20,400,1);
    em1.AddEmployee(5,20,400,1);
    em1.AddEmployee(6,20,400,1);
    em1.AddEmployee(7,20,400,1);


    em1.IncreaseCompanyValue(20, 1000);
    em1.HireEmployee(1,20);
    em1.PromoteEmployee(1,400, 2);
    em1.AcquireCompany(20,10,1.5);
    em1.AddEmployee(1,10,100,1);
    em1.AddEmployee(2,10,200,1);
    em1.AddEmployee(3,10,300,1);
    em1.PromoteEmployee(4,200,10);


    int *array;
    int ptr;
    em1.GetAllEmployeesBySalary(20, &array, &ptr);

    for (int i=0; i<ptr; i++)
    {
        std::cout << "employye num:" << ptr << "\n";
        std::cout << array[i] << "\n";
    }

    int *array2;
    int ptr2;
    em1.GetAllEmployeesBySalary(10, &array2, &ptr2);

    for (int i=0; i<ptr2; i++)
    {
        std::cout << "employye num:" << ptr2 << "\n";
        std::cout << array2[i] << "\n";
    }


    em1.AddEmployee(5,10, 900, 2);
    em1.AcquireCompany(20,10,1.5);
    int *array3;
    int ptr3;
    em1.GetAllEmployeesBySalary(10, &array3, &ptr3);

    for (int i=0; i<ptr2; i++)
    {
        std::cout << "employye num:" << ptr3 << "\n";
        std::cout << array2[i] << "\n";
    }

    return 0;
}