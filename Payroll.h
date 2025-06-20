#ifndef PAYROLL_H
#define PAYROLL_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
using namespace std;
class Payroll
{
private:
    // Member variables
    int id;
    string firstName;
    string lastName;
    int departmentCode;
    string position;
    float hoursWorked;
    float basicPay;
    float overtimePay;
    float grossPay;

public:

    // Default constructor
    Payroll();

    // Copy constructor
    Payroll(int id, const string &firstName, const string &lastName,
            int departmentCode, const string &position,
            float hoursWorked, float basicPay,
            float overtimePay, float grossPay);
    Payroll(const Payroll &payroll);

    // Destructor
    ~Payroll();

    // Mutators
    void setId(int empId);
    void setFirstName(const string &fn);
    void setLastName(const string &ln);
    void setDepartmentCode(int deptCode);
    void setPosition(const string &post);
    void setHoursWorked(float hr);
    void setBasicPay(float bPay);
    void setOvertimePay(float otPay);
    void setGrossPay(float grssPay);

    // Accessors
    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    int getDepartmentCode() const;
    string getPosition() const;
    float getHoursWorked() const;
    float getBasicPay() const;
    float getOvertimePay() const;
    float getGrossPay() const;

    // Display method
    void display() const;
};

#endif // PAYROLL_H
