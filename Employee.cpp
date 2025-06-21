#include "Employee.h"

// Constants for file names
const string EMP_FILE_NAME = "employee.txt";
const string TEMP_EMP_FILE_NAME = "tempemp.txt";
const string EMP_PAYROLL_FILE_NAME = "employee_payroll.txt";
const string TEMP_EMP_PAYROLL_FILE_NAME = "temp_emp_payroll.txt";

// Destructor
Employee::~Employee() {}

// Default constructor
Employee::Employee() 
    : id(0), firstName("first name"), lastName("last name"), 
      departmentCode(0), position("position"), hoursWorked(0.0f) {}

// Primary constructor
Employee::Employee(int id, const string& firstName, const string& lastName, 
                   int departmentCode, const string& position, float hoursWorked)
    : id(id), firstName(firstName), lastName(lastName), 
      departmentCode(departmentCode), position(position), hoursWorked(hoursWorked) {}

// Copy constructor
Employee::Employee(const Employee &Emp) 
    : id(Emp.id), firstName(Emp.firstName), lastName(Emp.lastName), 
      departmentCode(Emp.departmentCode), position(Emp.position), hoursWorked(Emp.hoursWorked) {}

// Mutators
void Employee::setId(int empId) { id = empId; }
void Employee::setFirstName(const string& fn) { firstName = fn; }
void Employee::setLastName(const string& ln) { lastName = ln; }
void Employee::setDepartmentCode(int deptCode) { departmentCode = deptCode; }
void Employee::setPosition(const string& post) { position = post; }
void Employee::setHoursWorked(float hr) { hoursWorked = hr; }

// Accessors
int Employee::getId() const { return id; }
string Employee::getFirstName() const { return firstName; }
string Employee::getLastName() const { return lastName; }
int Employee::getDepartmentCode() const { return departmentCode; }
string Employee::getPosition() const { return position; }
float Employee::getHoursWorked() const { return hoursWorked; }

// Center text utility function
string centerText(const string& text, int width) {
    int len = (int)text.length();
    if (width <= len) return text.substr(0, width);
    int leftPadding = (width - len) / 2;
    int rightPadding = width - len - leftPadding;
    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
}

// Display header
void Employee::displayHeader() const {
    cout << "\n";
    cout << "\t" << " ╔════════════════╦══════════════════════════════╦══════════════════════════════╦════════════════╦══════════════════════════════╦════════════════╗" << endl;
    cout << "\t" << " ║"
         << centerText("ID", 16) << "║"
         << centerText("FIRST NAME", 30) << "║"
         << centerText("LAST NAME", 30) << "║"
         << centerText("DEPT CODE", 16) << "║"
         << centerText("POSITION", 30) << "║"
         << centerText("HOURS", 16) << "║" << endl;
    cout << "\t" << " ╠════════════════╬══════════════════════════════╬══════════════════════════════╬════════════════╬══════════════════════════════╬════════════════╣" << endl;
}

// Display employee details
void Employee::display() const {
    cout << setfill(' '); // Ensure fill character is space
    cout << "\t" << " ║ " << left << setw(15) << getId()
         << "║ " << left << setw(29) << getFirstName().substr(0, 29)
         << "║ " << left << setw(29) << getLastName().substr(0, 29)
         << "║ " << left << setw(15) << getDepartmentCode()
         << "║ " << left << setw(25) << getPosition().substr(0, 25)
         << "║ " << right << setw(14) << fixed << setprecision(2) << getHoursWorked()
         << " ║" << endl;
    cout << "\t" << " ╚════════════════╩══════════════════════════════╩══════════════════════════════╩════════════════╩══════════════════════════════╩════════════════╝";
}

// Utility function to get validated input for string
string Employee::getValidatedString(const string& prompt) {
    string input;
    cout << prompt;

    if (cin.peek() == '\n') cin.ignore(); // Clear leftover newline if present
    getline(cin, input);
    
    // Input validation: ensure input is not empty
    while (input.empty()) {
        cout << "Input cannot be empty. Please enter again: ";
        getline(cin, input);
    }
    return input;
}

// Utility function to get validated input for integer
int Employee::getValidatedInt(const string& prompt) {
    int value;

    cout << prompt;

    // Input validation loop
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a numeric value: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character
    return value;
}

