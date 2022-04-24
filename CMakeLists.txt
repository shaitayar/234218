cmake_minimum_required(VERSION 3.17)
project(234218)

set(CMAKE_CXX_STANDARD 11)

add_executable(234218 AvlTree.h employee.h employee.cpp company.h company.cpp EmployeeManager.h EmployeeManager.cpp tests_for_employee.cpp)