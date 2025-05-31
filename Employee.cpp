#include "Employee.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

// Constants for file names
const string EMP_FILE_NAME = "employee.txt";
const string TEMP_EMP_FILE_NAME = "tempemp.txt";
const string EMP_PAYROLL_FILE_NAME = "employee_payroll.txt";
const string TEMP_EMP_PAYROLL_FILE_NAME = "temp_emp_payroll.txt";

// Destructor
Employee::~Employee() {}

// Default constructor
Employee::Employee() 
    : id(0), firstName("first name"), lastName("last name"), 
      departmentCode(0), position("position"), hoursWorked(0.0f) {}

// Primary constructor
Employee::Employee(int id, const string& firstName, const string& lastName, 
                   int departmentCode, const string& position, float hoursWorked)
    : id(id), firstName(firstName), lastName(lastName), 
      departmentCode(departmentCode), position(position), hoursWorked(hoursWorked) {}

// Copy constructor
Employee::Employee(const Employee &Emp) 
    : id(Emp.id), firstName(Emp.firstName), lastName(Emp.lastName), 
      departmentCode(Emp.departmentCode), position(Emp.position), hoursWorked(Emp.hoursWorked) {}

// Mutators
void Employee::setId(int empId) { id = empId; }
void Employee::setFirstName(const string& fn) { firstName = fn; }
void Employee::setLastName(const string& ln) { lastName = ln; }
void Employee::setDepartmentCode(int deptCode) { departmentCode = deptCode; }
void Employee::setPosition(const string& post) { position = post; }
void Employee::setHoursWorked(float hr) { hoursWorked = hr; }

// Accessors
int Employee::getId() const { return id; }
string Employee::getFirstName() const { return firstName; }
string Employee::getLastName() const { return lastName; }
int Employee::getDepartmentCode() const { return departmentCode; }
string Employee::getPosition() const { return position; }
float Employee::getHoursWorked() const { return hoursWorked; }

// Display method
void Employee::display() const {
    cout << setfill('=') << setw(115) << "=" << setfill(' ') << endl;
    cout << "| " << left << setw(10) << "ID"
         << "| " << left << setw(20) << "FIRST NAME"
         << "| " << left << setw(20) << "LAST NAME"
         << "| " << left << setw(15) << "DEPT CODE"
         << "| " << left << setw(20) << "POSITION"
         << "| " << right << setw(10) << "HOURS"
         << "\t |" << endl;
    cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
    cout << "| " << left << setw(10) << getId()
         << "| " << left << setw(20) << getFirstName()
         << "| " << left << setw(20) << getLastName()
         << "| " << left << setw(15) << getDepartmentCode()
         << "| " << left << setw(20) << getPosition()
         << "| " << right << setw(10) << fixed << setprecision(2) << getHoursWorked()
         << "\t |" << endl;
    cout << setfill('=') << setw(115) << "=" << setfill(' ') << endl;
}

// Utility function to get validated input for string
string Employee::getValidatedString(const string& prompt) {
    string input;
    cout << prompt;
    if (cin.peek() == '\n') cin.ignore(); // Clear leftover newline if present
    getline(cin, input);
    
    while (input.empty()) {
        cout << "Input cannot be empty. Please enter again: ";
        getline(cin, input);
    }
    return input;
}

// Utility function to get validated input for integer
int Employee::getValidatedInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character
    return value;
}

// Utility function to get validated input for float
float Employee::getValidatedFloat(const string& prompt) {
    float value;
    
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cout << "Invalid input. Please enter a non-negative numeric value: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character
    return value;
}

// Create employee with input validation
Employee Employee::createEmployee(int empId) {
    string firstName = getValidatedString("➡️\t Enter Employee first name: ");
    cout << endl;
    string lastName = getValidatedString("➡️\t Enter Employee last name: ");
    cout << endl;
    int departmentCode = getValidatedInt("➡️\t Enter Employee department code: ");
    cout << endl;
    string position = getValidatedString("➡️\t Enter Employee position: ");
    cout << endl;
    float hoursWorked = getValidatedFloat("➡️\t Enter Employee hours worked: ");
    cout << endl;

    return Employee(empId, firstName, lastName, departmentCode, position, hoursWorked);
}

