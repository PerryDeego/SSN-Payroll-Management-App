#include "Employee.h"
#include "EmpNode.h"
#include "EmpList.h"
#include <iostream>
#include <functional>

using namespace std;

EmpList::EmpList() {
    head = nullptr;
}

EmpList::~EmpList() {
    EmpNode* current = head;
    while (current != nullptr) {
        EmpNode* nextNode = current->getNext();
        delete current; // Free the current node
        current = nextNode; // Move to the next node
    }
}

bool EmpList::isEmpty() {
    return head == nullptr;
}

bool EmpList::isFull() {
    EmpNode *temp = new EmpNode();
    if (temp != nullptr) {
        delete temp;
        return false;
    }
    return true;
}

void EmpList::insertAtFront(Employee empData) {
    if (!isFull()) {
        EmpNode *newNode = new EmpNode(empData);
        if (newNode != nullptr) {
            newNode->setNext(head);
            head = newNode;
        } else {
            cout << "[❌ Error allocating memory for node! ]" << endl << endl;
        }
    } else {
        cout << "[ℹ️ List already full! ]" << endl << endl;
    }
}

int EmpList::countNodes() {
    int count = 0;
    EmpNode *temp = head;
    while (temp != nullptr) {
        ++count;
        temp = temp->getNext();
    }
    return count;
}

void EmpList::traverse() {
    if (!isEmpty()) {
        EmpNode *temp = head;
        
        while (temp != nullptr) {
            temp->display();
            temp = temp->getNext();
            cout << endl;
        }
    } else {
        cout << "[ℹ️ List is empty, no records to display! ]" << endl;
    }
}

// Merge Sort by ID
void EmpList::mergeSortById() {
    head = mergeSort(head, [](const Employee& a, const Employee& b) {
        return a.getId() < b.getId();
    });
}

// Merge Sort by Last Name
void EmpList::mergeSortByLastName() {
    head = mergeSort(head, [](const Employee& a, const Employee& b) {
        return a.getLastName() < b.getLastName();
    });
}

// Merge Sort by Department Code
void EmpList::mergeSortByDepartmentCode() {
    head = mergeSort(head, [](const Employee& a, const Employee& b) {
        return a.getDepartmentCode() < b.getDepartmentCode();
    });
}

// Merge Sort by Position
void EmpList::mergeSortByPosition() {
    head = mergeSort(head, [](const Employee& a, const Employee& b) {
        return a.getPosition() < b.getPosition();
    });
}

// Merge Sort by Hours Worked
void EmpList::mergeSortByHoursWorked() {
    head = mergeSort(head, [](const Employee& a, const Employee& b) {
        return a.getHoursWorked() < b.getHoursWorked();
    });
}

// Helper function to perform merge sort
EmpNode* EmpList::mergeSort(EmpNode* node, std::function<bool(const Employee&, const Employee&)> compare) {
    if (!node || !node->getNext())
        return node;

    EmpNode* middle = getMiddle(node);
    EmpNode* nextOfMiddle = middle->getNext();
    middle->setNext(nullptr);

    EmpNode* left = mergeSort(node, compare);
    EmpNode* right = mergeSort(nextOfMiddle, compare);

    return merge(left, right, compare);
}

// Function to get the middle node of the list
EmpNode* EmpList::getMiddle(EmpNode* node) {
    if (!node) return node;

    EmpNode* slow = node;
    EmpNode* fast = node->getNext();

    while (fast && fast->getNext()) {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }
    return slow;
}

// Function to merge two sorted lists
EmpNode* EmpList::merge(EmpNode* left, EmpNode* right, std::function<bool(const Employee&, const Employee&)> compare) {
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
