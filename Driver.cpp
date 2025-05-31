
/*
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
-- Description: This Management System (PMS) designed to manage the payroll for SSN  Management System (PMS)
-- Created by: D. Perry
-- Created date : June 2, 2018
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
*/

#include "Headers.h"
//....................................||
int main()
{
	try
	{
		mainConsole();
		cout << "\n\t\t[ SHUTTING DOWN SYSTEM... ! ]\n\n";
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
		cerr << "[ Something unexpected has occurred. ]" << endl;
	}

	pressEnterContinue();
	return 0;
}

// Function: Employee Console
void employeeConsole()
{
	clearScreen();

	int choice;
	Employee empObject;
	Employee *empPtr = new Employee();

	cout << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = employeeMenu()))
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t[ RETURNING TO MAIN MENU... ]\n"
				 << endl;
			usleep(1000000);
			clearScreen();
			break;
		}

		switch (choice)
		{
		case 1:
			while (true)
			{
				int id;
				clearScreen();
				cout << "\n\t======================================================\n";
				cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
				cout << "\t|                ADD NEW EMPLOYEE RECORD             |\n";
				cout << "\t======================================================\n";
				cout << "\t------------------------------------------------------\n";
				cout << "\t| Please enter the Employee ID to add a new employee |\n";
				cout << "\t------------------------------------------------------\n\n";
				cout << "Enter Employee ID or [-1 to quit]: ";
				cin >> id;
				cout << endl
					 << endl;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\t[ ℹ️ Invalid input. Please enter a valid Employee ID. ]\n";
					continue;
				}
				if (id == -1)
					break;

				empObject = empPtr->createEmployee(id);
				empPtr->addRecord(empObject);
				cout << "\n\t[✚] Employee added.\n";
				usleep(1000000);
				clearScreen();
			}
			clearScreen();
			break;

		case 2:
			while (true)
			{
				try
				{
					int updateId;
					clearScreen();
					cout << "\t============================================================\n";
					cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM          |\n";
					cout << "\t|           UPDATE EXISTING EMPLOYEE INFORMATION           |\n";
					cout << "\t============================================================\n";
					cout << "\t------------------------------------------------------------\n";
					cout << "\t| Please enter the Employee ID to update an employee       |\n";
					cout << "\t------------------------------------------------------------\n\n";
					cout << "Enter Employee ID to update or [-1 to quit]: ";
					cin >> updateId;
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid Employee ID! ]");
					}
					if (updateId == -1)
						break;

					empPtr->updateRecord(updateId);
					cout << "\n\t[~] Employee updated.\n";
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
				usleep(1000000);
				clearScreen();
			}
			clearScreen();
			break;

		case 3:
			while (true)
			{
				try
				{
					int searchId;
					clearScreen();
					cout << "\t======================================================\n";
					cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
					cout << "\t|                   VIEW EMPLOYEE RECORD              |\n";
					cout << "\t======================================================\n\n";
					cout << "Enter Employee ID to view or [-1 to quit]: ";
					cin >> searchId;
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid Employee ID! ]");
					}
					if (searchId == -1)
						break;

					empPtr->viewRecord(searchId);
					pressEnterContinue();
					clearScreen();
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
			}
			clearScreen();
			break;

		case 4:
			clearScreen();
			cout << "\n\t==========================================================================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                        |\n";
			cout << "\t|                   VIEW SORTED EMPLOYEE RECORDS                         |\n";
			cout << "\t==========================================================================\n";
			cout << "\t|  ID.No  |  First Name  |  Last Name   | Dept. Code |  Position   | Worked Hours |\n";
			cout << "\t--------------------------------------------------------------------------\n";
			sortEmployeeConsole();
			pressEnterContinue();
			clearScreen();
			break;

		case 5:
			while (true)
			{
				try
				{
					int deleteId;
					clearScreen();
					cout << "\n\t======================================================\n";
					cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
					cout << "\t|                DELETE EMPLOYEE RECORD              |\n";
					cout << "\t======================================================\n";
					cout << "\t------------------------------------------------------\n";
					cout << "\t| Please enter the Employee ID to delete an employee |\n";
					cout << "\t------------------------------------------------------\n\n";
					cout << "Enter Employee ID to delete or [-1 to quit]: ";
					cin >> deleteId;
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid Employee ID! ]");
					}
					if (deleteId == -1)
						break;

					empPtr->deleteRecord(deleteId);
					cout << "\n\t[-] Employee deleted.\n";
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
				usleep(1000000);
				clearScreen();
			}
			clearScreen();
			break;

		default: // Invalid choice
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a[ ❌ Incorrect selection. Try again. ]" << endl;
			usleep(2000000);
			clearScreen();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}
	}
	delete empPtr;
}

