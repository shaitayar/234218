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
    Employee e2(2, 200, 2, (&c1));
    Employee e3(3, 300, 2, (&c1));
    Employee e4(4, 400, 2, (&c1));
    Employee e5(5, 500, 5, (&c1));
    Employee e6(6, 600, 6, (&c1));
    Employee e7(7, 700, 7, (&c1));
    Employee e8(8, 800, 8, (&c1));
    Employee e9(9, 900, 9, (&c1));
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


    tree.deleteNode(7);
    return 0;
}