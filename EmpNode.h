#ifndef EMPNODE_H
#define EMPNODE_H

#include "Employee.h"
#include <iostream>

class EmpNode {
private:
    Employee data;
    EmpNode *next;

public:
    // Destructor
    ~EmpNode();

    // Default constructor
    EmpNode();

    // Primary constructor
    EmpNode(Employee nodeData);

    // Copy constructor
    EmpNode(const EmpNode &nd);

    // Mutators
    void setNext(EmpNode *nxt);
    void setData(Employee emp);

    // Accessors
    Employee getData() const;
    EmpNode* getNext() const;

    // Display method
    void display() const;
};

#endif
