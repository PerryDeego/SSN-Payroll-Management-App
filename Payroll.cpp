#include "Payroll.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

// Destructor
Payroll::~Payroll() {}

// Default constructor
Payroll::Payroll()
    : id(0), firstName("first name"), lastName("last name"), 
      departmentCode(0), position("position"), 
      hoursWorked(0.0f), basicPay(0.0f), 
      overtimePay(0.0f), grossPay(0.0f) {}

// Primary constructor
Payroll::Payroll(int id, const string& firstName, const string& lastName, 
                 int departmentCode, const string& position, 
                 float hoursWorked, float basicPay, 
                 float overtimePay, float grossPay)
    : id(id), firstName(firstName), lastName(lastName), 
      departmentCode(departmentCode), position(position), 
      hoursWorked(hoursWorked), basicPay(basicPay), 
      overtimePay(overtimePay), grossPay(grossPay) {}

// Copy constructor
Payroll::Payroll(const Payroll &payroll)
    : id(payroll.id), firstName(payroll.firstName), 
      lastName(payroll.lastName), departmentCode(payroll.departmentCode), 
      position(payroll.position), hoursWorked(payroll.hoursWorked), 
      basicPay(payroll.basicPay), overtimePay(payroll.overtimePay), 
      grossPay(payroll.grossPay) {}

// Mutators
void Payroll::setId(int empId) { id = empId; }
void Payroll::setFirstName(const string& fn) { firstName = fn; }
void Payroll::setLastName(const string& ln) { lastName = ln; }
void Payroll::setDepartmentCode(int deptCode) { departmentCode = deptCode; }
void Payroll::setPosition(const string& post) { position = post; }
void Payroll::setHoursWorked(float hr) { hoursWorked = hr; }
void Payroll::setBasicPay(float bPay) { basicPay = bPay; }
void Payroll::setOvertimePay(float otPay) { overtimePay = otPay; }
void Payroll::setGrossPay(float grssPay) { grossPay = grssPay; }

// Accessors
int Payroll::getId() const { return id; }
string Payroll::getFirstName() const { return firstName; }
string Payroll::getLastName() const { return lastName; }
int Payroll::getDepartmentCode() const { return departmentCode; }
string Payroll::getPosition() const { return position; }
float Payroll::getHoursWorked() const { return hoursWorked; }
float Payroll::getBasicPay() const { return basicPay; }
float Payroll::getOvertimePay() const { return overtimePay; }
float Payroll::getGrossPay() const { return grossPay; }

void Payroll::display() const
{
  // Define column widths
  const int width_id = 10;
  const int width_first = 20;
  const int width_last = 20;
  const int width_dept = 15;
  const int width_pos = 20;
  const int width_hours = 12;
  const int width_basic = 12;
  const int width_ot = 14;
  const int width_gross = 13;

  
  const int total_width = 1 + width_id + 2 + width_first + 2 + width_last + 2 + width_dept + 2 +
               width_pos + 2 + width_hours + 2 + width_basic + 2 + width_ot + 2 + width_gross + 2 + 1;

  cout << "\t" << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
  cout << "\t" << "| " << left << setw(width_id) << getId()
     << "| " << left << setw(width_first) << getFirstName()
     << "| " << left << setw(width_last) << getLastName()
     << "| " << left << setw(width_dept) << getDepartmentCode()
     << "| " << left << setw(width_pos) << getPosition()
     << "| " << right << setw(width_hours) << fixed << setprecision(2) << getHoursWorked()
     << "| " << right << setw(width_basic) << fixed << setprecision(2) << getBasicPay()
     << "| " << right << setw(width_ot) << fixed << setprecision(2) << getOvertimePay()
     << "| " << right << setw(width_gross) << fixed << setprecision(2) << getGrossPay()
     << " |" << endl;
    cout << "\t" << setfill('-') << setw(total_width) << "-" << setfill(' ') << endl;
}
