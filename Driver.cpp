
/*
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
-- Description: This Management System (PMS) designed to manage the payroll for SSN  Management System (PMS)
-- Created by: D. Perry 
-- Created date : June 2, 2018
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
*/

//........Preprocessor Directives........||					                                  
#include <string> 
#include <iostream> 
#include <unistd.h> // for usleep
#include <cstdlib>  // for system
#include <stdexcept> 
#include <fstream>
//.......................................||
#include "Employee.h"
#include "Department.h"
#include "EmpNode.h"
#include "EmpList.h"
#include "PayList.h"
//.......................................||
using namespace std;

//------------- method prototypes -------||
int mainMenu();
int departmentMenu();
int employeeMenu();
int payrollMenu();
int sortedEmployeeMenu();
int sortedPayrollMenu();
void mainConsole();
void departmentConsole();
void employeeConsole();
void sortEmployeeConsole();
void payrollLogo();
void payrollConsole();
void payrollProcessing();
void viewSinglePayroll(int);
void sortPayrollConsole();
float calculateOvertimePay(float, float);
float calculateGrossPay(float, float);
float calculateRegularPay(float, float);

// Function: Clear screen 
void clearScreen();

// Function: Enter input to continue
void pressEnterContinue();


//......................................||
int main()
{
    try {
        mainConsole();
        cout << "\n\t\t[SHUTTING DOWN SYSTEM!]\n\n";
    }
    catch (runtime_error &r)
    {
        cerr << r.what() << endl;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Something unexpected has occurred." << endl;
    }

    pressEnterContinue();
    return 0;
}


//---------------------------------------- methods ---------------------------------------||

// Function: Clear screen 
void clearScreen() {
    system("clear");  
}

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
	cout << "\t|  0. EXIT PROGRAM                                            |\n";
	cout << "\t|  1. DEPARTMENT RECORD                                       |\n";
	cout << "\t|  2. EMPLOYEE RECORDS                                        |\n";
	cout << "\t|  3. PAYROLL RECORDS                                         |\n";
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
	cout << "\t|  0. RETURN TO MAIN                                          |\n";
	cout << "\t|  1. ADD DEPARTMENT                                          |\n";
	cout << "\t|  2. UPDATE DEPARTMENT                                       |\n";
	cout << "\t|  3. VIEW DEPARTMENT                                         |\n";
	cout << "\t|  4. VIEW ALL DEPARTMENTS                                    |\n";
	cout << "\t|  5. DELETE DEPARTMENT                                       |\n";
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
	cout << "\t|  0. RETURN TO MAIN                                          |\n";
	cout << "\t|  1. ADD EMPLOYEE                                            |\n";
	cout << "\t|  2. UPDATE EMPLOYEE                                         |\n";
	cout << "\t|  3. VIEW EMPLOYEE                                           |\n";
	cout << "\t|  4. VIEW SORTED EMPLOYEE                                    |\n";
	cout << "\t|  5. DELETE EMPLOYEE                                         |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your option: ";
	cin >> choice;
	cout << endl;
	return choice;
}

void payrollLogo()
{
	cout << "\n\n";
	cout << "\t\t=============================================================================================================================\n";
	cout << "\t\t|                                                                                                                           |\n";
	cout << "\t\t|                                         SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                               	     |\n";
	cout << "\t\t|                                                                                                                           |\n";
	cout << "\t\t=============================================================================================================================\n";
	cout << "\t\t|  ID.No  |  First Name  |  Last Name   | Dept. Code |  Position   | Worked Hours | Regular Pay | Overtime Pay | Gross Pay  |\n";
	cout << "\t\t-----------------------------------------------------------------------------------------------------------------------------\n";
	cout << "\n\n";
} 