// Utility function to check file access
bool Employee::checkFileAccess(ios& file) {
    if (file.fail()) {
        throw runtime_error("[❌ ERROR ACCESSING FILE! ]");
    }
    return true; // Return true if no error
}


// Helper function to write a department record to files
void Employee::writeRecord(ofstream& empFile, ofstream& empPayrollFile, const Employee& emp) {
    empFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t"
            << emp.getDepartmentCode() << "\t" << emp.getPosition() << endl;
    empPayrollFile << emp.getId() << "\t" << emp.getDepartmentCode() << "\t" << emp.getHoursWorked() << endl;
}

// Function: Add record
void Employee::addRecord(const Employee& emp) {
    if (emp.getId() == 0 || emp.getFirstName().empty() || emp.getLastName().empty() ||
        emp.getDepartmentCode() == 0 || emp.getPosition().empty() || emp.getHoursWorked() < 0) {
        cout << "\t\t\a\n [ Cannot add record: All fields must be non-empty and valid! ]\n\n";
        return;
    }

    try {
        ifstream empFileCheck(EMP_FILE_NAME);
        checkFileAccess(empFileCheck);

        int id, deptCode;
        string firstName, lastName, position;
        bool exists = false;
        bool nameExists = false;

        while (empFileCheck >> id >> firstName >> lastName >> deptCode >> position) {
            if (id == emp.getId()) {
                exists = true;
                break;
            }
            if (firstName == emp.getFirstName() && lastName == emp.getLastName()) {
                nameExists = true;
                break;
            }
        }
        empFileCheck.close();

        if (exists) {
            cout << endl << "ℹ️\t Record with Employee Id: " << emp.getId() << " already exists. Cannot add duplicate." << endl << endl;
            return;
        }
        if (nameExists) {
            cout << endl << "ℹ️\t Record with Employee name: " << emp.getFirstName() << " " << emp.getLastName() << " already exists. Cannot add duplicate." << endl << endl;
            return;
        }

        ofstream empFile(EMP_FILE_NAME, ios::app);
        ofstream empPayrollFile(EMP_PAYROLL_FILE_NAME, ios::app);
        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);

        writeRecord(empFile, empPayrollFile, emp);
        empFile.close();
        empPayrollFile.close();
        cout << endl << "✅\t Record with Employee Id: " << emp.getId() << " added successfully." << endl;
        cout << endl;

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}


