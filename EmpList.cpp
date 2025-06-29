#include "Employee.h"
#include "EmpNode.h"
#include "EmpList.h"

using namespace std;


EmpList::EmpList() {
    head = nullptr;
}

EmpList::~EmpList() {
    EmpNode* current = head;

    // Traverse the list and delete each node
    while (current != nullptr) {
        EmpNode* nextNode = current->getNext();
        delete current; 
        current = nextNode; 
    }
}

bool EmpList::isEmpty() {
    return head == nullptr;
}

bool EmpList::isFull() {
    EmpNode *temp = new EmpNode();
    
    // Check if memory allocation was successful
    if (temp != nullptr) {
        delete temp;
        return false;
    }
    return true;
}

void EmpList::insertAtFront(Employee empData) {

    // Check if the list is full before inserting
    // If the list is not full, create a new node and insert it at the front
    if (!isFull()) {
        EmpNode *newNode = new EmpNode(empData);

        // Check if memory allocation was successful
        if (newNode != nullptr) {
            newNode->setNext(head);
            head = newNode;
        } else {
            cout << "\n\t\t[ ❌ Error allocating memory for node! ]" << endl << endl;
        }
    } else {
        cout << "\n\t\t[ ℹ️ List already full! ]" << endl << endl;
    }
}

int EmpList::countNodes() {
    int count = 0;
    EmpNode *temp = head;

    // Traverse the list and count the nodes
    if (isEmpty()) {
        return count; // Return 0 if the list is empty
    }

    // If the list is not empty, traverse through each node
    while (temp != nullptr) {
        ++count;
        temp = temp->getNext();
    }
    return count;
}

void EmpList::traverse() {

    // Check if the list is empty before traversing
    if (!isEmpty()) {
        EmpNode *temp = head;
        
        temp->getData().displayHeader();

        // Traverse the list and display each employee's data
        while (temp != nullptr) {
            temp->display();
            temp = temp->getNext();
            cout << endl;
        }
    } else {
        cout << "\n\t\t[ ℹ️ List is empty, no records to display! ]" << endl;
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
EmpNode* EmpList::mergeSort(EmpNode* node, function<bool(const Employee&, const Employee&)> compare) {

    // Base case: if the list is empty or has only one node, return it
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

    // If the list is empty or has only one node, return it
    if (!node) return node;

    EmpNode* first = node;
    EmpNode* second = node->getNext();

    // Use the slow and fast pointer technique to find the middle node
    while (second && second->getNext()) {
        first = first->getNext();
        second = second->getNext()->getNext();
    }
    return first;
}

// Function to merge two sorted lists
EmpNode* EmpList::merge(EmpNode* left, EmpNode* right, function<bool(const Employee&, const Employee&)> compare) {

    // If either list is empty, return the other list
    if (!left) return right;
    // If the right list is empty, return the left list
    if (!right) return left;

    // Compare the data of the two nodes and merge accordingly
    if (compare(left->getData(), right->getData())) {
        left->setNext(merge(left->getNext(), right, compare));
        return left;
    } else {
        right->setNext(merge(left, right->getNext(), compare));
        return right;
    }
}
