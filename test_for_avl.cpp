#include "AvlTree.h"
#include "iostream"
#include "employee.h"
#include "company.h"

using std::string;


int main() {
    CompEmployeeById c;
    AvlTree<Employee,CompEmployeeById> tree(c);
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

    tree.insert(&e3);
    tree.insert(&e4);
    tree.insert(&e1);
    tree.insert(&e2);
    tree.insert(&e2);
    tree.insert(&e5);
    tree.insert(&e7);
    tree.insert(&e8);
    tree.insert(&e6);
    tree.insert(&e9);
    tree.insert(&e10);
    int x=0;
    int * total_num=&x;
    int y = 0;
    int * num = &y;
    tree.getMatch(3,7,700,2,total_num,num);
    std::cout<<"total: "<<*total_num << "\nnum: "<<*num<<std::endl;
    return 0;
}