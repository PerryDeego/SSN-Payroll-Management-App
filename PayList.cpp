#include "Payroll.h"
#include "PayrollNode.h"
#include "PayList.h"

#include <iostream>
using namespace std;

PayList::PayList()
{
    head = nullptr;
}

PayList::~PayList()
{
    // Destructor implementation can be added here if needed
}

bool PayList::isEmpty()
{
    return head == nullptr;
}

bool PayList::isFull()
{
    PayrollNode *temp = new PayrollNode();
    if (temp != nullptr)
    {
        delete temp;
        return false;
    }
    return true;
}

void PayList::insertAtFront(Payroll payData)
{
    if (!isFull())
    {
        PayrollNode *newNode = new PayrollNode(payData);
        if (newNode != nullptr)
        {
            newNode->setNext(head);
            head = newNode;
        }
        else
        {
            cout << "Error allocating memory for node!" << endl << endl;
        }
    }
    else
    {
        cout << "List already full!" << endl << endl;
    }
}

int PayList::countNodes()
{
    int count = 0;
    PayrollNode *currentNode = head;
    while (currentNode != nullptr)
    {
        ++count;
        currentNode = currentNode->getNext();
    }
    return count;
}

void PayList::traverse()
{
    if (!isEmpty())
    {
        PayrollNode *currentNode = head;
        while (currentNode != nullptr)
        {
            currentNode->display();
            currentNode = currentNode->getNext();
            cout << endl;
        }
    }
    else
    {
        cout << "List is empty, no nodes to traverse!" << endl;
    }
}

// Merge Sort by ID
void PayList::mergeSortById()
{
    head = mergeSort(head, [](const Payroll& a, const Payroll& b) {
        return a.getId() < b.getId();
    });
}

// Merge Sort by Last Name
void PayList::mergeSortByLastName()
{
    head = mergeSort(head, [](const Payroll& a, const Payroll& b) {
        return a.getLastName() < b.getLastName();
    });
}

// Merge Sort by Department Code
void PayList::mergeSortByDepartmentCode()
{
    head = mergeSort(head, [](const Payroll& a, const Payroll& b) {
        return a.getDepartmentCode() < b.getDepartmentCode();
    });
}

// Merge Sort by Position
void PayList::mergeSortByPosition()
{
    head = mergeSort(head, [](const Payroll& a, const Payroll& b) {
        return a.getPosition() < b.getPosition();
    });
}

// Helper function to perform merge sort
PayrollNode* PayList::mergeSort(PayrollNode* node, function<bool(const Payroll&, const Payroll&)> compare)
{
    if (!node || !node->getNext())
        return node;

    PayrollNode* middle = getMiddle(node);
    PayrollNode* nextOfMiddle = middle->getNext();
    middle->setNext(nullptr);

    PayrollNode* left = mergeSort(node, compare);
    PayrollNode* right = mergeSort(nextOfMiddle, compare);

    return merge(left, right, compare);
}

// Function to get the middle node of the list
PayrollNode* PayList::getMiddle(PayrollNode* node)
{
    if (!node) return node;

    PayrollNode* slow = node;
    PayrollNode* fast = node->getNext();

    while (fast && fast->getNext())
    {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }
    return slow;
}

// Function to merge two sorted lists
PayrollNode* PayList::merge(PayrollNode* left, PayrollNode* right, function<bool(const Payroll&, const Payroll&)> compare)
{
    if (!left) return right;
    if (!right) return left;

    if (compare(left->getData(), right->getData()))
    {
        left->setNext(merge(left->getNext(), right, compare));
        return left;
    }
    else
    {
        right->setNext(merge(left, right->getNext(), compare));
        return right;
    }
}