int payrollMenu()
{
	clearScreen();
	int choice;

	cout << "\n\n";
	cout << "\t==================== PROCESS PAYROLL MENU ====================\n";
	cout << "\t|  0. RETURN TO MAIN                                         |\n";
	cout << "\t|  1. PROCESS PAYROLL                                        |\n";
	cout << "\t|  2. VIEW PAYROLL                                           |\n";
	cout << "\t|  3. VIEW SORTED PAYROLL                                    |\n";
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
	cout << "\t|  0. RETURN TO EMPLOYEE MENU                                |\n";
	cout << "\t|  1. SORT BY ID                                             |\n";
	cout << "\t|  2. SORT BY LAST NAME                                      |\n";
	cout << "\t|  3. SORT BY DEPARTMENT                                     |\n";
	cout << "\t|  4. SORT BY POSITION                                       |\n";
	cout << "\t|  5. SORT BY HOURS WORKED                                   |\n";
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
	cout << "\t|  0. RETURN TO MAIN                                         |\n";
	cout << "\t|  1. SORT BY ID                                             |\n";
	cout << "\t|  2. SORT BY LAST NAME                                      |\n";
	cout << "\t|  3. SORT BY DEPARTMENT CODE                                |\n";
	cout << "\t|  4. SORT BY POSITION                                       |\n";
	cout << "\t==============================================================\n";
	cout << "\n\tEnter your selection: ";
	cin >> choice;
	cout << endl;

	return choice;
}


void employeeConsole()
{
	clearScreen();
	int choice;
	Employee empObject;
	Employee *empPtr = new Employee();

	cout << endl << endl << endl << endl;
	while  ((choice = employeeMenu())) // while true
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\t~~~~~~~~~~ RETURNING TO  MAIN ~~~~~~~~~~ " << endl << endl;
			usleep(3000000); // Sleep for 1 second (1 million microseconds)
			clearScreen();
			break;
		} // end if

		switch (choice)
		{
		case 1:
			while (true)
			{
				int id;

				cout << " \t~~~~~~~~~~~~ ADD EMPLOYEE ~~~~~~~~~~~~~~" << endl << endl;
				cout << "Enter Employee id or [-1 to quit] : ";
				cin >> id;
				cout << endl;
				if (id == -1)
					break;

				empObject = empPtr->createEmployee(id);
				empPtr->addRecord(empObject);
				empPtr = nullptr;
				usleep(3000000); // Sleep for 1 second (1 million microseconds)
				clearScreen();

			} // end while

			clearScreen();
			break;

		case 2:
			while (true)
			{
				try {
					int updateId; // declaration of id to look up record
					cout << "\t~~~~~~~~~~~ UPDATE EMPLOYEE ~~~~~~~~~~~~~" << endl << endl;

					cout << "ENTER EMPLOYEE ID TO UPDATE RECORD OR [-1] TO QUIT : ";
					cin >> updateId; // input id use to look employee record
					cout << endl << endl;

					if (cin.fail())
					{
						cin.clear();
						throw invalid_argument("\t\tNOT A VALID EMPLOYEE ID!");
					} // end if

					if (updateId == -1) // use to exit loop
						break;

					empPtr->updateRecord(updateId);
					empPtr = nullptr;
				} // end try
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				} // end catch

				usleep(3000000); // Sleep for 1 second (1 million microseconds)
				clearScreen();
			} // end while

			clearScreen();
			break;
		case 3:
			while (true)
			{
				try {
					int searchId; // declaration of id to look up record
					cout << "\t~~~~~~~~~~~~~ VIEW EMPLOYEE ~~~~~~~~~~~~~" << endl << endl;

					cout << "ENTER EMPLOYEE ID TO LOOKUP RECORD OR [-1] TO QUIT : ";
					cin >> searchId; // input id use to look employee record
					cout << endl << endl;

					if (cin.fail())
					{
						cin.clear();
						throw invalid_argument("\t\tNOT A VALID EMPLOYEE ID!");
					} // end if

					if (searchId == -1) // use to exit loop
						break;

					empPtr->viewRecord(searchId);
					empPtr = nullptr;
				} // end try
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				} // end catch

				usleep(3000000); // Sleep for 1 second (1 million microseconds)
				clearScreen();
			} // end while

			clearScreen();
			break;

		case 4:
			cout << "\t~~~~~~~~~~~~~ VIEW SORTED EMPLOYEE ~~~~~~~~~~~~~" << endl << endl;
			sortEmployeeConsole();

			pressEnterContinue();
			clearScreen();
			break;
		case 5:
			while (true)
			{
				try {
					int deleteId; // declaration of intervention record look up number
					cout << "\t~~~~~~~~~~~~~ DELETE EMPLOYEE ~~~~~~~~~~~~~" << endl << endl;

					cout << "ENTER EMPLOYEE ID TO DELETE RECORD OR [-1] TO QUIT : ";
					cin >> deleteId; // number use to look intervention record
					cout << endl << endl;

					if (cin.fail())
					{
						cin.clear();
						throw invalid_argument("\t\tNOT A VALID EMPLOYEE ID!");
					} // end if

					if (deleteId == -1) // condition use to exit loop
						break;

					empPtr->deleteRecord(deleteId);
					empPtr = nullptr;
				} // end try
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				} // end catch

				usleep(3000000); // Sleep for 1 second (1 million microseconds)
				clearScreen();
			} // end while

			clearScreen();
			break;
		default:
			cout << endl << endl << endl;
			cout << "\t\t\a Incorrect selection. Try again." << endl;
			usleep(3000000); // Sleep for 1 second (1 million microseconds)
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		} // end case
	} // end while
}

