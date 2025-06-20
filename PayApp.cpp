
/*
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
-- Description: This Payroll Management System (PMS) is designed to manage payroll for SSN employees.
-- Created by: D. Perry
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
*/

#include "Utilities.h" 

//...............................................................||
int main()
{
	try
	{
		mainConsole(); // Call the main console function to start the application
		cout << "\n\t\t[ 🖐️ SHUTTING DOWN SYSTEM... ]\n\n";
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
		cerr << "\n\t[ ⚠️ Something unexpected has occurred. ]" << endl;
	}

	pressEnterContinue();
	clearScreen();
	return 0;
}
//.....................................................................||

// Function: Department Console
void departmentConsole()
{
	clearScreen();
	int choice;
	Department deptObject;
	Department *deptPtr = new Department(); // Create a new instance of Department

	while ((choice = departmentMenu()))
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t[🔄/t RETURNING TO MAIN MENU... ]\n"
				 << endl;
			usleep(1000000);
			clearScreen();
			break;
		}

		switch (choice) // Switch based on user choice
		{
		case 1: // Add new department record
			while (true) // Loop until user chooses to quit
			{
				clearScreen();
				cout << "\n\t╔══════════════════════════════════════════════════════════════════════╗\n";
				cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
				cout << "\t║                ADD NEW DEPARTMENT RECORD                           ║\n";
				cout << "\t╚══════════════════════════════════════════════════════════════════════╝\n";
				cout << endl;

				int code;
				cout << "\t Enter Department code or [-1 to quit]: ";
				cin >> code;
				cout << endl;

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

		case 2: // Update existing department record
			while (true) // Loop until user chooses to quit
			{
				clearScreen();
				cout << "\n\t╔══════════════════════════════════════════════════════════════════════╗\n";
				cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
				cout << "\t║                UPDATE DEPARTMENT RECORD                            ║\n";
				cout << "\t╚══════════════════════════════════════════════════════════════════════╝\n";
				cout << endl;
				try
				{
					int updateCode;
					cout << "\t Enter Department code to update or [-1 to quit]: ";
					cin >> updateCode;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid department code! ]");
					}
					if (updateCode == -1) // If user enters -1, break the loop
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

		case 3: // View specific department record
			while (true) // Loop until user chooses to quit
			{
				clearScreen();
				cout << "\n\t╔══════════════════════════════════════════════════════════════════════╗\n";
				cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
				cout << "\t║                VIEW DEPARTMENT RECORD                              ║\n";
				cout << "\t╚══════════════════════════════════════════════════════════════════════╝\n\n";

				try
				{
					int searchCode;
					cout << "\t Enter Department code to view or [-1 to quit]: ";
					cin >> searchCode;
					cout << endl
						 << endl;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid department code! ]");
					}

					if (searchCode == -1) // If user enters -1, break the loop
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

		case 4: // View all department records
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
			cout << "\t║                VIEW ALL DEPARTMENTS                                ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════╝\n";

			deptPtr->viewAllRecordss();
			pressEnterContinue();
			clearScreen();
			break;

		case 5: // Delete department record
			while (true) // Loop until user chooses to quit
			{
				clearScreen();
				cout << "\n\t╔══════════════════════════════════════════════════════════════════════╗\n";
				cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
				cout << "\t║                DELETE DEPARTMENT RECORD                            ║\n";
				cout << "\t╚══════════════════════════════════════════════════════════════════════╝\n\n";

				try
				{
					int deleteCode;
					cout << "\t Enter Department code to delete or [-1 to quit]: ";
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

		default: // Invalid choice
			cout << "\n\t[ ℹ️/t Incorrect selection. Try again. ]\n";
			usleep(1000000);
			clearScreen();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}
	}

	delete deptPtr; // Clean up dynamically allocated memory
}

// Function: Employee Console
void employeeConsole()
{
	clearScreen();

	int choice;
	Employee empObject;
	Employee *empPtr = new Employee(); // Create a new instance of Employee

	cout << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = employeeMenu())) // Loop while choice does not equal 0
	{
		clearScreen();
		if (choice == 0)
		{
			cout << "\n\t[ 🔄/t RETURNING TO MAIN MENU... ]\n"
				 << endl;
			usleep(1000000);
			clearScreen();
			break;
		}

		switch (choice) // Switch based on user choice
		{
		case 1: // Add new employee record
			while (true) // Loop until user chooses to quit
			{
				int id;

				clearScreen();
				cout << "\n\t╔══════════════════════════════════════════════════════════════╗\n";
				cout << "\t║      SOFTWARE SOLUTION NOW (SSN) PAYROLL SYSTEM             ║\n";
				cout << "\t║                ADD NEW EMPLOYEE RECORD                      ║\n";
				cout << "\t╠══════════════════════════════════════════════════════════════╣\n";
				cout << "\t║  Please enter the Employee ID to add a new employee         ║\n";
				cout << "\t╚══════════════════════════════════════════════════════════════╝\n\n";

				cout << "\t Enter Employee ID or [-1 to quit]: ";
				cin >> id;
				cout << endl
					 << endl;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "\t[ ℹ️/t Invalid input. Please enter a valid Employee ID. ]\n";
					continue;
				}
				if (id == -1) // If user enters -1, break the loop
					break;

				empObject = empPtr->createEmployee(id);
				empPtr->addRecord(empObject);
				cout << "\n\t[✚] Employee added.\n";
				usleep(1000000);
				clearScreen();
			}
			clearScreen();
			break;

		case 2: // Update existing employee record
			while (true) // Loop until user chooses to quit
			{
				try
				{
					int updateId;

					clearScreen();
					cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
					cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
					cout << "\t║                   UPDATE EXISTING EMPLOYEE INFORMATION                     ║\n";
					cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";
					cout << "\t║  Please enter the Employee ID to update an employee                        ║\n";
					cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";

					cout << "\t Enter Employee ID to update or [-1 to quit]: ";
					cin >> updateId;
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(10000, '\n');
						throw invalid_argument("\t[ ❌ Not a valid Employee ID! ]");
					}
					if (updateId == -1) // If user enters -1, break the loop
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

		case 3: // View specific employee record
			while (true) // Loop until user chooses to quit
			{
				try
				{
					int searchId;

					clearScreen();
					cout << "\n\t╔════════════════════════════════════════════════════════════════════════╗\n";
					cout << "\t║           SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                 ║\n";
					cout << "\t║                    VIEW EMPLOYEE RECORD                              ║\n";
					cout << "\t╠════════════════════════════════════════════════════════════════════════╣\n";
					cout << "\t║  Please enter the Employee ID to view an employee record             ║\n";
					cout << "\t╚════════════════════════════════════════════════════════════════════════╝\n\n";

					cout << "\t Enter Employee ID to view or [-1 to quit]: ";
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

		case 4: // View all employee records
			clearScreen();

			// This option allows you to view all employee records sorted by various criteria.
			sortEmployeeConsole(empFileName,empPayrollFileName);
			pressEnterContinue();
			clearScreen();
			break;

		case 5: // Delete employee record
			while (true) // Loop until user chooses to quit
			{
				try
				{
					int deleteId;
					clearScreen();
					cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════════╗\n";
					cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                      ║\n";
					cout << "\t║                        DELETE EMPLOYEE RECORD                                  ║\n";
					cout << "\t╠══════════════════════════════════════════════════════════════════════════════════╣\n";
					cout << "\t║  Please enter the Employee ID to delete an employee record                     ║\n";
					cout << "\t╚══════════════════════════════════════════════════════════════════════════════════╝\n\n";

					cout << "\t Enter Employee ID to delete or [-1 to quit]: ";
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
			cout << "\t\t\a[ ℹ️/t Incorrect selection. Try again. ]" << endl;
			usleep(2000000);
			clearScreen();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}
	}

	delete empPtr; // Clean up dynamically allocated memory
	clearScreen();
}

// Function: sortEmployeeConsole
void sortEmployeeConsole(const string &empFileName, const string &empPayrollFileName)
{
	clearScreen();
	int choice;
	int listSize = 0;
	EmpList *emplist = new EmpList(); // Create a new instance of EmpList

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

		if (empFile.fail() || empPayrollFile.fail()) // Check if files opened successfully
		{
			throw runtime_error("[ ❌ ERROR ACCESSING FILE! ]");
		}

		while (empFile >> id >> firstName >> lastName >> departmentCode >> position &&
			   empPayrollFile >> empId >> deptCode >> hoursWorked) // Read from both files
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

		if (existingNodes == 0) // No records found
		{
			cout << "\t\t\n[ ℹ️/t No record(s) exist for Employees!!! ]\n\n";
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
		if (choice == 0) // If choice is 0, return to main menu
		{
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                          RETURNING TO MAIN MENU                            ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			break;
		}

		listSize = emplist->countNodes(); // count nodes that were added to employee list

		switch (choice) // Switch based on user choice
		{
		case 1: // Sort by Employee ID
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                  EMPLOYEES SORTED BY EMPLOYEE ID                           ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

			emplist->mergeSortById();
			emplist->traverse();
			break;

		case 2: // Sort by Last Name
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                  EMPLOYEES SORTED BY LAST NAME                             ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

			emplist->mergeSortByLastName();
			emplist->traverse();
			break;

		case 3: // Sort by Department Code
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║              EMPLOYEES SORTED BY DEPARTMENT CODE                           ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

			emplist->mergeSortByDepartmentCode();
			emplist->traverse();
			break;

		case 4: // Sort by Position
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                  EMPLOYEES SORTED BY POSITION                              ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

			emplist->mergeSortByPosition();
			emplist->traverse();
			break;

		case 5: // Sort by Hours Worked
			clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║              EMPLOYEES SORTED BY HOURS WORKED                              ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

			emplist->mergeSortByHoursWorked(); // Use merge sort instead of bubble sort
			emplist->traverse();
			break;

		default: // Invalid choice
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t[ ℹ️/t Incorrect selection. Try again. ]" << endl;
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
	clearScreen();
}

void payrollProcessing(const string &ratesFileName, const string &empFileName, const string &empPayrollFileName, const string &payrollFileName)
{
    try
    {
        // Open files and check if they are accessible
        ifstream ratesFile(ratesFileName);
        ifstream empFile(empFileName);
        ifstream empPayrollFile(empPayrollFileName);
        ofstream payrollFile(payrollFileName); // overwrite file for each run

        checkFileAccess(ratesFile);
        checkFileAccess(empFile);
        checkFileAccess(empPayrollFile);
        checkFileAccess(payrollFile);

        int code;
        float hrRate, otRate;
        map<int, pair<float, float>> deptRates; // Map to hold department rates: deptCode -> (hourlyRate, overtimeRate)

        // Read department rates
        while (ratesFile >> code >> hrRate >> otRate) 
        {
            deptRates[code] = make_pair(hrRate, otRate);
        }

        // Read employees into a map: empId -> Employee object
        map<int, Employee> employees;
        int id, deptCodeEmp;
        string firstName, lastName, position;

        while (empFile >> id >> firstName >> lastName >> deptCodeEmp >> position) 
        {
            Employee emp;
            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCodeEmp);
            emp.setPosition(position);
            employees[id] = emp;
        }

        const int baseHrs = 40; // Base hours for regular pay calculation

        payrollLogo(); // Display payroll logo

        // Now process payroll records
        int payrollId, payrollDeptCode;
        float hrsWorked;

        bool recordsFound = false; // Flag to check if any records were processed

        while (empPayrollFile >> payrollId >> payrollDeptCode >> hrsWorked) // Read payroll records
        {
            // Find employee by payrollId
            auto empIt = employees.find(payrollId);

            if (empIt == employees.end()) // If employee not found in records
            {
                cout << "\n\t[ ⚠️\t Employee ID " << payrollId << " in payroll file not found in employee records. Skipping... ]\n";
                continue;
            }

            Employee &emp = empIt->second; // Get the employee object

            // Confirm department code matches payroll record's department code for consistency (optional)
            if (emp.getDepartmentCode() != payrollDeptCode)
            {
                cout << "\n\t[ ⚠️\t Department code mismatch for Employee ID " << payrollId << ". Payroll dept: " << payrollDeptCode
                     << ", Employee dept: " << emp.getDepartmentCode() << ". Skipping... ]\n";
                continue;
            }

            // Find department rates
            auto rateIt = deptRates.find(emp.getDepartmentCode());

            if (rateIt == deptRates.end()) // If department rates not found
            {
                cout << "\n\t[ ⚠️\t Department rates not found for Department Code: " << emp.getDepartmentCode() << ". Skipping employee ID " << payrollId << " ]\n";
                continue;
            }

            float deptHourlyRate = rateIt->second.first;
            float deptOvertimeRate = rateIt->second.second;

            if (hrsWorked <= 0) // Check if hours worked is zero or negative
            {
                continue; // Skip if hours worked is zero or negative
            }

            // Calculate pays
            float regularPay = 0.0f;
            float overtimePay = 0.0f;

            if (hrsWorked > baseHrs) // If hours worked exceeds base hours, calculate regular and overtime pay
            {
                regularPay = calculateRegularPay(deptHourlyRate, baseHrs);
                overtimePay = calculateOvertimePay(hrsWorked, deptOvertimeRate);
            }
            else // If hours worked is within base hours, calculate only regular pay
            {
                regularPay = calculateRegularPay(deptHourlyRate, hrsWorked);
            }

            float grossPay = calculateGrossPay(regularPay, overtimePay);

            // Display payroll record in table format
            createAndDisplayPayroll(emp.getId(), emp.getFirstName(), emp.getLastName(), emp.getDepartmentCode(),
                                    emp.getPosition(), hrsWorked, regularPay, overtimePay, grossPay);

            // Write to output payroll file
            payrollFile << emp.getId() << "\t" << emp.getFirstName() << "\t"
                        << emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t"
                        << emp.getPosition() << "\t" << hrsWorked << "\t"
                        << regularPay << "\t" << overtimePay << "\t" << grossPay << endl;

            recordsFound = true; // Set flag to true if at least one record was processed
        }

        if (!recordsFound) // If no payroll records were processed
        {
            cout << "\n\t[ ℹ️\t No payroll records processed. ]\n";
        }

        // Close all files
        ratesFile.close();
        empFile.close();
        empPayrollFile.close();
        payrollFile.close();
    }
    catch (const exception &e)
    {
        cerr << "Exception during payroll processing: " << e.what() << endl;
    }
}


// Function: View Single Payroll Record
void viewSinglePayroll(int searchId, const string &payrollFileName)
{

	try
	{
		ifstream payrollFile(payrollFileName, ios::in);

		bool found = false; // Flag to check if record is found

		int id, deptCode;
		string firstName, lastName, position;
		float hrs;

		float regularPay, overtimePay, grossPay;

		// Check file access
		checkFileAccess(payrollFile);

		while (payrollFile >> id >> firstName >> lastName >> deptCode >> position >> hrs >> regularPay >> overtimePay >> grossPay) // Read payroll records
		{
			if (searchId == id) // If the searched ID matches the current record's ID
			{
				found = true;// Set found flag to true
				clearScreen();
				payrollLogo();
				createAndDisplayPayroll(id, firstName, lastName, deptCode,
										position, hrs, regularPay, overtimePay, grossPay);

				break;
			} // end if

		} // end while

		if (found == false) // If no record was found
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
void sortPayrollConsole(const string &payrollFileName)
{
	clearScreen();
	int choice;
	int listSize = 0;
	PayList *payrollList = new PayList(); // Create a new instance of PayList

	try
	{
		ifstream payFile(payrollFileName, ios::in);

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

		checkFileAccess(payFile);

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

			payrollList->insertAtFront(payroll); // Initialize list with payroll records
			++existingNodes; // Increment the count of existing nodes
		}

		if (existingNodes == 0) // If no records were found
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
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                          RETURNING TO MAIN MENU                            ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
			usleep(3000000);
			clearScreen();
			break;
		}

		listSize = payrollList->countNodes();

		switch (choice) // Switch based on user choice
		{
		case 1: // Sort by Employee ID
		clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                  PAYROLL SORTED BY EMPLOYEE ID                             ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

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

		case 2: // Sort by Last Name
		clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║              PAYROLL SORTED BY EMPLOYEE LAST NAME                          ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

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

		case 3: // Sort by Department Code
		clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║              PAYROLL SORTED BY DEPARTMENT CODE                             ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

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

		case 4: // Sort by Position
		clearScreen();
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                  PAYROLL SORTED BY POSITION                                ║\n";
			cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";

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

		default: // Invalid choice
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a[ ℹ️/t Incorrect selection. Try again. ]" << endl;
			usleep(3000000);
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		}
	}
}

// Function: Delete Single Payroll Record
void deleteSinglePayroll(int searchId , const string &payrollFileName , const string &tempPayFileName)
{
	bool found = false;
	bool deleted = false;

	try
	{
		ifstream payrollFile(payrollFileName, ios::in);
		ofstream tempFile(tempPayFileName, ios::out);

		checkFileAccess(payrollFile);
		checkFileAccess(tempFile);

		int id, deptCode;
		string firstName, lastName, position;
		float hrs, regularPay, overtimePay, grossPay;

		while (payrollFile >> id >> firstName >> lastName >> deptCode >> position >> hrs >> regularPay >> overtimePay >> grossPay) // Read payroll records
		{
			if (searchId == id) // If the searched ID matches the current record's ID
			{
				found = true; // Set found flag to true
				clearScreen();

				cout << "\n╔════════════════════════════════════════════════════════════════════════════════════╗\n";
				cout << "║                           PAYROLL RECORD FOUND                                   ║\n";
				cout << "╠════════════════════════════════════════════════════════════════════════════════════╣\n";
				payrollLogo();
				createAndDisplayPayroll(id, firstName, lastName, deptCode,
										position, hrs, regularPay, overtimePay, grossPay);
				cout << "\n╔════════════════════════════════════════════════════════════════════════════════════╗\n";

				char confirm;

				// Input validation loop
				do
				{
					cout << "║   ❗ WARNING: This action will permanently delete the payroll record.             \n";
					cout << "║   ❗ Are you sure you want to delete this payroll record? (y/n): ";
					cin >> confirm;
					confirm = tolower(confirm);
					if (confirm != 'y' && confirm != 'n')
						cout << "║   Please enter 'y' or 'n'." << endl;
				} while (confirm != 'y' && confirm != 'n');

				cout << "║\n";
				cout << "╚════════════════════════════════════════════════════════════════════════════════════╝\n\n";

				if (confirm == 'y') // If user confirms deletion
				{
					cout << "\n\t[ ❌ Deleting payroll record... ]" << endl;
					deleted = true;
					// Skip writing this record to temp file (deleting)
				}
				else // If use cancels deletion
				{
					cout << "\n\t\t[ ℹ️  Deletion cancelled. Payroll record will be kept. ]" << endl;

					tempFile << id << "\t" << firstName << "\t" << lastName << "\t"
							 << deptCode << "\t" << position << "\t" << hrs << "\t"
							 << regularPay << "\t" << overtimePay << "\t" << grossPay << endl;
				}
			}
			else // If the record does not match the search ID, write it to the temp file
			{
				tempFile << id << "\t" << firstName << "\t" << lastName << "\t"
						 << deptCode << "\t" << position << "\t" << hrs << "\t"
						 << regularPay << "\t" << overtimePay << "\t" << grossPay << endl;
			}
		}

		payrollFile.close();
		tempFile.close();

		if (!found) // If no record was found
		{
			remove(tempPayFileName.c_str());
			cout << "\n\t [ ❌ Record with Employee ID: " << searchId << " does not exist! ]\n\n";
		}
		else if (found && deleted) // If record was found and deletion confirmed
		{
			if (remove(payrollFileName.c_str()) != 0)
				throw runtime_error("\t [ ❌ ERROR REMOVING ORIGINAL PAYROLL FILE! ]");

			if (rename(tempPayFileName.c_str(), payrollFileName.c_str()) != 0)
				throw runtime_error("\t [ ❌ ERROR RENAMING TEMP PAYROLL FILE! ]");

			cout << "\n [ ✅ Payroll record with Employee ID: " << searchId << " has been deleted. ]" << endl
				 << endl;
		}
		else // If deletion was cancelled
		{
			// Deletion cancelled, remove temp file as original file remains unchanged
			remove(tempPayFileName.c_str());
			cout << "\n\t [ ❌ Payroll record with Employee ID: " << searchId << " was not deleted. ]" << endl;
		}
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
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
		if (choice == 0) // If choice is 0, return to main menu
		{
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                          RETURNING TO MAIN MENU                            ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
			usleep(3000000); // Sleep for 3 seconds (3 million microseconds)
			clearScreen();
			break;
		} // end if

		switch (choice) // Switch based on user choice
		{
		case 1: // Process payroll records
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
			cout << "\t║                    PROCESSED EMPLOYEE PAYROLL RECORD                       ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";

			payrollProcessing(ratesFileName, empFileName, empPayrollFileName, payrollFileName); // Call function to process payroll records
			cout << endl
				 << endl
				 << endl;

			pressEnterContinue();
			clearScreen();
			break;

		case 2: // View single payroll record

			while (true) // Loop until user chooses to quit
			{
				try
				{
					int searchId; // declaration of id to look up record
					cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
					cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
					cout << "\t║                      VIEW EMPLOYEE PAYROLL RECORD                          ║\n";
					cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";

					cout << "\t ENTER EMPLOYEE ID TO LOOKUP PAYROLL RECORD OR [-1] TO QUIT : ";
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

					viewSinglePayroll(searchId, payrollFileName); // call function to view single payroll record
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
			break;

		case 3: // View all payroll records
			sortPayrollConsole(payrollFileName); // This option allows you to view all payroll records sorted by various criteria.

			cout << endl
				 << endl
				 << endl;
			pressEnterContinue();
			clearScreen();
			break;

		case 4: // Delete single payroll record
			while (true) // Loop until user chooses to quit
			{
				try
				{
					int deleteId;
					cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
					cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                  ║\n";
					cout << "\t║                      DELETE EMPLOYEE PAYROLL RECORD                        ║\n";
					cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";

					cout << "\t ENTER EMPLOYEE ID TO DELETE PAYROLL RECORD OR [-1] TO QUIT : ";
					cin >> deleteId;
					cout << endl
						 << endl;

					if (cin.fail())
					{
						cin.clear();
						throw invalid_argument("\t\t[ ❌ NOT A VALID EMPLOYEE ID! ]");
					}

					if (deleteId == -1) // condition use to exit loop
						break;

					deleteSinglePayroll(deleteId, payrollFileName, tempPayFileName); // Call function to delete single payroll record
				}
				catch (invalid_argument &e)
				{
					cerr << e.what() << endl;
				}

				cout << endl
					 << endl
					 << endl
					 << endl;
				pressEnterContinue();
				clearScreen();
			}
			break;

		default: // Invalid choice
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a [ ℹ️/t Incorrect selection. Try again. ]" << endl;
			usleep(3000000); // Sleep for 3 seconds (3 million microseconds)
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

	cout << "\033[1;37m" << endl
		 << endl
		 << endl
		 << endl;
	while ((choice = mainMenu())) // loop while choice does not = 0
	{
		clearScreen();
		if (choice == 0) // If choice is 0, exit the program
		{
			cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
			cout << "\t║                EXITING PAYROLL MANAGEMENT SYSTEM - GOODBYE!                ║\n";
			cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			break;
		} // end if

		switch (choice) // Switch based on user choice
		{
		case 1: // Department Management
			departmentConsole();
			break;
		case 2: // Employee Management
			employeeConsole();
			break;
		case 3: // Payroll Management
			payrollConsole();
			break;
		default: // Invalid choice
			cout << endl
				 << endl
				 << endl;
			cout << "\t\t\a [ ℹ️/t Incorrect selection. Try again. ]" << endl;
			usleep(3000000); // Sleep for 3 seconds
			clearScreen();
			cin.clear();
			cin.ignore();
			break;
		} // end case

	} // end while
	cout << "\033[0m"; // Reset color
}