// Function: sortEmployeeConsole
void sortEmployeeConsole()
{
	clearScreen();
	int choice;
	int listSize = 0;
	EmpList *emplist = new EmpList();

	//------------------ read objects from employee file --------------------------//
	string empFileName = "employee.txt";
	string empPayrollFileName = "employee_payroll.txt";

	try
	{
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
			throw runtime_error("[ ❌ ERROR ACCESSING FILE! ]");
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
			cout << "\t\t\a\n[ ℹ️ No record(s) exist for Employees!!! ]\n\n";
		}

		empFile.close();
		empPayrollFile.close();
	}
	catch (exception &i)
	{
		cerr << i.what();
	}
	//-----------------------------------------------------------------------//

	cout << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = sortedEmployeeMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\t==============================================================\n";
			cout << "\t|                  RETURNING TO MAIN MENU                     |\n";
			cout << "\t==============================================================\n\n";
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			break;
		}

		listSize = emplist->countNodes(); // count nodes that were added to employee list

		switch (choice)
		{
		case 1:
			cout << "\n\t================ SORT EMPLOYEE RECORDS BY ID ================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM           |\n";
			cout << "\t|                EMPLOYEES SORTED BY EMPLOYEE ID            |\n";
			cout << "\t============================================================\n\n";
			emplist->mergeSortById();
			emplist->traverse();
			break;

		case 2:
			cout << "\n\t============= SORT EMPLOYEE RECORDS BY LAST NAME =============\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM            |\n";
			cout << "\t|             EMPLOYEES SORTED BY LAST NAME                  |\n";
			cout << "\t==============================================================\n\n";
			emplist->mergeSortByLastName();
			emplist->traverse();
			break;

		case 3:
			cout << "\n\t========== SORT EMPLOYEE RECORDS BY DEPARTMENT CODE ==========\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM            |\n";
			cout << "\t|           EMPLOYEES SORTED BY DEPARTMENT CODE              |\n";
			cout << "\t==============================================================\n\n";
			emplist->mergeSortByDepartmentCode();
			emplist->traverse();
			break;

		case 4:
			cout << "\n\t=============== SORT EMPLOYEE RECORDS BY POSITION =============\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM             |\n";
			cout << "\t|                EMPLOYEES SORTED BY POSITION                 |\n";
			cout << "\t===============================================================\n\n";
			emplist->mergeSortByPosition();
			emplist->traverse();
			break;

		case 5:
			cout << "\n\t=========== SORT EMPLOYEE RECORDS BY WORKED HOURS =============\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM             |\n";
			cout << "\t|           EMPLOYEES SORTED BY HOURS WORKED                  |\n";
			cout << "\t===============================================================\n\n";
			emplist->mergeSortByHoursWorked(); // Use merge sort instead of bubble sort
			emplist->traverse();
			break;

		default:
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a[ ℹ️ Incorrect selection. Try again. ]" << endl;
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

// Function: Department Console
void departmentConsole()
{
	clearScreen();
	int choice;
	Department deptObject;
	Department *deptPtr = new Department();

	while ((choice = departmentMenu()))
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t[ RETURNING TO MAIN MENU... ]\n"
				 << endl;
			usleep(1000000);
			clearScreen();
			break;
		}

		switch (choice)
		{
		case 1:
			while (true)
			{
				clearScreen();
				cout << "\n\t======================================================\n";
				cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
				cout << "\t|                ADD NEW DEPARTMENT RECORD           |\n";
				cout << "\t======================================================\n";
				int code;
				cout << "Enter Department code or [-1 to quit]: ";
				cin >> code;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\t[ ℹ️ Invalid input. Please enter a valid department code. ]\n";
					continue;
				}
				if (code == -1)
					break;

				deptObject = deptPtr->createDepartment(code);
				deptPtr->addRecord(deptObject);
				cout << "\n\t[+] Department added.\n";
				usleep(3000000);
				clearScreen();
			}
			clearScreen();
			break;

		case 2:
			while (true)
			{
				clearScreen();
				cout << "\n\t======================================================\n";
				cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
				cout << "\t|                UPDATE DEPARTMENT RECORD            |\n";
				cout << "\t======================================================\n";
				try
				{
					int updateCode;
					cout << "Enter Department code to update or [-1 to quit]: ";
					cin >> updateCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid department code! ]");
					}
					if (updateCode == -1)
						break;

					deptPtr->updateRecord(updateCode);
					cout << "\n\t[~] Department updated.\n";
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
			}
			clearScreen();
			break;

		case 3:
			while (true)
			{
				clearScreen();
				cout << "\n\t======================================================\n";
				cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
				cout << "\t|                VIEW DEPARTMENT RECORD              |\n";
				cout << "\t======================================================\n";
				try
				{
					int searchCode;
					cout << "Enter Department code to view or [-1 to quit]: ";
					cin >> searchCode;
					cout << endl
						 << endl;	
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid department code! ]");
					}

					if (searchCode == -1)
						break;

					deptPtr->viewRecord(searchCode);
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
			}
			clearScreen();
			break;

		case 4:
			clearScreen();
			cout << "\n\t======================================================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
			cout << "\t|                VIEW ALL DEPARTMENTS                |\n";
			cout << "\t======================================================\n";
			deptPtr->viewAllRecords();
			pressEnterContinue();
			clearScreen();
			break;

		case 5:
			while (true)
			{
				clearScreen();
				cout << "\n\t======================================================\n";
				cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM    |\n";
				cout << "\t|                DELETE DEPARTMENT RECORD            |\n";
				cout << "\t======================================================\n";
				try
				{
					int deleteCode;
					cout << "Enter Department code to delete or [-1 to quit]: ";
					cin >> deleteCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid department code! ]");
					}
					if (deleteCode == -1)
						break;

					deptPtr->deleteRecord(deleteCode);
					cout << "\n\t[-] Department deleted.\n";
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}
				pressEnterContinue();
				clearScreen();
			}
			clearScreen();
			break;

		default:
			cout << "\n\t[ ℹ️ Incorrect selection. Try again. ]\n";
			usleep(1000000);
			clearScreen();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}
	}

	delete deptPtr; // Clean up dynamically allocated memory
}