void sortEmployeeConsole()
{
    clearScreen();
    int choice;
    int listSize = 0;
    EmpList *emplist = new EmpList();

    //------------------ read objects from employee file --------------------------//
    string empFileName = "employee.txt";
    string empPayrollFileName = "employeepayroll.txt";

    try {
        ifstream empFile(empFileName, ios::in);
        ifstream empPayrollFile(empPayrollFileName, ios::in);

        int id, empId;
        string firstName;
        string lastName;
        int departmentCode, deptCode;
        string position;
        float hoursWorked;
        int existingNodes = 0;
        Employee emp;

        if (empFile.fail() || empPayrollFile.fail())
        {
            throw runtime_error("ERROR ACCESSING FILE!");
        }

        while (empFile >> id >> firstName >> lastName >> departmentCode >> position &&
               empPayrollFile >> empId >> deptCode >> hoursWorked)
        {
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(departmentCode);
            emp.setPosition(position);
            emp.setHoursWorked(hoursWorked);

            if (emp.getId() == empId && emp.getDepartmentCode() == deptCode)
            {
                emplist->insertAtFront(emp); // initialize list
                ++existingNodes;
            }
        }

        if (existingNodes == 0)
        {
            cout << "\t\t\a\nNo node(s) exist for Employees!!!\n\n";
        }

        empFile.close();
        empPayrollFile.close();

    } catch (exception &i) {
        cerr << i.what();
    }
    //-----------------------------------------------------------------------//

    cout << endl << endl << endl << endl;
    while ((choice = sortedEmployeeMenu())) // loop while choice does not = 0
    {
        clearScreen();
        if (choice == 0)
        {
            cout << "\t~~~~~~~~~~ RETURNING TO MAIN ~~~~~~~~~~ " << endl << endl;
            usleep(3000000); // Sleep for 3 seconds
            clearScreen();
            break;
        }

        listSize = emplist->countNodes(); // count nodes that were added to employee list

        switch (choice)
        {
        case 1:
            cout << " \t~~~~~~~~~~~~ SORT EMPLOYEE RECORDS BY ID ~~~~~~~~~~~~~~" << endl << endl;
            emplist->mergeSortById();
            emplist->traverse();
            break;

        case 2:
            cout << " \t~~~~~~~~~~~~ SORT EMPLOYEE RECORDS BY LAST NAME ~~~~~~~~~~~~~~" << endl << endl;
            emplist->mergeSortByLastName();
            emplist->traverse();
            break;

        case 3:
            cout << " \t~~~~~~~~~~~~ SORT EMPLOYEE RECORDS BY DEPARTMENT CODE ~~~~~~~~~~~~~~" << endl << endl;
            emplist->mergeSortByDepartmentCode();
            emplist->traverse();
            break;

        case 4:
            cout << " \t~~~~~~~~~~~~ SORT EMPLOYEE RECORDS BY POSITION ~~~~~~~~~~~~~~" << endl << endl;
            emplist->mergeSortByPosition();
            emplist->traverse();
            break;

        case 5:
            cout << " \t~~~~~~~~~~~~ SORT EMPLOYEE RECORDS BY WORKED HOURS ~~~~~~~~~~~~~~" << endl << endl;
            emplist->mergeSortByHoursWorked(); // Use merge sort instead of bubble sort
            emplist->traverse();
            break;

        default:
            cout << endl << endl << endl;
            cout << "\t\t\a Incorrect selection. Try again." << endl;
            usleep(3000000); // Sleep for 3 seconds
            clearScreen();
            cin.clear();
            cin.ignore();
            break;
        }
        pressEnterContinue(); // Prompt to continue after each operation
        clearScreen();
    }

    delete emplist; // Clean up dynamically allocated memory
}



