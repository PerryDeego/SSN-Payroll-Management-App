#include "Payroll.h"
#include "PayrollNode.h"

// Destructor
PayrollNode::~PayrollNode() {}

//Default Constructor
PayrollNode::PayrollNode() :data()
{
	next = nullptr;
}

// Primary Constructor
PayrollNode::PayrollNode(Payroll nodeData)
	:data(nodeData)
{
	next = nullptr;
}

// Copy constructor
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


