#include "Payroll.h"

// Destructor
Payroll::~Payroll() {}

// Default constructor
Payroll::Payroll()
    : id(0), firstName("first name"), lastName("last name"), 
      departmentCode(0), position("position"), 
      hoursWorked(0.0f), basicPay(0.0f), 
      overtimePay(0.0f), grossPay(0.0f) {}

// Default constructor
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


// Display class values
void Payroll::display() const
{
    cout << setfill(' '); // Reset fill to spaces

    cout << "\t" << " ║ "
         << right << setw(10) << getId() << " ║ "
         << left << setw(21) << getFirstName().substr(0, 21) << "║ "
         << left << setw(21) << getLastName().substr(0, 21) << "║ "
         << right << setw(14) << getDepartmentCode() << " ║ "
         << left << setw(23) << getPosition().substr(0, 23) << "║ "
         << right << setw(10) << fixed << setprecision(2) << getHoursWorked() << " ║ "
         << right << setw(10) << fixed << setprecision(2) << getBasicPay() << " ║ "
         << right << setw(14) << fixed << setprecision(2) << getOvertimePay() << " ║ "
         << right << setw(13) << fixed << setprecision(2) << getGrossPay() << " ║" << endl;
  cout << "\t" << " ╠════════════╬══════════════════════╬══════════════════════╬════════════════╬════════════════════════╬════════════╬════════════╬════════════════╬═══════════════╣" << endl;
} 