void departmentConsole()
{
	clearScreen();
	int choice;
	Department deptObject;
	Department *deptPtr = new Department();

	cout << endl << endl;
	while ((choice = departmentMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t[RETURNING TO MAIN MENU]\n" << endl;
			usleep(1000000); // Shorter pause for better UX
			clearScreen();
			break;
		}

		switch (choice)
		{
		case 1:
			cout << "\n\t================= ADD DEPARTMENT =================\n";
			while (true)
			{
				int code;
				cout << "\nEnter Department code or [-1 to quit]: ";
				cin >> code;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\t[!] Invalid input. Please enter a valid department code.\n";
					continue;
				}
				if (code == -1)
					break;

				deptObject = deptPtr->createDepartment(code);
				deptPtr->addRecord(deptObject);
				deptPtr = nullptr;
				cout << "\n\t[+] Department added.\n";
				usleep(1000000);
				clearScreen();
				cout << "\n\t================= ADD DEPARTMENT =================\n";
			}
			clearScreen();
			break;

		case 2:
			cout << "\n\t================= UPDATE DEPARTMENT ==============\n";
			while (true)
			{
				try {
					int updateCode;
					cout << "\nEnter Department code to update or [-1 to quit]: ";
					cin >> updateCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[!] Not a valid department code!");
					}
					if (updateCode == -1)
						break;

					deptPtr->updateRecord(updateCode);
					deptPtr = nullptr;
					cout << "\n\t[~] Department updated.\n";
				}
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
				cout << "\n\t================= UPDATE DEPARTMENT ==============\n";
			}
			clearScreen();
			break;

		case 3:
			cout << "\n\t================== VIEW DEPARTMENT ===============\n";
			while (true)
			{
				try {
					int searchCode;
					cout << "\nEnter Department code to view or [-1 to quit]: ";
					cin >> searchCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[!] Not a valid department code!");
					}
					if (searchCode == -1)
						break;

					deptPtr->viewRecord(searchCode);
					deptPtr = nullptr;
				}
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
				cout << "\n\t================== VIEW DEPARTMENT ===============\n";
			}
			clearScreen();
			break;

		case 4:
			cout << "\n\t================== ALL DEPARTMENTS ===============\n";
			deptPtr->viewAllRecords(); // Correct method name
			deptPtr = nullptr;
			pressEnterContinue();
			clearScreen();
			break;

		case 5:
			cout << "\n\t================= DELETE DEPARTMENT ==============\n";
			while (true)
			{
				try {
					int deleteCode;
					cout << "\nEnter Department code to delete or [-1 to quit]: ";
					cin >> deleteCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[!] Not a valid department code!");
					}
					if (deleteCode == -1)
						break;

					deptPtr->deleteRecord(deleteCode);
					deptPtr = nullptr;
					cout << "\n\t[-] Department deleted.\n";
				}
				catch (invalid_argument &e) {
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
				cout << "\n\t================= DELETE DEPARTMENT ==============\n";
			}
			clearScreen();
			break;

		default:
			cout << "\n\t[!] Incorrect selection. Try again.\n";
			usleep(1000000);
			clearScreen();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}
	}
}


