#include "Payroll.h"
#include "PayrollNode.h"
#include "PayList.h"

// Constructor to initialize the linked list
PayList::PayList() {
    head = nullptr;
}

// Destructor to clean up the linked list
PayList::~PayList() {
    PayrollNode *currentNode = head;
    while (currentNode != nullptr) {
        PayrollNode *nextNode = currentNode->getNext();
        delete currentNode;
        currentNode = nextNode;
    }
    head = nullptr;
}


// Check if the list is empty
bool PayList::isEmpty() const {
    return head == nullptr;
}

// Check if the list is full (in this case, always returns false since we use dynamic memory allocation)
bool PayList::isFull() const {
    PayrollNode *temp = new (nothrow) PayrollNode();

    // If memory allocation fails, the list is considered full
    if (temp != nullptr) {
        delete temp;
        return false;
    }
    return true;
}

// Insert a new Payroll record at the front of the list
void PayList::insertAtFront(Payroll payData) {

    // Check if the list is full before inserting
    if (!isFull()) {
        PayrollNode *newNode = new (nothrow) PayrollNode(payData);

        // If memory allocation was successful, insert the new node at the front
        if (newNode != nullptr) {
            newNode->setNext(head);
            head = newNode;
        } else {
            cout << "\n\t\t[ ❌ Memory allocation failed for new node. ]" << endl;
        }
    } else {
        cout << "\n\t\t[ ℹ️️ List is full, unable to insert new node. ]" << endl;
    }
}

// Count the number of nodes in the list
int PayList::countNodes() const {
    int count = 0;
    PayrollNode *currentNode = head;

    // If the list is empty, return 0
    if (isEmpty()) {
        return count; // Return 0 if the list is empty
    }

    // Traverse the list and count the nodes
    while (currentNode != nullptr) {
        ++count;
        currentNode = currentNode->getNext(); // Move to the next node
    }

    return count;
}

// Traverse the list and display each Payroll record
void PayList::traverse() const {

    // Check if the list is empty before traversing
    if (!isEmpty()) {
        PayrollNode *currentNode = head;

        // If the list is not empty, traverse through each node
        while (currentNode != nullptr) {
            currentNode->display();
            currentNode = currentNode->getNext(); // Move to the next node
            cout << endl;
        }
    } else {
        cout << "\n\t\t[ ℹ️️ List is empty. No records to display. ]" << endl;
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

// Helper: Get the middle node of a list
PayrollNode* PayList::getMiddle(PayrollNode *node) {

    // If the list is empty or has only one node, return it
    if (!node) return node;

    PayrollNode *first = node;
    PayrollNode *second = node->getNext();

    // Use the slow and fast pointer technique to find the middle node
    while (second && second->getNext()) {
        first = first->getNext();
        second = second->getNext()->getNext();
    }

    return first;
}

// Helper: Merge Sort implementation
PayrollNode* PayList::mergeSort(PayrollNode *node, function<bool(const Payroll &, const Payroll &)> compare) {
    
    // Base case: if the list is empty or has only one node, return it
    if (!node || !node->getNext()) return node;

    PayrollNode *middle = getMiddle(node);
    PayrollNode *nextOfMiddle = middle->getNext();
    middle->setNext(nullptr);  // Split list

    PayrollNode *left = mergeSort(node, compare);
    PayrollNode *right = mergeSort(nextOfMiddle, compare);

    return merge(left, right, compare);
}

// Helper: Merge two sorted lists
PayrollNode* PayList::merge(PayrollNode *left, PayrollNode *right, function<bool(const Payroll &, const Payroll &)> compare) {
    
    // If the left list is empty, return the right list
    if (!left) return right;

    // If the right list is empty, return the left list
    if (!right) return left;

    // Compare the data of the current nodes of both lists
    if (compare(left->getData(), right->getData())) {
        // If the left node's data is less than the right node's data,
        // set the next of the left node to the result of merging the rest of the left list with the right list
        left->setNext(merge(left->getNext(), right, compare));

        return left; 
    } else {
        // If the right node's data is less than or equal to the left node's data,
        // set the next of the right node to the result of merging the left list with the rest of the right list
        right->setNext(merge(left, right->getNext(), compare));
        return right;
    }
}
