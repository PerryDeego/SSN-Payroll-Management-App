#include "Department.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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
    cout << "+-------------------+--------------------------+----------------+-------------------+" << endl;
    cout << "| DEPARTMENT CODE   | DEPARTMENT NAME          | HOURLY RATE    | OVERTIME RATE     |" << endl;
    cout << "+-------------------+--------------------------+----------------+-------------------+" << endl;
}

void Department::display() const {
    cout << "|+ Department Code   : " << getCode() << endl;
    cout << "|+ Department Name   : " << getName() << endl;
    cout << "|+ Hourly Rate       : $" << fixed << setprecision(2) << getHourlyRate() << endl;
    cout << "|+ Overtime Rate     : $" << fixed << setprecision(2) << getOvertimeRate() << endl;
    cout << "+-----------------------------------------------+" ;
}

// Utility function to get validated rate input
float Department::getValidatedRate(const std::string& prompt) {
    float rate;
    cout << prompt;
    while (!(cin >> rate) || rate <= 0.0f) {
        cout << "❌ Invalid input. Please enter a positive numeric value: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }
    return rate;
}

// Function: Create department
Department Department::createDepartment(int deptcode) {
    string name;
    float hourlyRate = 0.0f, overtimeRate = 0.0f;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

// Utility function to check file access
bool Department::checkFileAccess(std::ios& file) {
    if (file.fail()) {
        throw std::runtime_error("[❌ ERROR ACCESSING FILE! ]");
    }
    return true; // Return true if no error
}

// Helper function to write a department record to files
void Department::writeRecord(ofstream& deptFile, ofstream& ratesFile, const Department& dept) {
    deptFile << dept.getCode() << "\t" << dept.getName() << endl;
    ratesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
}

// Function: Add record
void Department::addRecord(const Department& dept) {
    if (dept.getCode() == 0 || dept.getName().empty() || dept.getHourlyRate() <= 0.0f || dept.getOvertimeRate() <= 0.0f) {
        cout << "\t\t\a\n [❌ Cannot add record: All fields must be non-empty and non-zero! ]\n\n";
        return;
    }

    try {
        ifstream deptNewFile(DEPT_FILE_NAME);
        checkFileAccess(deptNewFile);

        int deptCode;
        string deptName;
        bool exists = false;

        // Check for duplicate code or name
        while (deptNewFile >> deptCode) {
            deptNewFile.ignore(); // skip tab
            getline(deptNewFile, deptName);

            // Compare code or name (case-sensitive)
            if (dept.getCode() == deptCode) {
                cout << "\t\t\a\n [❌ Record with Department Code: " << dept.getCode() << " already exists!!! ]\n\n";
                exists = true;
                break;
            } else if (dept.getName() == deptName) {
                cout << "\t\t\a\n [❌ Record with Department Name: " << dept.getName() << " already exists!!! ]\n\n";
                exists = true;
                break;
            }
        }
        deptNewFile.close();

        if (exists) {
            return;
        }

        ofstream deptFile(DEPT_FILE_NAME, ios::app);
        ofstream ratesFile(RATES_FILE_NAME, ios::app);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        writeRecord(deptFile, ratesFile, dept);
        deptFile.close();
        ratesFile.close();
        cout << "[✅ Record with code: " << dept.getCode() << " added successfully... ]" << endl;

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

        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);
        checkFileAccess(tempDeptFile);
        checkFileAccess(tempRatesFile);

        bool found = false;
        vector<pair<int, string>> existingRecords; // Store existing records for duplicate checking

        while (true) {
            int deptCode, deptRateCode;
            string deptName;
            float hrRate, otRate;

            if (!(deptFile >> deptCode)) break; // End of file
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);

            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            existingRecords.emplace_back(deptCode, deptName);

            if (deptCode == updateCode && deptRateCode == updateCode) {
                found = true;

                cout << "\n+--------------------------------------------------+\n"
                     << "|           DEPARTMENT RECORD FOUND                |\n"
                     << "+--------------------------------------------------+\n"
                     << "Department Code: " << deptCode
                     << " | Department Name: " << deptName
                     << " | Hourly Rate: " << hrRate
                     << " | Overtime Rate: " << otRate << endl;

                cout << "\n+--------------------------------------------------+\n"
                     << "|       ENTER UPDATE DEPARTMENT RECORD INFORMATION |\n"
                     << "+--------------------------------------------------+\n";

                Department updatedDept = createDepartment(updateCode);

                // Check for duplicate name excluding current record
                bool duplicateFound = false;
                for (const auto& record : existingRecords) {
                    if (updatedDept.getName() == record.second && updatedDept.getCode() != record.first) {
                        cout << "\t\t\a\n [❌ Duplicate Department Name: " << updatedDept.getName() << " already exists!!! ]\n\n";
                        duplicateFound = true;
                        break;
                    }
                }

                if (duplicateFound) {
                    // Write original record back since update is not allowed
                    writeRecord(tempDeptFile, tempRatesFile, Department(deptCode, deptName, hrRate, otRate));
                } else {
                    // Write updated record
                    writeRecord(tempDeptFile, tempRatesFile, updatedDept);
                    cout << "\n[✅ Record with Department Code: " << updateCode << " has been updated ]" << endl;
                }
            } else {
                // Write existing record as is
                writeRecord(tempDeptFile, tempRatesFile, Department(deptCode, deptName, hrRate, otRate));
            }
        }

        if (!found) {
            cout << "\t\t\a\n [❌ Record with Department Code: " << updateCode << " does not exist!!! ]\n\n";
        }

        // Clean up
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        // Replace old files with updated temp files
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
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        displayHeader();
        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            if (searchCode == dept.getCode() && dept.getCode() == deptRateCode) {
                found = true;
                dept.display();
                break;
            }
        }

        if (!found) {
            cout << "\t\t\a\n [❌ Record with Department Code: " << searchCode << " does not exist!!! ]\n\n";
        }

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: View all records
void Department::viewAllRecords() {
    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;
        int recordsCounter = 0;

        displayHeader();
        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            recordsCounter++;
            dept.display();
            cout << endl;
        }

        if (recordsCounter == 0) {
            cout << "\t\t\a\n [❌ No Department records exist!!! ]\n\n";
        }

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Function: Delete record
void Department::deleteRecord(int deleteCode) {
    try {
        ifstream deptFile(DEPT_FILE_NAME);
        ifstream ratesFile(RATES_FILE_NAME);
        ofstream tempDeptFile(TEMP_DEPT_FILE_NAME);
        ofstream tempRatesFile(TEMP_RATES_FILE_NAME);

        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);
        checkFileAccess(tempDeptFile);
        checkFileAccess(tempRatesFile);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        cout << "\n [❌ Attempting to delete record with Department Code: " << deleteCode << " ]" << endl;

        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            if (deleteCode == dept.getCode() && dept.getCode() == deptRateCode) {
                found = true;
                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|           DEPARTMENT RECORD FOUND                |" << endl;
                cout << "+--------------------------------------------------+" << endl;
                dept.display();
                cout << "\n+--------------------------------------------------+" << endl;

                cout << "❗ Are you sure you want to delete this record? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    cout << "\n❌ Deleting record..." << endl;
                    // Do not write this record to temp files (effectively deleting)
                } else {
                    cout << "\n❌ Deletion cancelled. Record will be kept." << endl;
                    writeRecord(tempDeptFile, tempRatesFile, dept);
                }
            } else {
                writeRecord(tempDeptFile, tempRatesFile, dept);
            }
        }

        if (!found) {
            cout << "\t\t\a\n [❌ Record with Department Code: " << deleteCode << " does not exist!!! ]\n\n";
        } else {
            cout << "\n [✅ Record with Department Code: " << deleteCode << " has been deleted (if confirmed). ]" << endl << endl;
        }

        // Clean up
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        remove(DEPT_FILE_NAME.c_str());
        rename(TEMP_DEPT_FILE_NAME.c_str(), DEPT_FILE_NAME.c_str());
        remove(RATES_FILE_NAME.c_str());
        rename(TEMP_RATES_FILE_NAME.c_str(), RATES_FILE_NAME.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