// Function: Update employee record
void Employee::updateRecord(int updateId) {
    try {
        bool found = false;
        ifstream empFile(EMP_FILE_NAME);
        ofstream empTempFile(TEMP_EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);
        ofstream tempEmpPayrollFile(TEMP_EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);
        checkFileAccess(empTempFile);
        checkFileAccess(tempEmpPayrollFile);

        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        while (empFile >> id >> firstName >> lastName >> deptCode >> position &&
               empPayrollFile >> id >> deptCode >> hrs) {
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            if (updateId == emp.getId()) {
                found = true;

                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|           EMPLOYEE RECORD FOUND                  |" << endl;
                cout << "+--------------------------------------------------+" << endl;
                emp.display();
                cout << "\nPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();

                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|           UPDATE EMPLOYEE INFORMATION             |" << endl;
                cout << "+---------------------------------------------------+" << endl;

                Employee updateEmp = createEmployee(updateId);
                empTempFile << updateEmp.getId() << "\t" << updateEmp.getFirstName() << "\t" 
                            << updateEmp.getLastName() << "\t" << updateEmp.getDepartmentCode() << "\t" 
                            << updateEmp.getPosition() << endl;
                tempEmpPayrollFile << updateEmp.getId() << "\t" << updateEmp.getDepartmentCode() << "\t" 
                                   << updateEmp.getHoursWorked() << endl;

                cout << "\n\n\t\t\a\n[✅ Record with Employee Id: " << updateId << " has been updated" << endl << endl;
            } else {
                writeRecord(empTempFile, tempEmpPayrollFile, emp);
            }
        }

        if (!found) {
            cout << "\t\t\a\n[ ℹ️\t Record with Employee Id : " << updateId << " does not exist!!!\n\n";
        }

        empFile.close();
        empTempFile.close();
        empPayrollFile.close();
        tempEmpPayrollFile.close();

        remove(EMP_FILE_NAME.c_str());
        rename(TEMP_EMP_FILE_NAME.c_str(), EMP_FILE_NAME.c_str());
        remove(EMP_PAYROLL_FILE_NAME.c_str());
        rename(TEMP_EMP_PAYROLL_FILE_NAME.c_str(), EMP_PAYROLL_FILE_NAME.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: View employee record
void Employee::viewRecord(int searchId) {
    try {
        ifstream empFile(EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);

        bool found = false;
        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        while (empFile >> id >> firstName >> lastName >> deptCode >> position && 
               empPayrollFile >> id >> deptCode >> hrs) {
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);
    
            if (searchId == emp.getId()) {
                found = true;
                emp.display();
                break;
            }
        }

        if (!found) {
            cout << "\t\t\a\n[ℹ️ Record with Employee Id : " << searchId << " does not exist!!! ]\n\n";
        }

    } catch (exception &i) {
        cerr << i.what();
    }
}

// Function: View all employee records
void Employee::viewAllRecord() {
    try {
        ifstream empFile(EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);

        int recordCount = 0;
        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        while (empFile >> id >> firstName >> lastName >> deptCode >> position && 
               empPayrollFile >> id >> deptCode >> hrs) {
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            ++recordCount;
            emp.display();
            cout << endl;
        }

        if (recordCount == 0) {
            cout << "\t\t\a\n [ℹ️ No record(s) Employee exist!!! ]\n\n";
        }

    } catch (exception &i) {
        cerr << i.what();
    }
}

// Function: Delete employee record
void Employee::deleteRecord(int deleteId) {
    try {
        bool found = false;
        ifstream empFile(EMP_FILE_NAME);
        ofstream empTempFile(TEMP_EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);
        ofstream tempEmpPayrollFile(TEMP_EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);
        checkFileAccess(empTempFile);
        checkFileAccess(tempEmpPayrollFile);

        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        while (empFile >> id >> firstName >> lastName >> deptCode >> position &&
               empPayrollFile >> id >> deptCode >> hrs) {
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            if (deleteId == emp.getId()) {
                found = true;

                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|           EMPLOYEE RECORD FOUND                  |" << endl;
                cout << "+--------------------------------------------------+" << endl;
                emp.display();
                cout << "\n+--------------------------------------------------+" << endl;

                cout << "❗ Are you sure you want to delete this record? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y') {
                    cout << "\n❌ Deleting record..." << endl;
                    // Do not write this record to temp files (effectively deleting)
                    continue;
                } else {
                    cout << "\n❌ Deletion cancelled. Record will be kept." << endl;
                }
            }

            writeRecord(empTempFile, tempEmpPayrollFile, emp);
        }

        if (!found) {
            cout << "\t\t\a\n [ℹ️ Record with Employee Id : " << deleteId << " does not exist!!! ]\n\n";
        }

        empFile.close();
        empTempFile.close();
        empPayrollFile.close();
        tempEmpPayrollFile.close();

        remove(EMP_FILE_NAME.c_str());
        rename(TEMP_EMP_FILE_NAME.c_str(), EMP_FILE_NAME.c_str());
        remove(EMP_PAYROLL_FILE_NAME.c_str());
        rename(TEMP_EMP_PAYROLL_FILE_NAME.c_str(), EMP_PAYROLL_FILE_NAME.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