void payrollProcessing()
{
	string ratesFileName = "rates.txt";
	string empFileName = "employee.txt";
	string empPayrollFileName = "employeepayroll.txt";
	string payrollFileName = "monthlyPayroll.txt";

	payrollLogo();
	
	try
	{
		ifstream ratesFile(ratesFileName, ios::in);
		ifstream empFile(empFileName, ios::in);
		ifstream empPayrollFile(empPayrollFileName, ios::in);
		ofstream payrollFile(payrollFileName, ios::app);

		Department dept;
		int code;
		float hrRate, otRate;

		bool assignToDept = false;
		bool payment = false;

		Employee emp;
		int id, payrollId, payrollDeptCode, deptCode;
		string fn, ln, post;
		float hrs;


		// local variable declaration 
		int baseHrs = 40;
		float deptRate = 0.0;
		float overtimeRate = 0.0;
		float workedHours = 0.0;
		float overtimePay;
		float regularPay;
		float grossPay;


		if (ratesFile.fail() || empFile.fail() || empPayrollFile.fail() || payrollFile.fail())
		{
			throw runtime_error("ERROR ACCESSING FILE!");
		} // end if

		while (true)
		{
			ratesFile >> code >> hrRate >> otRate;

			dept.setCode(code);
			dept.setHourlyRate(hrRate);
			dept.setOvertimeRate(otRate);

			empFile >> id >> fn >> ln >> deptCode >> post; // read and store employee details from file in to local variables
			empPayrollFile >> payrollId >> payrollDeptCode >> hrs; // read and store employee payroll details from file in to local variables

			emp.setId(id);
			emp.setFirstName(fn);
			emp.setLastName(ln);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(post);
			emp.setHoursWorked(hrs);

			if (emp.getDepartmentCode() == dept.getCode()) // validates employee is assigned to the department with a rate
			{
				assignToDept = true;
				
				workedHours = emp.getHoursWorked();
				deptRate = dept.getHourlyRate();
				overtimeRate = dept.getOvertimeRate();

				if (workedHours > 0)
				{
					payment = true; // employee have a payroll	
				} // end if

			} // end if

			  //--------------------- calculate employee payroll -------------------------------//
			if (assignToDept && payment)
			{
				if (workedHours > baseHrs) // validates calculation of overtime if worked hours exceed 40hrs
				{
					float extraHours = 0.0;

					extraHours = workedHours - baseHrs;
					regularPay = calculateRegularPay(deptRate, workedHours);
					overtimePay = calculateOvertimePay(extraHours, overtimeRate);
				} // end if
				else if (workedHours > 0 && workedHours < baseHrs)
				{
					regularPay = calculateRegularPay(deptRate, workedHours);
					overtimePay = 0.0;
				} // end else if
				else
				{
					regularPay = 0.0;
					overtimePay = 0.0;
				} // end else

				grossPay = calculateGrossPay(regularPay, overtimePay);
			} // end if

		
			cout << "    " << emp.getId() << "\t\t" << emp.getFirstName() << "\t\t" << emp.getLastName() << "\t\t" << emp.getDepartmentCode() << "  " << "\t\t" << emp.getPosition() << "\t\t" << emp.getHoursWorked() << "\t\t" << regularPay << "\t\t" << overtimePay << "\t\t" << grossPay << endl << endl;
			payrollFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t" << emp.getPosition() << "\t" << emp.getHoursWorked() << "\t" << regularPay << "\t" << overtimePay << "\t" << grossPay << endl;

			if (ratesFile.eof() || empFile.eof() || empPayrollFile.eof())
				break;

			pressEnterContinue();
		} // end while

		ratesFile.close(); // close rates file 
		empFile.close(); // close employee file
		empPayrollFile.close(); // close employee payroll file
		payrollFile.close(); // close monthly payroll file

	} // end try
	catch (exception &i)
	{
		cerr << i.what();
	} // end catch
}


