//........Preprocessor Directives.......||
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

class Employee {
private:
    int id;
    string firstName;
    string lastName;
    int departmentCode;
    string position;
    float hoursWorked;

public:
    // Destructor
    ~Employee();

    // Default constructor
    Employee();

    // Primary constructor
    Employee(int id, const string& firstName, const string& lastName, 
             int departmentCode, const string& position, float hoursWorked);

    // Copy constructor
    Employee(const Employee &Emp);

    // Mutators
    void setId(int empId);
    void setFirstName(const string& fn);
    void setLastName(const string& ln);
    void setDepartmentCode(int deptCode);
    void setPosition(const string& post);
    void setHoursWorked(float hr);

    // Accessors
    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    int getDepartmentCode() const;
    string getPosition() const;
    float getHoursWorked() const;

    //--------- Methods -----------//
    void displayHeader() const;
    void display() const;
    string getValidatedString(const string& prompt);
    float getValidatedFloat(const string& prompt);
    int getValidatedInt(const string& prompt);

    void writeRecord(ofstream& empFile, ofstream& empPayrollFile, const Employee& emp);
    Employee createEmployee(int empId);
    bool checkFileAccess(ifstream& file, const string& filename);
    bool checkFileAccess(ofstream& file, const string& filename);
    void addRecord(const Employee& emp);
    void updateRecord(int empId);
    void viewRecord(int empId);
    void viewAllRecords();
    void deleteRecord(int empId);
	
};

#endif // EMPLOYEE_H
