#ifndef EMPNODE_H
#define EMPNODE_H


#include "Employee.h"
#include <iostream>

class EmpNode{
private:
	Employee data;
	EmpNode *next;

public:
	//destructure constructor
	~EmpNode();

	//default constructor
	EmpNode();

	//primary constructor
	EmpNode(Employee nodeData);

	EmpNode(const EmpNode &emp);

	//--------- mutators ------------//
	void setNext(EmpNode *nxt);

	void setData(Employee emp);

	//-------- accessors -----------//
	Employee getData() const;

	EmpNode* getNext() const;

	void display() const;

};
#endif