void viewSinglePayroll(int searchId)
{
	string payrollFileName = "monthlyPayroll.txt";

	try
	{
		ifstream payrollFile(payrollFileName, ios::in);

		bool found = false;

		int id, deptCode;
		string fn, ln, post;
		float hrs;

		float regularPay, overtimePay, grossPay;

		if (payrollFile.fail())
		{
			throw runtime_error("ERROR ACCESSING FILE!");
		} // end if

		while (!payrollFile.eof())
		{
			payrollFile >> id >> fn >> ln >> deptCode >> post >> hrs >> regularPay >> overtimePay >> grossPay;

			if (searchId == id)
			{
				found = true; // validates that lookup record was found

				payrollLogo();
				cout << "|  ID.No  |   First Name   |   Last Name   |   Dept. Code   |   Position Hours   |   Worked Hours   |   Regular Pay   |   Overtime Pay   |   Gross Pay  |" << endl << endl;
				cout << "    " << id << "\t\t" << fn << "\t\t" << ln << "\t\t" << deptCode << "  " << "\t\t" << post << "\t\t" << hrs << "\t\t" << regularPay << "\t\t" << overtimePay << "\t\t" << grossPay << endl << endl;

				break;
			} // end if 
				
		} // end while

		if (found == false)
		{
			cout << "\t\t\a\nRecord with Department Code : " << searchId << " does not exist!!!\n\n";
		} // end if


		payrollFile.close(); // close department file
		
	} // end try
	catch (exception &i)
	{
		cerr << i.what();
	} // end catch
	
}

void sortPayrollConsole()
{
    clearScreen();
    int choice;
    int listSize = 0;
    PayList *payrollList = new PayList();

    string monthlyPayrollFileName = "monthlyPayroll.txt";

    try {
    ifstream payFile(monthlyPayrollFileName, ios::in);

    int empId;
    string firstName;
    string lastName;
    int deptCode;
    string position;
    float hoursWorked;
    float regularPay;
    float otPay;
    float grossPay;
    int existingNodes = 0;
    Payroll payroll;

    if (payFile.fail())
    {
        throw runtime_error("ERROR ACCESSING FILE!");
    }

    // Only insert if the read was successful
    while (payFile >> empId >> firstName >> lastName >> deptCode >> position >> hoursWorked >> regularPay >> otPay >> grossPay)
    {
        payroll.setId(empId);
        payroll.setFirstName(firstName);
        payroll.setLastName(lastName);
        payroll.setDepartmentCode(deptCode);
        payroll.setPosition(position);
        payroll.setHoursWorked(hoursWorked);
        payroll.setBasicPay(regularPay);
        payroll.setOvertimePay(otPay);
        payroll.setGrossPay(grossPay);

        payrollList->insertAtFront(payroll);
        ++existingNodes;
    }

    if (existingNodes == 0)
    {
        cout << "\t\t\a\nNo node(s) exist for Employees payroll!!!\n\n";
    }

    payFile.close();

} catch (exception &i) {
    cerr << i.what();
}

cout << endl << endl << endl << endl;
while (( choice = sortedPayrollMenu() )) // loop while choice does not = 0
{
    clearScreen();
    if (choice == 0)
    {
        cout << "\t~~~~~~~~~~ RETURNING TO  MAIN ~~~~~~~~~~ " << endl << endl;
        usleep(3000000);
        clearScreen();
        break;
    }

    listSize = payrollList->countNodes();

    payrollLogo();

    switch (choice)
    {
    case 1:
        cout << "\n\t================ SORT PAYROLL RECORDS BY ID ================\n\n";
        payrollList->mergeSortById();
        payrollList->traverse();
        cout << endl << endl << endl << endl;
        pressEnterContinue();
        clearScreen();
        break;

    case 2:
        cout << " \t~~~~~~~~~~~~ SORT PAYROLL RECORDS BY LAST NAME ~~~~~~~~~~~~~~" << endl << endl;
        payrollList->mergeSortByLastName();
        payrollList->traverse();
        cout << endl << endl << endl << endl;
        pressEnterContinue();
        clearScreen();
        break;
    case 3:
        cout << " \t~~~~~~~~~~~~ SORT PAYROLL RECORDS BY DEPARTMENT CODE ~~~~~~~~~~~~~~" << endl << endl;
        payrollList->mergeSortByDepartmentCode();
        payrollList->traverse();
        cout << endl << endl << endl << endl;
        pressEnterContinue();
        clearScreen();
        break;

    case 4:
        cout << " \t~~~~~~~~~~~~ SORT PAYROLL RECORDS BY POSITION ~~~~~~~~~~~~~~" << endl << endl;
        payrollList->mergeSortByPosition();
        payrollList->traverse();
        cout << endl << endl << endl << endl;
        pressEnterContinue();
        clearScreen();
        break;
    
    default:
        cout << endl << endl << endl;
        cout << "\t\t\a Incorrect selection. Try again." << endl;
        usleep(3000000);
        clearScreen();
        cin.clear();
        cin.ignore();
        break;
    }
}
}

