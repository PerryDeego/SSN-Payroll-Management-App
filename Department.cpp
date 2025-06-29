#include "Department.h"

// Constants for file names
const string DEPT_FILE_NAME = "department.txt";
const string TEMP_DEPT_FILE_NAME = "tempdept.txt";
const string RATES_FILE_NAME = "rates.txt";
const string TEMP_RATES_FILE_NAME = "temprates.txt";

// Destructor
Department::~Department() {}

// Default constructor
Department::Department() : code(0), name("department name"), hourlyRate(0.0f), overtimeRate(0.0f) {}

// Primary constructor
Department::Department(int code, const string& name, float hourlyRate, float overtimeRate)
    : code(code), name(name), hourlyRate(hourlyRate), overtimeRate(overtimeRate) {}

// Copy constructor
Department::Department(const Department &Dept)
    : code(Dept.code), name(Dept.name), hourlyRate(Dept.hourlyRate), overtimeRate(Dept.overtimeRate) {}

// Mutators
void Department::setCode(int cd) { code = cd; }
void Department::setName(const string& deptName) { name = deptName; }
void Department::setHourlyRate(float hrRate) { hourlyRate = hrRate; }
void Department::setOvertimeRate(float otRate) { overtimeRate = otRate; }

// Accessors
int Department::getCode() const { return code; }
string Department::getName() const { return name; }
float Department::getHourlyRate() const { return hourlyRate; }
float Department::getOvertimeRate() const { return overtimeRate; }

// Function: Display header for department records
void Department::displayHeader() const {
    cout << "\n";
    cout <<"\t" << " ╔═════════════════════╦══════════════════════════════╦════════════════╦════════════════════╗" << endl;
    cout << "\t" << " ║  DEPARTMENT CODE    ║      DEPARTMENT NAME         ║  HOURLY RATE   ║   OVERTIME RATE    ║" << endl;
    cout << "\t" << " ╠═════════════════════╬══════════════════════════════╬════════════════╬════════════════════╣" << endl;
}

// Function: Display department record
void Department::display() const {
    cout << setfill(' '); // Ensure fill character is space

    cout << "\t" << " ║ " << left << setw(19) << getCode()
         << " ║ " << left << setw(28) << getName().substr(0, 28)
         << " ║ $" << right << setw(13) << fixed << setprecision(2) << getHourlyRate()
         << " ║ $" << right << setw(17) << fixed << setprecision(2) << getOvertimeRate()
         << " ║" << endl;
}


