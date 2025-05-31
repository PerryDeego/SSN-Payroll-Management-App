//........Preprocessor Directives........||					                                  
#include <string> 
#include <iostream> 
#include <iomanip>  // For setw, left, right
#include <unistd.h> // for usleep
#include <cstdlib>  // for system
#include <stdexcept> 
#include <fstream>
#include <ctime>    // for date/time
#include <iomanip>
#include <limits>   // for numeric_limits
//.......................................||
#include "Employee.h"
#include "Department.h"
#include "EmpNode.h"
#include "EmpList.h"
#include "PayList.h"
//.......................................||
using namespace std;


//------------- method prototypes -------||
void mainConsole();
void departmentConsole();
void employeeConsole();
void sortEmployeeConsole();
void payrollConsole();
void payrollProcessing();
void viewSinglePayroll(int);
void sortPayrollConsole();

//---------------------------------------- methods ---------------------------------------||

// Function: Clear screen 
void clearScreen() {
	system("clear");  
}

void printDateTime() {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	// Format: YYYY-MM-DD HH:MM:SS
	cout << "\t---------------------------------------------------------------\n";
	cout << "\t|\t\tDate: " 
		 << 1900 + ltm->tm_year << "-"
		 << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
		 << setw(2) << setfill('0') << ltm->tm_mday
		 << "   Time: "
		 << setw(2) << setfill('0') << ltm->tm_hour << ":"
		 << setw(2) << setfill('0') << ltm->tm_min << ":"
		 << setw(2) << setfill('0') << ltm->tm_sec
		 << "\t\t|\n";
	cout << "\t---------------------------------------------------------------\n";
}

//..

void pressEnterContinue() {
	cout << endl << endl;
	system( "read -n 1 -s -p \"Press any key to continue...\"" );
}
int mainMenu()
{
	clearScreen();
	int choice;
	cout << "\n\n\n";
	cout << "\t===============================================================\n";
	cout << "\t|                  SOFTWARE SOLUTION NOW (SSN)                |\n";
	cout << "\t|                        PAYROLL SYSTEM                       |\n";
	cout << "\t===============================================================\n";
	printDateTime();
	cout << "\t|                                                             |\n";
	cout << "\t|  0. EXIT PROGRAM                                            |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  1. DEPARTMENT RECORD                                       |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  2. EMPLOYEE RECORDS                                        |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  3. PAYROLL RECORDS                                         |\n";
	cout << "\t|                                                             |\n";
	cout << "\t===============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;
	return choice;
}

int departmentMenu()
{
	clearScreen();
	int choice;
	cout << "\n\n\n";
	cout << "\t==================== DEPARTMENT MAIN MENU =====================\n";
	printDateTime();
	cout << "\t|                                                             |\n";
	cout << "\t|  0. RETURN TO MAIN                                          |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  1. ADD DEPARTMENT                                          |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  2. UPDATE DEPARTMENT                                       |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  3. VIEW DEPARTMENT                                         |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  4. VIEW ALL DEPARTMENTS                                    |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  5. DELETE DEPARTMENT                                       |\n";
	cout << "\t|                                                             |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;
	return choice;
}

int employeeMenu()
{
	clearScreen();
	int choice;
	cout << "\n\n\n";
	cout << "\t===================== EMPLOYEE MAIN MENU ======================\n";
	printDateTime();
	cout << "\t|                                                             |\n";
	cout << "\t|  0. RETURN TO MAIN                                          |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  1. ADD EMPLOYEE                                            |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  2. UPDATE EMPLOYEE                                         |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  3. VIEW EMPLOYEE                                           |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  4. VIEW SORTED EMPLOYEE                                    |\n";
	cout << "\t|                                                             |\n";
	cout << "\t|  5. DELETE EMPLOYEE                                         |\n";
	cout << "\t|                                                             |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;
	return choice;
}