void payrollConsole()
{
	clearScreen();
	int choice;

	cout << endl << endl << endl << endl;
	while (( choice = payrollMenu() )) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\t~~~~~~~~~~ RETURNING TO  MAIN ~~~~~~~~~~ " << endl << endl;
			usleep(3000000); // Sleep for 1 second (1 million microseconds)
			clearScreen();
			break;
		} // end if

		switch (choice)
		{
			case 1:
				payrollProcessing();
				cout << endl << endl << endl;

				pressEnterContinue();
				clearScreen();
				break;

			case 2:

				while (true)
				{
					try {
						int searchId; // declaration of id to look up record
						cout << "\t~~~~~~~~~~~~~ VIEW EMPLOYEE PAYROLL ~~~~~~~~~~~~~" << endl << endl;

						cout << "ENTER EMPLOYEE ID TO LOOKUP PAYROLL RECORD OR [-1] TO QUIT : ";
						cin >> searchId; // input id use to look employee record
						cout << endl << endl;

						if (cin.fail())
						{
							cin.clear();
							throw invalid_argument("\t\tNOT A VALID EMPLOYEE ID!");
						} //end if

						if (searchId == -1) // condition use to exit loop
							break;
						viewSinglePayroll(searchId);
					} // end try
					catch (invalid_argument &e) {
						cerr << e.what() << endl;
					} // end catch


					cout << endl << endl << endl << endl;
					pressEnterContinue();
					clearScreen();
				} // end while

			case 3:
				sortPayrollConsole();

				cout << endl << endl << endl;
				pressEnterContinue();
				clearScreen();
				break;
				
			default:
				cout << endl << endl << endl;
				cout << "\t\t\a Incorrect selection. Try again." << endl;
				usleep(3000000); // Sleep for 1 second (1 million microseconds)
				clearScreen();
				cin.clear();
				cin.ignore();
				break;
		} // end case



	} // end while
}

// -------------------- main application menu ----------------------//
void mainConsole()
{
	clearScreen();
	int choice;

	// ANSI escape code for bold white text: \033[1;37m
	// Reset color: \033[0m

	cout << "\033[1;37m" << endl << endl << endl << endl;
	while (( choice = mainMenu() )) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\t~~~~~~~~~~ CLOSING APPLICATION ~~~~~~~~~~ " << endl << endl;
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			break;
		} // end if

		switch (choice)
		{
		case 1:
			departmentConsole();
			break;
		case 2:
			employeeConsole();
			break;
		case 3:
			payrollConsole();
			break;
		default:
			cout << endl << endl << endl;
			cout << "\t\t\a Incorrect selection. Try again." << endl;
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		} //end case

	} //end while
	cout << "\033[0m"; // Reset color
}


//---------------------------- Payroll Calculations ---------------------------------||
float calculateRegularPay(float hourlyRate, float hoursWorked)
{
	float regularPay = 0.0;

	regularPay = hourlyRate * hoursWorked;
	return regularPay;
}

float calculateOvertimePay(float extraHours, float hourlyRate)
{
	float overtimepay = 0.0;

	overtimepay = extraHours * hourlyRate * 1.5;
	return overtimepay;
}


float calculateGrossPay(float regularPay, float overtimePay)
{
	float grossPay = 0.0;
	grossPay = regularPay + overtimePay;

	return grossPay;
}