// Utility function to get validated rate input
float Department::getValidatedRate(const string& prompt) {
    float rate;
    cout << prompt;
    while (!(cin >> rate) || rate <= 0.0f) {
        cout << "\t [ ❌ Invalid input. Please enter a positive numeric value: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return rate;
}

// Function: Create department
Department Department::createDepartment(int deptcode) {
    string name;
    float hourlyRate = 0.0f, overtimeRate = 0.0f;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    cout << "➡️\t Enter Department name: ";
    getline(cin, name);
    cout << endl;
    
    // Input validation for hourly rate
    hourlyRate = getValidatedRate("➡️\t Enter Department hourly rate: ");
    cout << endl;
    
    // Input validation for overtime rate
    overtimeRate = getValidatedRate("➡️\t Enter Department overtime rate: ");
    cout << endl;
    
    return Department(deptcode, name, hourlyRate, overtimeRate);
}

// Utility function to check file access and create file if it does not exist
bool Department::checkFileAccess(ifstream& file, const string& filename) {
    if (!file) { 
        ofstream createFile(filename); 
        if (!createFile) {
            throw runtime_error("\t [ ❌ ERROR CREATING FILE: " + filename + " ]");
        }
        createFile.close(); 
    }
    return true; 
}

// Overload for ofstream
bool Department::checkFileAccess(ofstream& file, const string& filename) {
    if (!file) { 
        ofstream createFile(filename);
        if (!createFile) {
            throw runtime_error("\t [ ❌ ERROR CREATING FILE: " + filename + " ]");
        }
        createFile.close(); 
    }
    return true; 
}


// Helper function to write a department record to files
void Department::writeRecord(ofstream& deptFile, ofstream& ratesFile, const Department& dept) {
    deptFile << dept.getCode() << "\t" << dept.getName() << endl;
    ratesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
}

// Function: Add record
void Department::addRecord(const Department& dept) {
    if (dept.getCode() == 0 || dept.getName().empty() || dept.getHourlyRate() <= 0.0f || dept.getOvertimeRate() <= 0.0f) {
        cout << "\n\t [ ❌ Cannot add record: All fields must be non-empty and non-zero! ]\n\n";
        return;
    }

    try {
        ifstream deptNewFile(DEPT_FILE_NAME);
        checkFileAccess(deptNewFile, DEPT_FILE_NAME); 

        int deptCode;
        string deptName;
        bool exists = false;

        // Check for duplicate code or name
        while (deptNewFile >> deptCode) {
            deptNewFile.ignore(); // skip tab
            getline(deptNewFile, deptName);

            // Check if the department code or name already exists
            if (dept.getCode() == deptCode) {
                cout << "\n\t [ ❌ Record with Department Code: " << dept.getCode() << " already exists! ]\n\n";
                exists = true;
                break;
            } else if (dept.getName() == deptName) {
                cout << "\n\t [ ❌ Record with Department Name: " << dept.getName() << " already exists! ]\n\n";
                exists = true;
                break;
            }
        }
        deptNewFile.close();

        // If no duplicate found, proceed to add the record
        if (exists) {
            return;
        }

        // Open files for appending
        ofstream deptFile(DEPT_FILE_NAME, ios::app);
        ofstream ratesFile(RATES_FILE_NAME, ios::app);
        // Check file access for both files
        checkFileAccess(deptFile, DEPT_FILE_NAME); 
        checkFileAccess(ratesFile, RATES_FILE_NAME); 

        writeRecord(deptFile, ratesFile, dept);
        cout << "\n\t [ ✅ Record with code: " << dept.getCode() << " added successfully... ]" << endl;

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}


// Function: Update record
void Department::updateRecord(int updateCode) {
    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);
        ofstream tempDeptFile(TEMP_DEPT_FILE_NAME);
        ofstream tempRatesFile(TEMP_RATES_FILE_NAME);

        // Check file access for all files
        checkFileAccess(deptFile, DEPT_FILE_NAME);
        checkFileAccess(ratesFile, RATES_FILE_NAME);
        checkFileAccess(tempDeptFile, TEMP_DEPT_FILE_NAME);
        checkFileAccess(tempRatesFile, TEMP_RATES_FILE_NAME);

        bool found = false;
        vector<pair<int, string>> existingRecords; // Vector to store existing records for duplicate checking

        // Read existing records into a vector for duplicate checking
        while (true) {
            int deptCode, deptRateCode;
            string deptName;
            float hrRate, otRate;

            // Read department code and name
            if (!(deptFile >> deptCode)) break; 
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);

            // Read rates
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            existingRecords.emplace_back(deptCode, deptName); // Store existing records for duplicate checking

            // Check if the current record matches the update code
            if (deptCode == updateCode && deptRateCode == updateCode) {
                found = true;

                // Store the record to be updated
                Department deptToUpdate(deptCode, deptName, hrRate, otRate);
                deptToUpdate.displayHeader();
                deptToUpdate.display();
                cout << endl << endl << endl;

                deptToUpdate = createDepartment(updateCode);

                bool duplicateFound = false; // Flag to check for duplicates

                // Check if the current department code is different and the name matches an existing record
                for (const auto& record : existingRecords) {
                    if (deptToUpdate.getCode() != record.first && deptToUpdate.getName() == record.second) {
                        cout << "\n\t [ ❌ Duplicate Department Name: " << deptToUpdate.getName() << " already exists! ]\n\n";
                        duplicateFound = true;
                        break;
                    }
                }

                // If a duplicate was found, write the original record to the temporary files
                if (duplicateFound) {
                    writeRecord(tempDeptFile, tempRatesFile, Department(deptCode, deptName, hrRate, otRate));
                } else {
                    writeRecord(tempDeptFile, tempRatesFile, deptToUpdate);
                    cout << "\n\t [ ✅ Record with Department Code: " << updateCode << " has been updated ]" << endl;
                }
            } else {
                writeRecord(tempDeptFile, tempRatesFile, Department(deptCode, deptName, hrRate, otRate));
            }
        }

        // If no record was found with the update code
        if (!found) {
            cout << "\n\t [ ❌ Record with Department Code: " << updateCode << " does not exist! ]\n\n";
        }

        // Close all files
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        // Replace original files with temporary files
        remove(DEPT_FILE_NAME.c_str());
        rename(TEMP_DEPT_FILE_NAME.c_str(), DEPT_FILE_NAME.c_str());
        remove(RATES_FILE_NAME.c_str());
        rename(TEMP_RATES_FILE_NAME.c_str(), RATES_FILE_NAME.c_str());

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Function: View record
void Department::viewRecord(int searchCode) {
    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);

        checkFileAccess(deptFile, DEPT_FILE_NAME);
        checkFileAccess(ratesFile, RATES_FILE_NAME);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        displayHeader();
        // Read department records and rates
        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);

            // Read rates
            // If reading rates fails, break the loop
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            // Check if the current record matches the search code
            if (searchCode == dept.getCode() && dept.getCode() == deptRateCode) {
                found = true;
                dept.display();
                break;
            }
        }

        // If no record was found with the search code
        if (!found) {
            cout << "\n\t [ ❌ Record with Department Code: " << searchCode << " does not exist! ]\n\n";
        }

        // Close files
        deptFile.close();
        ratesFile.close();

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: View all records
void Department::viewAllRecords() {
    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);
        
        checkFileAccess(deptFile, DEPT_FILE_NAME);
        checkFileAccess(ratesFile, RATES_FILE_NAME);

        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;
        int recordsCounter = 0;

        displayHeader();

        // Read department records and rates
        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);

            // If reading rates fails, break the loop
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            recordsCounter++; // Increment the record counter
            dept.display();
            cout << endl;
        }

        // If no records were found
        if (recordsCounter == 0) {
            cout << "\n\t[ ❌ No Department records exist! ]\n\n";
        }

        // Display total records found
        deptFile.close();
        ratesFile.close();

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: Delete record
void Department::deleteRecord(int deleteCode) {
    bool found = false;
    bool deleted = false; 

    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);
        ofstream tempDeptFile(TEMP_DEPT_FILE_NAME);
        ofstream tempRatesFile(TEMP_RATES_FILE_NAME);

        checkFileAccess(deptFile, DEPT_FILE_NAME);
        checkFileAccess(ratesFile, RATES_FILE_NAME);
        checkFileAccess(tempDeptFile, TEMP_DEPT_FILE_NAME);
        checkFileAccess(tempRatesFile, TEMP_RATES_FILE_NAME);

        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        // Read department records and rates
        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);

            // If reading rates fails, break the loop
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            // Check if the current record matches the delete code
            if (deleteCode == deptCode && deptCode == deptRateCode) {
                found = true;

                cout << "\n\t╔════════════════════════════════════════════════════════════════════════════════════╗" << endl;
                cout << "\t║                           DEPARTMENT RECORD FOUND                                ║" << endl;
                cout << "\t╠════════════════════════════════════════════════════════════════════════════════════╣" << endl;
                Department dept(deptCode, deptName, hrRate, otRate);
                displayHeader();
                dept.display();
                cout << "\n\t╚════════════════════════════════════════════════════════════════════════════════════╝" << endl;

                char confirm;
                // Input validation loop
                do {
                    cout << "\t║   ❗ WARNING: This action will permanently delete the department record.           " << endl;
                    cout << "\t║   ❗ Are you sure you want to delete this record? (y/n): ";
                    cin >> confirm;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\t║   [ ❌ Invalid input. Please enter 'y' or 'n'. ]" << endl;
                    }

                    confirm = tolower(confirm);

                    // Check if input is valid
                    if (confirm != 'y' && confirm != 'n')
                        cout << "\t║   Please enter 'y' or 'n'." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

                // Display confirmation message
                } while (confirm != 'y' && confirm != 'n');

                cout << "\t║" << endl;
                cout << "\t╚════════════════════════════════════════════════════════════════════════════════════╝" << endl << endl;

                // If user confirms deletion
                if (confirm == 'y') {
                    cout << "\n\t[ ❌ Deleting department record... ]" << endl;
                    deleted = true;
                    
                } else {
                    cout << "\n\t\t[ ℹ️  Deletion cancelled. Department record will be kept. ]" << endl;
                    Department dept(deptCode, deptName, hrRate, otRate);
                    writeRecord(tempDeptFile, tempRatesFile, dept);
                }
            } else {
                Department dept(deptCode, deptName, hrRate, otRate);
                writeRecord(tempDeptFile, tempRatesFile, dept);
            }
        }

        // Close all files
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        // If no record was found with the delete code
        if (!found) {
            remove(TEMP_DEPT_FILE_NAME.c_str());
            remove(TEMP_RATES_FILE_NAME.c_str());
            cout << "\t\n[ ❌ Record with Department Code: " << deleteCode << " does not exist!!! ]\n\n";
        } else if (found && deleted) {
            if (remove(DEPT_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t[ ❌ ERROR REMOVING ORIGINAL DEPARTMENT FILE! ]");
            if (rename(TEMP_DEPT_FILE_NAME.c_str(), DEPT_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t[ ❌ ERROR RENAMING TEMP DEPARTMENT FILE! ]");
            if (remove(RATES_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t[ ❌ ERROR REMOVING ORIGINAL RATES FILE! ]");
            if (rename(TEMP_RATES_FILE_NAME.c_str(), RATES_FILE_NAME.c_str()) != 0)
                throw runtime_error("\t[ ❌ ERROR RENAMING TEMP RATES FILE! ]");
            cout << "\n\t[ ✅ Department record with Code: " << deleteCode << " has been deleted. ]" << endl << endl;
        } else {
            remove(TEMP_DEPT_FILE_NAME.c_str());
            remove(TEMP_RATES_FILE_NAME.c_str());
            cout << "\n\t[ ❌ Department record with Code: " << deleteCode << " was not deleted. ]" << endl;
        }
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
