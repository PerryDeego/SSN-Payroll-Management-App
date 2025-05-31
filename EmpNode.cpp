#include "Employee.h"
#include "EmpNode.h"
#include <iostream>

// Destructor
EmpNode::~EmpNode() {}

// Default constructor
EmpNode::EmpNode() : data(), next(nullptr) {}

// Primary constructor
EmpNode::EmpNode(Employee nodeData) : data(nodeData), next(nullptr) {}

// Copy constructor
EmpNode::EmpNode(const EmpNode &nd) : data(nd.getData()), next(nullptr) {}

// Mutators
void EmpNode::setNext(EmpNode *nxt) {
    next = nxt;
}

void EmpNode::setData(Employee empObj) {
    data = empObj;
}

// Accessors
Employee EmpNode::getData() const {
    return data;
}

EmpNode* EmpNode::getNext() const {
    return next;
}

// Display method
void EmpNode::display() const {
    data.display();
}