void payrollLogo()
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

	cout << "\n\n";
	cout << "\t" << setfill('=') << setw(total_width) << "=" << setfill(' ') << endl;
	cout << "\t|"
		 << setw(total_width - 2) << left << "                                   SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM"
		 << "|\n";
	cout << "\t" << setfill('=') << setw(total_width) << "=" << setfill(' ') << endl;

	cout <<"\t" << "| " << left << setw(width_id) << "ID"
		<< "| " << left << setw(width_first) << "FIRST NAME"
		<< "| " << left << setw(width_last) << "LAST NAME"
		<< "| " << left << setw(width_dept) << "DEPT CODE"
		<< "| " << left << setw(width_pos) << "POSITION"
		<< "| " << right << setw(width_hours) << "HOURS"
		<< "| " << right << setw(width_basic) << "BASIC PAY"
		<< "| " << right << setw(width_ot) << "OVERTIME PAY"
		<< "| " << right << setw(width_gross) << "GROSS PAY"
		<< " |" << endl;
}

int payrollMenu()
{
	clearScreen();

	int choice;

	cout << "\n\n";
	cout << "\t==================== PROCESS PAYROLL MENU ====================\n";
	printDateTime();
	cout << "\t|                                                            |\n";
	cout << "\t|  0. RETURN TO MAIN                                         |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  1. PROCESS PAYROLL                                        |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  2. VIEW PAYROLL                                           |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  3. VIEW SORTED PAYROLL                                    |\n";
	cout << "\t|                                                            |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;

	return choice;
}

int sortedEmployeeMenu()
{
	clearScreen();

	int choice;

	cout << "\n\n";
	cout << "\t================ SORT EMPLOYEE RECORD MENU ===================\n";
	printDateTime();
	cout << "\t|                                                            |\n";
	cout << "\t|  0. RETURN TO EMPLOYEE MENU                                |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  1. SORT BY ID                                             |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  2. SORT BY LAST NAME                                      |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  3. SORT BY DEPARTMENT                                     |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  4. SORT BY POSITION                                       |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  5. SORT BY HOURS WORKED                                   |\n";
	cout << "\t|                                                            |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;

	return choice;
}

int sortedPayrollMenu()
{
	clearScreen();

	int choice;

	cout << "\n\n";
	cout << "\t================== PAYROLL SORT MAIN MENU ====================\n";
	printDateTime();
	cout << "\t|                                                            |\n";
	cout << "\t|  0. RETURN TO MAIN                                         |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  1. SORT BY ID                                             |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  2. SORT BY LAST NAME                                      |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  3. SORT BY DEPARTMENT CODE                                |\n";
	cout << "\t|                                                            |\n";
	cout << "\t|  4. SORT BY POSITION                                       |\n";
	cout << "\t|                                                            |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your selection: ";
	cin >> choice;
	cout << endl;

	return choice;
}


void createAndDisplayPayroll(const int id, const string& firstName, const string& lastName, const int deptCode,
							 const string& position, float hrs, float regularPay, float overtimePay, float grossPay) {
	Payroll payroll;
	payroll.setId(id);
	payroll.setFirstName(firstName);
	payroll.setLastName(lastName);
	payroll.setDepartmentCode(deptCode);
	payroll.setPosition(position);
	payroll.setHoursWorked(hrs);
	payroll.setBasicPay(regularPay);
	payroll.setOvertimePay(overtimePay);
	payroll.setGrossPay(grossPay);
	payroll.display();
}



// Utility function to check file access
bool checkFileAccess(ios& file) {
    if (file.fail()) {
        throw runtime_error("[❌ ERROR ACCESSING FILE! ]");
    }
    return true; // Return true if no error
}



//---------------------------- Payroll Calculations ---------------------------------||
float calculateRegularPay(float hourlyRate, float hoursWorked)
{
    return hourlyRate * hoursWorked;
}

float calculateOvertimePay(float extraHours, float hourlyRate)
{
    return extraHours * hourlyRate * 1.5; // Consider using a constant for 1.5
}

float calculateGrossPay(float regularPay, float overtimePay)
{
    return regularPay + overtimePay;
}