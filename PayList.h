#ifndef PAYLIST_H
#define PAYLIST_H

#include "Payroll.h"
#include "PayrollNode.h"

#include <iostream>
#include <functional>

class PayList
{
private:
    PayrollNode *head;

    // Helper functions for merge sort
    PayrollNode* mergeSort(PayrollNode* node, std::function<bool(const Payroll&, const Payroll&)> compare);
    PayrollNode* getMiddle(PayrollNode* node);
    PayrollNode* merge(PayrollNode* left, PayrollNode* right, std::function<bool(const Payroll&, const Payroll&)> compare);

public:
    PayList();
    ~PayList();

    bool isEmpty();
    bool isFull();
    void insertAtFront(Payroll);
    int countNodes();
    void traverse();

    // Merge sort methods
    void mergeSortById();
    void mergeSortByLastName();
    void mergeSortByDepartmentCode();
    void mergeSortByPosition();
};

#endif






