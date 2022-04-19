#include "AvlTree.h"
#include "iostream"
#include "employee.h"
using std::string;



int main(){
    AvlTree<Employee> tree;
    Employee e1(1,100,1);
    Employee e2(2,200,2);
    Employee e3(5,500,5);
    tree.insert(e3);
    tree.insert(e2);
    tree.insert(e1);
    return 0;
}