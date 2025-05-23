#ifndef EMPLIST_H
#define EMPLIST_H

#include "Employee.h"
#include "EmpNode.h"
#include <iostream>
#include <functional>

class EmpList
{
private:
    EmpNode *head;

    // Helper functions for merge sort
    EmpNode* mergeSort(EmpNode* node, std::function<bool(const Employee&, const Employee&)> compare);
    EmpNode* getMiddle(EmpNode* node);
    EmpNode* merge(EmpNode* left, EmpNode* right, std::function<bool(const Employee&, const Employee&)> compare);

public:
    EmpList();
    ~EmpList();

    bool isEmpty();
    bool isFull();
    void insertAtFront(Employee);
    int countNodes();
    void traverse();

    // Merge sort methods
    void mergeSortById();
    void mergeSortByLastName();
    void mergeSortByDepartmentCode();
    void mergeSortByPosition();
    void mergeSortByHoursWorked();
};

#endif
