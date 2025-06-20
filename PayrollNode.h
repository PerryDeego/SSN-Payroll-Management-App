#ifndef PAYROLLNODE_H
#define PAYROLLNODE_H


#include "Payroll.h"
#include <iostream>

class PayrollNode {
private:
	Payroll data;
	PayrollNode *next;

public:
	~PayrollNode();

	PayrollNode();

	PayrollNode(Payroll);

	PayrollNode(const PayrollNode &);

	//--------- mutators ------------//
	void setNext(PayrollNode *nxt);
	void setData(Payroll);

	//-------- accessors -----------//
	Payroll getData() const;
	PayrollNode* getNext() const;

	void display() const;

};
#endif