void payrollProcessing()
{
	string ratesFileName = "rates.txt";
	string empFileName = "employee.txt";
	string empPayrollFileName = "employee_payroll.txt";
	string payrollFileName = "monthly_payroll.txt";

	try
	{
		ifstream ratesFile(ratesFileName);
		ifstream empFile(empFileName);
		ifstream empPayrollFile(empPayrollFileName);
		ofstream payrollFile(payrollFileName); // overwrite file for each run

		// Check file access
		checkFileAccess(ratesFile);
		checkFileAccess(empFile);
		checkFileAccess(empPayrollFile);
		checkFileAccess(payrollFile);

		Department dept;
		Employee emp;
		const int baseHrs = 40;


payrollLogo();
		while (true)
		{
			int code, id, payrollId, payrollDeptCode, deptCode;
			float hrRate, otRate, hrs;
			string firstName, lastName, position;

			// Read all fields for each file, break if any fail
			if (!(ratesFile >> code >> hrRate >> otRate) ||
				!(empFile >> id >> firstName >> lastName >> deptCode >> position) ||
				!(empPayrollFile >> payrollId >> payrollDeptCode >> hrs))
			{
				break; // Exit loop if any read fails
			}

			dept.setCode(code);
			dept.setHourlyRate(hrRate);
			dept.setOvertimeRate(otRate);

			emp.setId(id);
			emp.setFirstName(firstName);
			emp.setLastName(lastName);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(position);
			emp.setHoursWorked(hrs);

			if (emp.getDepartmentCode() == dept.getCode() && hrs > 0)
			{
				float workedHours = emp.getHoursWorked();
				float deptRate = dept.getHourlyRate();
				float overtimeRate = dept.getOvertimeRate();

				float regularPay = 0.0;
				float overtimePay = 0.0;

				if (workedHours > baseHrs)
				{
					regularPay = calculateRegularPay(deptRate, baseHrs);
					overtimePay = calculateOvertimePay(workedHours - baseHrs, overtimeRate);
				}
				else
				{
					regularPay = calculateRegularPay(deptRate, workedHours);
				}

				float grossPay = calculateGrossPay(regularPay, overtimePay);

				// Create and display payroll record
				createAndDisplayPayroll(emp.getId(), emp.getFirstName(), emp.getLastName(), emp.getDepartmentCode(),
							 emp.getPosition(), emp.getHoursWorked(), regularPay, overtimePay, grossPay);

				payrollFile << emp.getId() << "\t" << emp.getFirstName() << "\t"
							<< emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t"
							<< emp.getPosition() << "\t" << emp.getHoursWorked() << "\t"
							<< regularPay << "\t" << overtimePay << "\t" << grossPay << endl;
			}
		}

		ratesFile.close();
		empFile.close();
		empPayrollFile.close();
		payrollFile.close();
	}
	catch (exception &e)
	{
		cerr << e.what();
	}
}

