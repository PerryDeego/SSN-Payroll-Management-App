#include "Payroll.h"
#include "PayrollNode.h"
#include <iostream> 


//destructure constructor
PayrollNode::~PayrollNode() {}

//default constructor
PayrollNode::PayrollNode() :data()
{
	next = nullptr;
}

//primary constructor
PayrollNode::PayrollNode(Payroll nodeData)
	:data(nodeData)
{
	//this->data = nodeData;
	next = nullptr;
}

//copy constructor
PayrollNode::PayrollNode(const PayrollNode &nd)
	:data(nd.getData())
{
	next = nd.next;
}

void PayrollNode::setNext(PayrollNode *nxt)
{
	next = nxt;
}

void PayrollNode::setData(Payroll payObj)
{
	data = payObj;
}

Payroll PayrollNode::getData() const
{
	return data;
}

PayrollNode* PayrollNode::getNext() const
{
	return next;
}

void PayrollNode::display() const
{
	data.display();
}


