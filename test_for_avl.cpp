#include "AvlTree.h"
#include "iostream"
#include "employee.h"

using std::string;


int main() {
    AvlTree<Employee> tree;
    Employee e1(1, 100, 1);
    Employee e2(2, 200, 2);
    Employee e3(3, 300, 2);
    Employee e4(4, 400, 2);
    Employee e5(5, 500, 5);
    tree.insert(e3);
    tree.insert(e4);
    tree.insert(e5);
    tree.insert(e2);
    return 0;
}