// Utility function to get validated input for float
float Employee::getValidatedFloat(const string& prompt) {
    float value;
    
    cout << prompt;
    // Input validation loop
    while (!(cin >> value) || value < 0) {
        cout << "Invalid input. Please enter a non-negative numeric value: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character
    return value;
}

// Create employee with input validation
Employee Employee::createEmployee(int empId) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    string firstName = getValidatedString("➡️\t Enter Employee first name: ");
    cout << endl;
    string lastName = getValidatedString("➡️\t Enter Employee last name: ");
    cout << endl;
    int departmentCode = getValidatedInt("➡️\t Enter Employee department code: ");
    cout << endl;
    string position = getValidatedString("➡️\t Enter Employee position: ");
    cout << endl;
    float hoursWorked = getValidatedFloat("➡️\t Enter Employee hours worked: ");
    cout << endl;

    return Employee(empId, firstName, lastName, departmentCode, position, hoursWorked);
}

// Utility function to check file access and create file if it does not exist
bool Employee::checkFileAccess(ifstream& file, const string& filename) {
    // Check if the file can be opened
    if (!file) { 
        ofstream createFile(filename); 

        // If file creation fails, throw an error
        if (!createFile) {
            throw runtime_error("\t [ ❌ ERROR CREATING FILE: " + filename + " ]");
        }
        createFile.close(); 
    }
    return true; 
}

// Overload for ofstream
bool Employee::checkFileAccess(ofstream& file, const string& filename) {

    // Check if the file can be opened
    if (!file) { 
        ofstream createFile(filename);
        // If file creation fails, throw an error
        if (!createFile) {
            throw runtime_error("\t [ ❌ ERROR CREATING FILE: " + filename + " ]");
        }
        createFile.close(); 
    }
    return true; 
}


// Helper function to write an employee record to files
void Employee::writeRecord(ofstream& empFile, ofstream& empPayrollFile, const Employee& emp) {
    empFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t"
            << emp.getDepartmentCode() << "\t" << emp.getPosition() << endl;
    empPayrollFile << emp.getId() << "\t" << emp.getDepartmentCode() << "\t" << emp.getHoursWorked() << endl;
}