// Function: View Single Payroll Record
void viewSinglePayroll(int searchId)
{
	string payrollFileName = "monthly_payroll.txt";

	try
	{
		ifstream payrollFile(payrollFileName, ios::in);

		bool found = false;

		int id, deptCode;
		string firstName, lastName, position;
		float hrs;

		float regularPay, overtimePay, grossPay;

		if (payrollFile.fail())
		{
			throw runtime_error("[ ❌ ERROR ACCESSING FILE! ]");
		} // end if

		while (payrollFile >> id >> firstName >> lastName >> deptCode >> position >> hrs >> regularPay >> overtimePay >> grossPay)
		{
			if (searchId == id)
			{
				found = true; // validates that lookup record was found
				clearScreen();
				payrollLogo();
				createAndDisplayPayroll(id, firstName, lastName, deptCode,
							 position, hrs, regularPay, overtimePay, grossPay);

				break;
			} // end if
		} // end while

		if (found == false)
		{
			cout << "\t\t\a\n [ ❌ Record with Department Code : " << searchId << " does not exist!!! ]\n\n";
		} // end if

		payrollFile.close(); // close department file

	} // end try
	catch (exception &i)
	{
		cerr << i.what();
	} // end catch
}

// Function: View All Payroll Records
void sortPayrollConsole()
{
	clearScreen();
	int choice;
	int listSize = 0;
	PayList *payrollList = new PayList();

	string monthlyPayrollFileName = "monthly_payroll.txt";

	try
	{
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
			throw runtime_error("[ ❌ ERROR ACCESSING FILE! ]");
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
			cout << "\t\t\a\n[ ❌ No record(s) exist for Employees payroll. ]\n\n";
		}

		payFile.close();
	}
	catch (exception &i)
	{
		cerr << i.what();
	}

	cout << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = sortedPayrollMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t==============================================================\n";
			cout << "\t|                  RETURNING TO MAIN MENU                     |\n";
			cout << "\t==============================================================\n\n";
			usleep(3000000);
			clearScreen();
			break;
		}

		listSize = payrollList->countNodes();

		switch (choice)
		{
		case 1:
			cout << "\n\t================ SORT PAYROLL RECORDS BY ID ================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM           |\n";
			cout << "\t|                PAYROLL SORTED BY EMPLOYEE ID              |\n";
			cout << "\t============================================================\n\n";
			payrollLogo();
			payrollList->mergeSortById();
			payrollList->traverse();
			cout << endl
				 << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;

		case 2:
			cout << "\n\t================ SORT PAYROLL RECORDS BY LAST NAME ================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                 |\n";
			cout << "\t|             PAYROLL SORTED BY EMPLOYEE LAST NAME                |\n";
			cout << "\t==================================================================\n\n";
			payrollLogo();
			payrollList->mergeSortByLastName();
			payrollList->traverse();
			cout << endl
				 << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;
		case 3:
			cout << "\n\t================ SORT PAYROLL RECORDS BY DEPARTMENT CODE ================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                        |\n";
			cout << "\t|             PAYROLL SORTED BY DEPARTMENT CODE                         |\n";
			cout << "\t=======================================================================\n\n";
			payrollLogo();
			payrollList->mergeSortByDepartmentCode();
			payrollList->traverse();
			cout << endl
				 << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;

		case 4:
			cout << "\n\t================ SORT PAYROLL RECORDS BY POSITION ================\n";
			cout << "\t|      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                |\n";
			cout << "\t|                PAYROLL SORTED BY POSITION                      |\n";
			cout << "\t===============================================================\n\n";
			payrollLogo();
			payrollList->mergeSortByPosition();
			payrollList->traverse();
			cout << endl
				 << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;

		default:
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a[ ℹ️ Incorrect selection. Try again.] " << endl;
			usleep(3000000);
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		}
	}
}

