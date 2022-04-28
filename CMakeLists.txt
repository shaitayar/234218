cmake_minimum_required(VERSION 3.17)
project(234218)

set(CMAKE_CXX_STANDARD 11)

add_executable(234218 AvlTree.h employee.h employee.cpp  company.cpp company.h
        library1.h library1.cpp EmployeeManager.cpp EmployeeManager.h test_for_avl.cpp)