// Function: Add record
void Employee::addRecord(const Employee& emp) {
    // Check if all fields are valid
    if (emp.getId() == 0 || emp.getFirstName().empty() || emp.getLastName().empty() ||
        emp.getDepartmentCode() == 0 || emp.getPosition().empty() || emp.getHoursWorked() < 0) {
        cout << "\t\n [ ℹ️ Cannot add record: All fields must be non-empty and valid! ]\n\n";
        return;
    }

    try {
        ifstream empFileCheck(EMP_FILE_NAME);
        checkFileAccess(empFileCheck, EMP_FILE_NAME);

        int id, deptCode;
        string firstName, lastName, position;
        bool exists = false;
        bool nameExists = false;

        // Check for duplicate records based on ID and name
        while (empFileCheck >> id >> firstName >> lastName >> deptCode >> position) {
            // Check if the ID or name already exists
            if (id == emp.getId()) {
                exists = true;
                break;
            }

            // Check if the name already exists
            if (firstName == emp.getFirstName() && lastName == emp.getLastName()) {
                nameExists = true;
                break;
            }
        }

        empFileCheck.close(); // Close the file after checking for duplicates

        // If a duplicate record exists, do not add the new record
        if (exists) {
            cout << endl << "\n\t[ ℹ️\t Record with Employee Id: " << emp.getId() << " already exists. Cannot add duplicate. ]" << endl << endl;
            return;
        }

        // If a record with the same name exists, do not add the new record
        if (nameExists) {
            cout << endl << "\n\t[ ℹ️\t Record with Employee name: " << emp.getFirstName() << " " << emp.getLastName() << " already exists. Cannot add duplicate. ]" << endl << endl;
            return;
        }

        // If no duplicates found, proceed to add the record
        ofstream empFile(EMP_FILE_NAME, ios::app);
        ofstream empPayrollFile(EMP_PAYROLL_FILE_NAME, ios::app);
        // Check file access for both files
        checkFileAccess(empFile, EMP_FILE_NAME);
        checkFileAccess(empPayrollFile, EMP_PAYROLL_FILE_NAME);

        // Write the employee record to both files
        writeRecord(empFile, empPayrollFile, emp);

        // Close the files after writing
        empFile.close();
        empPayrollFile.close();
        cout << endl << "\n\t[ ✅\t Record with Employee Id: " << emp.getId() << " added successfully. ]" << endl;
        cout << endl;

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: Update employee record
void Employee::updateRecord(int updateId) {
    try {
        bool found = false;
        ifstream empFile(EMP_FILE_NAME);
        ofstream empTempFile(TEMP_EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);
        ofstream tempEmpPayrollFile(TEMP_EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile, EMP_FILE_NAME);
        checkFileAccess(empPayrollFile, EMP_PAYROLL_FILE_NAME);
        checkFileAccess(empTempFile, TEMP_EMP_FILE_NAME);
        checkFileAccess(tempEmpPayrollFile, TEMP_EMP_PAYROLL_FILE_NAME);

        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        // Read records from both employee and payroll files
        while (empFile >> id >> firstName >> lastName >> deptCode) {
            empFile.ignore(); // Ignore the newline character after deptCode
            std::getline(empFile, position); // Read the entire line for position

            empPayrollFile >> id >> deptCode >> hrs;

            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            // If the ID matches the one to be updated
            if (updateId == emp.getId()) {
                found = true;

                cout << "\n";
                cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                          EMPLOYEE RECORD FOUND                             ║" << endl;
                cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;
                emp.displayHeader();
                emp.display();

                cout << "\n\n\n ▶️  Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();

                cout << "\n";
                cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
                cout << "║                      UPDATE EMPLOYEE INFORMATION                           ║" << endl;
                cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl << endl;

                Employee updateEmp = createEmployee(updateId);
                empTempFile << updateEmp.getId() << "\t" << updateEmp.getFirstName() << "\t" 
                            << updateEmp.getLastName() << "\t" << updateEmp.getDepartmentCode() << "\t" 
                            << updateEmp.getPosition() << endl;
                tempEmpPayrollFile << updateEmp.getId() << "\t" << updateEmp.getDepartmentCode() << "\t" 
                                   << updateEmp.getHoursWorked() << endl;

                cout << "\n\n\t[ ✅ Record with Employee Id: " << updateId << " has been updated ]" << endl << endl;
            } else {
                writeRecord(empTempFile, tempEmpPayrollFile, emp);
            }
        }

        // If no record was found with the given ID
        if (!found) {
            cout << "\n\t[ ℹ️\t Record with Employee Id : " << updateId << " does not exist! ]\n\n";
        }

        // Close all files
        empFile.close();
        empTempFile.close();
        empPayrollFile.close();
        tempEmpPayrollFile.close();

        // Rename temporary files to original file names
        remove(EMP_FILE_NAME.c_str());
        rename(TEMP_EMP_FILE_NAME.c_str(), EMP_FILE_NAME.c_str());
        remove(EMP_PAYROLL_FILE_NAME.c_str());
        rename(TEMP_EMP_PAYROLL_FILE_NAME.c_str(), EMP_PAYROLL_FILE_NAME.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: View employee record for a specific ID
void Employee::viewRecord(int searchId) {
    try {
        ifstream empFile(EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile, EMP_FILE_NAME);
        checkFileAccess(empPayrollFile, EMP_PAYROLL_FILE_NAME);

        bool found = false;
        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        // Read records from both employee and payroll files
        while (empFile >> id >> firstName >> lastName >> deptCode) {
          
            empFile.ignore(); // Ignore the newline character after deptCode
            getline(empFile, position); // Read the entire line for position

            empPayrollFile >> id >> deptCode >> hrs;

            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);
    
            // If the ID matches the one to be viewed
            if (searchId == emp.getId()) {
                found = true;
                emp.displayHeader();
                emp.display();
                break;
            }
        }

        // Close the files after reading
        if (!found) {
            cout << "\n\t [ ℹ️\t Record with Employee Id : " << searchId << " does not exist! ]\n\n";
        }

        // Close the files
        empFile.close();
        empPayrollFile.close();

    } catch (exception &i) {
        cerr << i.what();
    }
}


// Function: View all employee records
void Employee::viewAllRecords() {
    try {
        ifstream empFile(EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile, EMP_FILE_NAME);
        checkFileAccess(empPayrollFile, EMP_PAYROLL_FILE_NAME);

        int recordCount = 0;
        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        emp.displayHeader(); // Display header for employee records

        // Read records from both employee and payroll files
        while (empFile >> id >> firstName >> lastName >> deptCode) {
            empFile.ignore(); // Ignore the newline character after deptCode
            std::getline(empFile, position); // Read the entire line for position

            empPayrollFile >> id >> deptCode >> hrs;

            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            ++recordCount; // Increment record count
            emp.display();
            cout << endl;
        }

        // Close the files after reading
        if (recordCount == 0) {
            cout << "\n\t [ℹ️ No record(s) Employee exist! ]\n\n";
        }

        // Close the files
        empFile.close();
        empPayrollFile.close();

    } catch (exception &i) {
        cerr << i.what();
    }
}

// Function: Delete employee record
void Employee::deleteRecord(int deleteId) {
    bool found = false;
    bool deleted = false; 

    try {
        ifstream empFile(EMP_FILE_NAME);
        ifstream empPayrollFile(EMP_PAYROLL_FILE_NAME);
        ofstream empTempFile(TEMP_EMP_FILE_NAME);
        ofstream tempEmpPayrollFile(TEMP_EMP_PAYROLL_FILE_NAME);

        checkFileAccess(empFile, EMP_FILE_NAME);
        checkFileAccess(empPayrollFile, EMP_PAYROLL_FILE_NAME);
        checkFileAccess(empTempFile, TEMP_EMP_FILE_NAME);
        checkFileAccess(tempEmpPayrollFile, TEMP_EMP_PAYROLL_FILE_NAME);

        Employee emp;
        int id, deptCode;
        string firstName, lastName, position;
        float hrs;

        // Read records from both employee and payroll files
        while (empFile >> id >> firstName >> lastName >> deptCode) {
          
            empFile.ignore(); // Ignore the newline character after deptCode
            getline(empFile, position); // Read the entire line for position

            empPayrollFile >> id >> deptCode >> hrs;

            emp.setId(id);
            emp.setFirstName(firstName);
            emp.setLastName(lastName);
            emp.setDepartmentCode(deptCode);
            emp.setPosition(position);
            emp.setHoursWorked(hrs);

            // If the ID matches the one to be deleted
            if (deleteId == emp.getId()) {
                found = true; // Set found flag to true

                cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
                cout << "\t║                          EMPLOYEE RECORD FOUND                             ║" << endl;
                cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣" << endl;
                emp.displayHeader();
                emp.display();
                cout << "\n\t╚══════════════════════════════════════════════════════════════════════════════╝" << endl;

                char confirm;
                // Input validation loop
                do {
                    cout << "\t║   ❗ WARNING: This action will permanently delete the employee record.        " << endl;
                    cout << "\t║   ❗ Are you sure you want to delete this record? (y/n): ";
                    cin >> confirm;
                    confirm = tolower(confirm);

                    // Validate input
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\t║   [ ❌ Invalid input. Please enter 'y' or 'n'. ]" << endl;
                    }

                    // Check if input is valid
                    if (confirm != 'y' && confirm != 'n')
                        cout << "\t║   Please enter 'y' or 'n'." << endl;
                } while (confirm != 'y' && confirm != 'n'); // End of input validation loop

                cout << "\t║" << endl;
                cout << "\t╚══════════════════════════════════════════════════════════════════════════════╝" << endl << endl;

                // If user confirms deletion
                if (confirm == 'y') {
                    cout << "\n\t[  ❌ Deleting employee record... ]" << endl;
                    deleted = true;
                    // Do not write this record to temp files (effectively deleting)
                    continue;
                } else {
                    cout << "\n\t [ ℹ️  Deletion cancelled. Employee record will be kept. ]" << endl;
                    writeRecord(empTempFile, tempEmpPayrollFile, emp);
                }
            } else {
                writeRecord(empTempFile, tempEmpPayrollFile, emp);
            }
        }

        // If no record was found with the given ID
        empFile.close();
        empPayrollFile.close();
        empTempFile.close();
        tempEmpPayrollFile.close();

        // Remove original files and rename temporary files if deletion was successful
       if (!found) {
            remove(TEMP_EMP_FILE_NAME.c_str());
            remove(TEMP_EMP_PAYROLL_FILE_NAME.c_str());
            cout << "\n\t [ ❌ Record with Employee Id: " << deleteId << " does not exist!!! ]\n\n";
        } else if (found && deleted) {
            if (remove(EMP_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t [ ❌ ERROR REMOVING ORIGINAL EMPLOYEE FILE! ]");
            if (rename(TEMP_EMP_FILE_NAME.c_str(), EMP_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t [ ❌ ERROR RENAMING TEMP EMPLOYEE FILE! ]");
            if (remove(EMP_PAYROLL_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t [ ❌ ERROR REMOVING ORIGINAL PAYROLL FILE! ]");
            if (rename(TEMP_EMP_PAYROLL_FILE_NAME.c_str(), EMP_PAYROLL_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t [ ❌ ERROR RENAMING TEMP PAYROLL FILE! ]");
            cout << "\n\t [ ✅ Employee record with Id: " << deleteId << " has been deleted. ]" << endl << endl;
        } else {
            // Deletion cancelled, remove temp files as original files remain unchanged
            remove(TEMP_EMP_FILE_NAME.c_str());
            remove(TEMP_EMP_PAYROLL_FILE_NAME.c_str());
            cout << "\n\t [ ❌ Employee record with Id: " << deleteId << " was not deleted. ]" << endl;
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
// End of Employee.cpp