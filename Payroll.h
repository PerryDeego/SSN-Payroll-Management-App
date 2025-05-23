#ifndef PAYROLL_H
#define PAYROLL_H

#include <iostream>
#include <string> // Include string header for std::string

class Payroll
{
public:
    // Constructors
    Payroll();
    Payroll(int id, const std::string& firstName, const std::string& lastName, 
            int departmentCode, const std::string& position, 
            float hoursWorked, float basicPay, 
            float overtimePay, float grossPay);
    Payroll(const Payroll &payroll);

    // Destructor
    ~Payroll();

    // Mutators
    void setId(int empId);
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setDepartmentCode(int deptCode);
    void setPosition(const std::string& post);
    void setHoursWorked(float hr);
    void setBasicPay(float bPay);
    void setOvertimePay(float otPay);
    void setGrossPay(float grssPay);

    // Accessors
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    int getDepartmentCode() const;
    std::string getPosition() const;
    float getHoursWorked() const;
    float getBasicPay() const;
    float getOvertimePay() const;
    float getGrossPay() const;

    // Display method
    void display() const;

private:
    // Member variables
    int id;
    std::string firstName;
    std::string lastName;
    int departmentCode;
    std::string position;
    float hoursWorked;
    float basicPay;
    float overtimePay;
    float grossPay;
};

#endif // PAYROLL_H
