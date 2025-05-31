//........Preprocessor Directives.......||
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string> // Include string header for std::string

class Employee {
private:
    int id;
    std::string firstName;
    std::string lastName;
    int departmentCode;
    std::string position;
    float hoursWorked;

public:
    // Destructor
    ~Employee();

    // Default constructor
    Employee();

    // Primary constructor
    Employee(int id, const std::string& firstName, const std::string& lastName, 
             int departmentCode, const std::string& position, float hoursWorked);

    // Copy constructor
    Employee(const Employee &Emp);

    // Mutators
    void setId(int empId);
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setDepartmentCode(int deptCode);
    void setPosition(const std::string& post);
    void setHoursWorked(float hr);

    // Accessors
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    int getDepartmentCode() const;
    std::string getPosition() const;
    float getHoursWorked() const;

    //--------- Methods -----------//
    void display() const;
    std::string getValidatedString(const std::string& prompt);
    float getValidatedFloat(const std::string& prompt);
    int getValidatedInt(const std::string& prompt);

    void writeRecord(std::ofstream& empFile, std::ofstream& empPayrollFile, const Employee& emp);
    Employee createEmployee(int empId);
    bool checkFileAccess(std::ios& file);
    void addRecord(const Employee& emp);
    void updateRecord(int empId);
    void viewRecord(int empId);
    void viewAllRecord();
    void deleteRecord(int empId);
	
};

#endif // EMPLOYEE_H
