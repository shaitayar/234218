#include "AvlTree.h"
#include "iostream"
#include "employee.h"
using std::string;


int main() {
    AvlTree<Employee> tree;
    StatusType * stat;
    Employee e1(1, 100, 1);
    Employee e2(2, 200, 2);
    Employee e3(3, 300, 2);
    Employee e4(4, 400, 2);
    Employee e5(5, 500, 5);
    tree.insert(e3,stat);
    tree.insert(e4,stat);
    tree.insert(e5,stat);
    tree.insert(e2,stat);
    return 0;
}