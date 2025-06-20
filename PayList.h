#ifndef PAYLIST_H
#define PAYLIST_H

#include "Payroll.h"
#include "PayrollNode.h"

#include <iostream>
#include <functional>

using namespace std;

class PayList {
private:
    PayrollNode* head;

public:
    // Default constructor
    PayList();

    // Destructor
    ~PayList();

    // Delete copy semantics
    PayList(const PayList&) = delete;
    PayList& operator=(const PayList&) = delete;

    bool isEmpty() const;
    bool isFull() const;
    void insertAtFront(Payroll payData);
    int countNodes() const;
    void traverse() const;

    void mergeSortById();
    void mergeSortByLastName();
    void mergeSortByDepartmentCode();
    void mergeSortByPosition();

private:
    PayrollNode* getMiddle(PayrollNode *node);
    PayrollNode* mergeSort(PayrollNode *node, function<bool(const Payroll&, const Payroll&)> compare);
    PayrollNode* merge(PayrollNode *left, PayrollNode *right, function<bool(const Payroll&, const Payroll&)> compare);
};


#endif






