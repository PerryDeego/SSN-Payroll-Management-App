#include "Employee.h"
#include "EmpNode.h"
#include <iostream> 


//destructure constructor
EmpNode::~EmpNode() {}

//default constructor
EmpNode::EmpNode() :data()
{
	next = nullptr;
}

//primary constructor
EmpNode::EmpNode(Employee nodeData)
	:data(nodeData)
{
	//this->data = nodeData;
	next = nullptr;
}

//copy constructor
EmpNode::EmpNode(const EmpNode &nd)
	:data(nd.getData())
{
	this->next = nd.next;
}

void EmpNode::setNext(EmpNode *nxt)
{
	next = nxt;
}

void EmpNode::setData(Employee empObj)
{
	data = empObj;
}

Employee EmpNode::getData() const
{
	return data;
}

EmpNode* EmpNode::getNext() const
{
	return next;
}

void EmpNode::display() const
{
	data.display();
}