// Function: Payroll Console
void payrollConsole()
{
	clearScreen();
	int choice;

	cout << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = payrollMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t==============================================================\n";
			cout << "\t|                  RETURNING TO MAIN MENU...                   |\n";
			cout << "\t==============================================================\n\n";
			usleep(3000000); // Sleep for 1 second (1 million microseconds)
			clearScreen();
			break;
		} // end if

		switch (choice)
		{
		case 1:
			payrollProcessing();
			cout << endl
				 << endl
				 << endl;

			pressEnterContinue();
			clearScreen();
			break;

		case 2:

			while (true)
			{
				try
				{
					int searchId; // declaration of id to look up record
					cout << "\n\t==============================================================" << endl;
					cout << "\t|                VIEW EMPLOYEE PAYROLL RECORD                |" << endl;
					cout << "\t==============================================================" << endl
						 << endl;

					cout << "ENTER EMPLOYEE ID TO LOOKUP PAYROLL RECORD OR [-1] TO QUIT : ";
					cin >> searchId; // input id use to look employee record
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						throw invalid_argument("\t\t[ ❌ NOT A VALID EMPLOYEE ID! ]");
					} // end if

					if (searchId == -1) // condition use to exit loop
						break;

					viewSinglePayroll(searchId);
				} // end try
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				} // end catch

				cout << endl
					 << endl
					 << endl
					 << endl;
				pressEnterContinue();
				clearScreen();
			} // end while

		case 3:
			sortPayrollConsole();

			cout << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;

		default:
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a [ ℹ️ Incorrect selection. Try again. ]" << endl;
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

	cout << "\033[1;37m" << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = mainMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\t================== EXITING PAYROLL MANAGEMENT SYSTEM ==================" << endl
				 << endl;
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
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a [ ℹ️ Incorrect selection. Try again. ]" << endl;
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		} // end case

	} // end while
	cout << "\033[0m"; // Reset color
}
