#ifndef PAYLIST_H
#define PAYLIST_H

#include "Payroll.h"
#include "PayrollNode.h"

#include <iostream>
#include <functional>

class PayList {
private:
    PayrollNode* head;

public:
    PayList();
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
    PayrollNode* mergeSort(PayrollNode *node, std::function<bool(const Payroll&, const Payroll&)> compare);
    PayrollNode* getMiddle(PayrollNode *node);
    PayrollNode* merge(PayrollNode *left, PayrollNode *right, std::function<bool(const Payroll&, const Payroll&)> compare);
};


#endif






