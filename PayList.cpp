#include "Payroll.h"
#include "PayrollNode.h"
#include "PayList.h"
#include <iostream>
#include <functional>  // For std::function

using namespace std;

PayList::PayList() {
    head = nullptr;
}

PayList::~PayList() {
    PayrollNode *currentNode = head;
    while (currentNode != nullptr) {
        PayrollNode *nextNode = currentNode->getNext();
        delete currentNode;
        currentNode = nextNode;
    }
    head = nullptr;
}


bool PayList::isEmpty() const {
    return head == nullptr;
}

bool PayList::isFull() const {
    PayrollNode *temp = new (nothrow) PayrollNode();
    if (temp != nullptr) {
        delete temp;
        return false;
    }
    return true;
}

void PayList::insertAtFront(Payroll payData) {
    if (!isFull()) {
        PayrollNode *newNode = new (nothrow) PayrollNode(payData);
        if (newNode != nullptr) {
            newNode->setNext(head);
            head = newNode;
        } else {
            cout << "[ ❌ Memory allocation failed for new node. ]" << endl;
        }
    } else {
        cout << "[ ℹ️️ List is full, unable to insert new node. ]" << endl;
    }
}

int PayList::countNodes() const {
    int count = 0;
    PayrollNode *currentNode = head;
    while (currentNode != nullptr) {
        ++count;
        currentNode = currentNode->getNext();
    }
    return count;
}

void PayList::traverse() const {
    if (!isEmpty()) {
        PayrollNode *currentNode = head;
        while (currentNode != nullptr) {
            currentNode->display();
            currentNode = currentNode->getNext();
            cout << endl;
        }
    } else {
        cout << "[ ℹ️️ List is empty. No records to display. ]" << endl;
    }
}

// Merge Sort by ID
void PayList::mergeSortById() {
    head = mergeSort(head, [](const Payroll &a, const Payroll &b) {
        return a.getId() < b.getId();
    });
}

// Merge Sort by Last Name
void PayList::mergeSortByLastName() {
    head = mergeSort(head, [](const Payroll &a, const Payroll &b) {
        return a.getLastName() < b.getLastName();
    });
}

// Merge Sort by Department Code
void PayList::mergeSortByDepartmentCode() {
    head = mergeSort(head, [](const Payroll &a, const Payroll &b) {
        return a.getDepartmentCode() < b.getDepartmentCode();
    });
}

// Merge Sort by Position
void PayList::mergeSortByPosition() {
    head = mergeSort(head, [](const Payroll &a, const Payroll &b) {
        return a.getPosition() < b.getPosition();
    });
}

// Helper: Merge Sort implementation
PayrollNode* PayList::mergeSort(PayrollNode *node, function<bool(const Payroll &, const Payroll &)> compare) {
    if (!node || !node->getNext()) return node;

    PayrollNode *middle = getMiddle(node);
    PayrollNode *nextOfMiddle = middle->getNext();
    middle->setNext(nullptr);  // Split list

    PayrollNode *left = mergeSort(node, compare);
    PayrollNode *right = mergeSort(nextOfMiddle, compare);

    return merge(left, right, compare);
}

// Helper: Get the middle node of a list
PayrollNode* PayList::getMiddle(PayrollNode *node) {
    if (!node) return node;

    PayrollNode *slow = node;
    PayrollNode *fast = node->getNext();

    while (fast && fast->getNext()) {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    return slow;
}

// Helper: Merge two sorted lists
PayrollNode* PayList::merge(PayrollNode *left, PayrollNode *right, function<bool(const Payroll &, const Payroll &)> compare) {
    if (!left) return right;
    if (!right) return left;

    if (compare(left->getData(), right->getData())) {
        left->setNext(merge(left->getNext(), right, compare));
        return left;
    } else {
        right->setNext(merge(left, right->getNext(), compare));
        return right;
    }
}
