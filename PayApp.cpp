
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
		shutdownCounter(3);
	}
	catch (runtime_error &r)
	{
		cerr << r.what() << endl;
	}
	catch (exception &e)
	{
		cerr << "\n\t❌ Critical error: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "\n\t[ ⚠️ Something unexpected has occurred. ]" << endl;
	}

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
            cout << "\n\t[🔄 RETURNING TO MAIN MENU... ]\n" << endl;
            usleep(1000000);
            clearScreen();
            break;
        }

        switch (choice) // Switch based on user choice
        {
        case 1: // Add new department record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("ADD NEW DEPARTMENT RECORD");
                int code = getValidatedInput("\t Enter Department code or [-1 to quit]: ");

                if (code == -1) // If user enters -1, break the loop
                    break;

                deptObject = deptPtr->createDepartment(code);
                deptPtr->addRecord(deptObject);
                cout << "\n\t[+] Department added.\n";
                usleep(3000000);
            }
            clearScreen();
            break;

        case 2: // Update existing department record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("UPDATE DEPARTMENT RECORD");
                int updateCode = getValidatedInput("\t Enter Department code to update or [-1 to quit]: ");

                if (updateCode == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    deptPtr->updateRecord(updateCode);
                    cout << "\n\t[~] Department updated.\n";
                }
                catch (const invalid_argument &e)
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
                displayHeader("VIEW DEPARTMENT RECORD");
                int searchCode = getValidatedInput("\t Enter Department code to view or [-1 to quit]: ");

                if (searchCode == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    deptPtr->viewRecord(searchCode);
                }
                catch (const invalid_argument &e)
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
            displayHeader("VIEW ALL DEPARTMENTS");
            deptPtr->viewAllRecords();
            pressEnterContinue();
            clearScreen();
            break;

        case 5: // Delete department record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("DELETE DEPARTMENT RECORD");
                int deleteCode = getValidatedInput("\t Enter Department code to delete or [-1 to quit]: ");

                if (deleteCode == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    deptPtr->deleteRecord(deleteCode);
                    cout << "\n\t[-] Department deleted.\n";
                }
                catch (const invalid_argument &e)
                {
                    cerr << e.what() << endl;
                }
                pressEnterContinue();
                clearScreen();
            }
            clearScreen();
            break;

        default: // Invalid choice
            cout << "\n\t[ ℹ️ Incorrect selection. Try again. ]\n";
            usleep(1000000);
            clearScreen();
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
    }

    delete deptPtr; // Clean up dynamically allocated memory
	clearScreen();
}

// Function: Employee Console
void employeeConsole()
{
    clearScreen();
    int choice;
    Employee empObject;
    Employee *empPtr = new Employee(); // Create a new instance of Employee

    while ((choice = employeeMenu())) // Loop while choice does not equal 0
    {
        clearScreen();
        if (choice == 0)
        {
            cout << "\n\t[ 🔄 RETURNING TO MAIN MENU... ]\n" << endl;
            usleep(1000000);
            clearScreen();
            break;
        }

        switch (choice) // Switch based on user choice
        {
        case 1: // Add new employee record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("ADD NEW EMPLOYEE RECORD");
                int id = getValidatedInput("\t Enter Employee ID or [-1 to quit]: ");

                if (id == -1) // If user enters -1, break the loop
                    break;

                empObject = empPtr->createEmployee(id);
                empPtr->addRecord(empObject);
                cout << "\n\t[✚] Employee added.\n";
                usleep(1000000);
            }
            clearScreen();
            break;

        case 2: // Update existing employee record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("UPDATE EXISTING EMPLOYEE INFORMATION");
                int updateId = getValidatedInput("\t Enter Employee ID to update or [-1 to quit]: ");

                if (updateId == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    empPtr->updateRecord(updateId);
                    cout << "\n\t[~] Employee updated.\n";
                }
                catch (const invalid_argument &e)
                {
                    cerr << e.what() << endl;
                }
                usleep(1000000);
            }
            clearScreen();
            break;

        case 3: // View specific employee record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("VIEW EMPLOYEE RECORD");
                int searchId = getValidatedInput("\t Enter Employee ID to view or [-1 to quit]: ");

                if (searchId == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    empPtr->viewRecord(searchId);
                    pressEnterContinue();
                }
                catch (const invalid_argument &e)
                {
                    cerr << e.what() << endl;
                }
            }
            clearScreen();
            break;

        case 4: // View all employee records
            clearScreen();
            sortEmployeeConsole(empFileName, empPayrollFileName);
            pressEnterContinue();
            clearScreen();
            break;

        case 5: // Delete employee record
            while (true) // Loop until user chooses to quit
            {
                displayHeader("DELETE EMPLOYEE RECORD");
                int deleteId = getValidatedInput("\t Enter Employee ID to delete or [-1 to quit]: ");

                if (deleteId == -1) // If user enters -1, break the loop
                    break;

                try
                {
                    empPtr->deleteRecord(deleteId);
                    cout << "\n\t[-] Employee deleted.\n";
                }
                catch (const invalid_argument &e)
                {
                    cerr << e.what() << endl;
                }
                usleep(1000000);
            }
            clearScreen();
            break;

        default: // Invalid choice
            cout << "\t\t[ ℹ️ Incorrect selection. Try again. ]" << endl;
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

// Function: Sort Employee Console
void sortEmployeeConsole(const string &empFileName, const string &empPayrollFileName)
{
    clearScreen();
    int choice;
    int existingNodes = 0;
    EmpList *emplist = new EmpList(); // Create a new instance of EmpList

    try
    {
        ifstream empFile(empFileName);
        ifstream empPayrollFile(empPayrollFileName);

        if (empFile.fail() || empPayrollFile.fail()) // Check if files opened successfully
        {
            throw runtime_error("\t[ ❌ ERROR ACCESSING FILE! ]");
        }

        int id, empId, departmentCode, deptCode;
        string firstName, lastName, position;
        float hoursWorked;
        Employee emp;

        while (empFile >> id >> firstName >> lastName >> departmentCode)
        {
            // Read the full line for position
            getline(empFile, position); // Read the rest of the line for position

            empPayrollFile >> empId >> deptCode >> hoursWorked; // Read from payroll file

            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(departmentCode);
            emp.setPosition(position);
            emp.setHoursWorked(hoursWorked);

            if (emp.getId() == empId && emp.getDepartmentCode() == deptCode)
            {
                emplist->insertAtFront(emp); // Initialize list
                ++existingNodes;
            }
        }

        if (existingNodes == 0) // No records found
        {
            cout << "\t\t\n[ ℹ️ No record(s) exist for Employees!!! ]\n\n";
        }

        empFile.close();
        empPayrollFile.close();
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
        return; // Exit on exception
    }

    //-----------------------------------------------------------------------//

    cout << endl << endl << endl << endl;
    while ((choice = sortedEmployeeMenu())) // Loop while choice does not = 0
    {
        if (choice == 0) // If choice is 0, return to main menu
        {
            cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "\t║                          RETURNING TO MAIN MENU                            ║\n";
            cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
            usleep(3000000); // Sleep for 3 seconds
            clearScreen();
            break;
        }

        switch (choice) // Switch based on user choice
        {
        case 1: // Sort by Employee ID
            displayHeader("EMPLOYEES SORTED BY EMPLOYEE ID");
            emplist->mergeSortById();
            emplist->traverse();
            break;

        case 2: // Sort by Last Name
            displayHeader("EMPLOYEES SORTED BY LAST NAME");
            emplist->mergeSortByLastName();
            emplist->traverse();
            break;

        case 3: // Sort by Department Code
            displayHeader("EMPLOYEES SORTED BY DEPARTMENT CODE");
            emplist->mergeSortByDepartmentCode();
            emplist->traverse();
            break;

        case 4: // Sort by Position
            displayHeader("EMPLOYEES SORTED BY POSITION");
            emplist->mergeSortByPosition();
            emplist->traverse();
            break;

        case 5: // Sort by Hours Worked
            displayHeader("EMPLOYEES SORTED BY HOURS WORKED");
            emplist->mergeSortByHoursWorked(); // Use merge sort instead of bubble sort
            emplist->traverse();
            break;

        default: // Invalid choice
            cout << endl << endl << endl;
            cout << "\t\t[ ℹ️ Incorrect selection. Try again. ]" << endl;
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

// Function: Process Employee Payroll Records
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

		while (empFile >> id >> firstName >> lastName >> deptCodeEmp)
		{
			// Read the full line for position
			getline(empFile, position); // Read the rest of the line for position
			
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
        ifstream payrollFile(payrollFileName);
        checkFileAccess(payrollFile);

        string line;
        bool found = false;

        while (getline(payrollFile, line))
        {
            istringstream iss(line);
            int id, deptCode;
            string firstName, lastName, position;
            float hrs, regularPay, overtimePay, grossPay;

            // Read fixed fields
            if (!(iss >> id >> firstName >> lastName >> deptCode))
                continue;

            // Read the rest of the line for position and pay details
            string restOfLine;
            getline(iss, restOfLine);

            // Use a stringstream to parse the rest of the line
            istringstream restStream(restOfLine);
            restStream >> ws; // Skip leading whitespace

            // Read position (which may contain spaces)
            getline(restStream, position, '\t'); // Read until the first tab or space
            restStream >> hrs >> regularPay >> overtimePay >> grossPay;

            if (searchId == id)
            {
                found = true;

                clearScreen();
                payrollLogo();
                createAndDisplayPayroll(id, firstName, lastName, deptCode,
                                        position, hrs, regularPay, overtimePay, grossPay);
                break;
            }
        }

        if (!found)
        {
            cout << "\t\t\n [ ❌ Record with Employee ID : " << searchId << " does not exist!!! ]\n\n";
        }
    }
    catch (const exception &e)
    {
        cerr << e.what();
    }
}

// Function: View All Payroll Records
void sortPayrollConsole(const string &payrollFileName)
{
    clearScreen();
    int choice;
    int existingNodes = 0; // Count of existing nodes
    PayList *payrollList = new PayList(); // Create a new instance of PayList

    try
    {
        ifstream payFile(payrollFileName);
        checkFileAccess(payFile);

        string line;
        Payroll payroll;

        // Read each line from the file
        while (getline(payFile, line))
        {
            istringstream iss(line);
            int empId, deptCode;
            string firstName, lastName, position;
            float hoursWorked, regularPay, otPay, grossPay;

            // Read fixed fields
            if (!(iss >> empId >> firstName >> lastName >> deptCode))
                continue; // Skip to the next line if reading fails

            // Read the rest of the line for position and pay details
            string restOfLine;
            getline(iss, restOfLine);
            istringstream restStream(restOfLine);
            restStream >> ws; // Skip leading whitespace

            // Read position (which may contain spaces)
            getline(restStream, position, '\t'); // Read until the first tab or space
            restStream >> hoursWorked >> regularPay >> otPay >> grossPay;

            // Set payroll details
            payroll.setId(empId);
            payroll.setFirstName(firstName);
            payroll.setLastName(lastName);
            payroll.setDepartmentCode(deptCode);
            payroll.setPosition(position);
            payroll.setHoursWorked(hoursWorked);
            payroll.setBasicPay(regularPay);
            payroll.setOvertimePay(otPay);
            payroll.setGrossPay(grossPay);

            // Insert payroll record into the list
            payrollList->insertAtFront(payroll);
            ++existingNodes; // Increment the count of existing nodes
        }

        if (existingNodes == 0) // If no records were found
        {
            cout << "\t\t\n[ ❌ No record(s) exist for Employees payroll. ]\n\n";
            return; // Exit if no records found
        }

        payFile.close();
    }
    catch (const exception &e)
    {
        cerr << "\t ❌ Exception occurred: " << e.what() << std::endl;
        return; // Exit on exception
    }

    cout << endl << endl << endl << endl;
    while ((choice = sortedPayrollMenu())) // loop while choice does not = 0
    {
        if (choice == 0)
        {
            cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
            cout << "\t║                          RETURNING TO MAIN MENU                            ║\n";
            cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝\n\n";
            usleep(3000000);
            clearScreen();
            break;
        }

        switch (choice) // Switch based on user choice
        {
        case 1:
			clearScreen();
            displayHeader("PAYROLL SORTED BY EMPLOYEE ID");
			payrollLogo();
            payrollList->mergeSortById();
            payrollList->traverse();
			clearScreen();
            break;

        case 2:
			clearScreen();
            displayHeader("PAYROLL SORTED BY EMPLOYEE LAST NAME");
			payrollLogo();
            payrollList->mergeSortByLastName();
            payrollList->traverse();
            break;

        case 3:
			clearScreen();
            displayHeader("PAYROLL SORTED BY DEPARTMENT CODE");
			payrollLogo();
            payrollList->mergeSortByDepartmentCode();
            payrollList->traverse();
			clearScreen();
            break;

        case 4:
			clearScreen();
            displayHeader("PAYROLL SORTED BY POSITION");
			payrollLogo();
            payrollList->mergeSortByPosition();
            payrollList->traverse();
			clearScreen();
            break;

        default: // Invalid choice
            cout << endl << endl << endl;
            cout << "\t\t\a[ ℹ️ Incorrect selection. Try again. ]" << endl;
            usleep(3000000);
            clearScreen();
            cin.clear();
            cin.ignore();
			clearScreen();
            break;
        }

        cout << endl << endl << endl << endl;
        pressEnterContinue();
        clearScreen();
    }
}

// Function: Delete Single Payroll Record
void deleteSinglePayroll(int searchId, const string &payrollFileName, const string &tempPayFileName)
{
	string line;
    bool found = false;
    bool deleted = false;

    try
    {
        ifstream payrollFile(payrollFileName);
        ofstream tempFile(tempPayFileName);

        checkFileAccess(payrollFile);
        checkFileAccess(tempFile);

        string line;
        bool found = false;

        while (getline(payrollFile, line))
        {
            istringstream iss(line);
            int id, deptCode;
            string firstName, lastName, position;
            float hrs, regularPay, overtimePay, grossPay;

            // Read fixed fields
            if (!(iss >> id >> firstName >> lastName >> deptCode))
                continue;

            // Read the rest of the line for position and pay details
            string restOfLine;
            getline(iss, restOfLine);

            // Use a stringstream to parse the rest of the line
            istringstream restStream(restOfLine);
            restStream >> ws; // Skip leading whitespace

            // Read position (which may contain spaces)
            getline(restStream, position, '\t'); // Read until the first tab or space
            restStream >> hrs >> regularPay >> overtimePay >> grossPay;


            if (searchId == id) // If the searched ID matches the current record's ID
            {
                found = true; // Set found flag to true
                clearScreen();

                cout << "\n╔════════════════════════════════════════════════════════════════════════════════════╗\n";
                cout << "║                           PAYROLL RECORD FOUND                                   ║\n";
                cout << "╠════════════════════════════════════════════════════════════════════════════════════╣\n";
                payrollLogo();
                createAndDisplayPayroll(id, firstName, lastName, deptCode, position, hrs, regularPay, overtimePay, grossPay);
                cout << "╚════════════════════════════════════════════════════════════════════════════════════╝\n";

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
                    deleted = true; // Mark as deleted
                    // Skip writing this record to temp file (deleting)
                }
                else // If user cancels deletion
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

            cout << "\n [ ✅ Payroll record with Employee ID: " << searchId << " has been deleted. ]" << endl << endl;
        }
        else // If deletion was cancelled
        {
            // Deletion cancelled, remove temp file as original file remains unchanged
            remove(tempPayFileName.c_str());
            cout << "\n\t [ ❌ Payroll record with Employee ID: " << searchId << " was not deleted. ]" << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
}

// Function: Payroll Console
void payrollConsole()
{
    clearScreen();
    int choice;

    while ((choice = payrollMenu())) // Loop while choice does not equal 0
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

        switch (choice) // Switch based on user choice
        {
        case 1: // Process payroll records
			clearScreen();
            displayHeader("PROCESSED EMPLOYEE PAYROLL RECORD");
            payrollProcessing(ratesFileName, empFileName, empPayrollFileName, payrollFileName); // Call function to process payroll records
            pressEnterContinue();
            clearScreen();
            break;

        case 2: // View single payroll record
			clearScreen();
            while (true) // Loop until user chooses to quit
            {
                displayHeader("VIEW EMPLOYEE PAYROLL RECORD");
                int searchId = getValidatedInput("\t ENTER EMPLOYEE ID TO LOOKUP PAYROLL RECORD OR [-1] TO QUIT: ");

                if (searchId == -1) // Condition to exit loop
                    break;

                viewSinglePayroll(searchId, payrollFileName); // Call function to view single payroll record
                pressEnterContinue();
                clearScreen();
            }
            break;

        case 3: // View all payroll records
			clearScreen();
            sortPayrollConsole(payrollFileName); // This option allows you to view all payroll records sorted by various criteria.
            pressEnterContinue();
            clearScreen();
            break;

        case 4: // Delete single payroll record
			clearScreen();
            while (true) // Loop until user chooses to quit
            {
                displayHeader("DELETE EMPLOYEE PAYROLL RECORD");
                int deleteId = getValidatedInput("\t ENTER EMPLOYEE ID TO DELETE PAYROLL RECORD OR [-1] TO QUIT: ");

                if (deleteId == -1) // Condition to exit loop
                    break;

                deleteSinglePayroll(deleteId, payrollFileName, tempPayFileName); // Call function to delete single payroll record
                pressEnterContinue();
                clearScreen();
            }
            break;

        default: // Invalid choice
            cout << "\n\t[ ℹ️ Incorrect selection. Try again. ]\n";
            usleep(3000000); // Sleep for 3 seconds
            clearScreen();
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
    }
	clearScreen();
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
