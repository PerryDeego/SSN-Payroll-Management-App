#include "Department.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

// Destructor
Department::~Department() {}

// Default constructor
Department::Department() : code(0), name("department name"), hourlyRate(0.0f), overtimeRate(0.0f) {}

// Primary constructor
Department::Department(int code, const string& name, float hourlyRate, float overtimeRate)
: code(code), name(name), hourlyRate(hourlyRate), overtimeRate(overtimeRate) {
    setCode(code);
    setName(name);
    setHourlyRate(hourlyRate);
    setOvertimeRate(overtimeRate);
}

// Copy constructor
Department::Department(const Department &Dept)
    : code(Dept.code), name(Dept.name), hourlyRate(Dept.hourlyRate), overtimeRate(Dept.overtimeRate) {}

// Mutators
void Department::setCode(int cd) { code = cd; }
void Department::setName(const string& nm) { name = nm; }
void Department::setHourlyRate(float hrRate) { hourlyRate = hrRate; }
void Department::setOvertimeRate(float otRate) { overtimeRate = otRate; }

// Accessors
int Department::getCode() const { return code; }
string Department::getName() const { return name; }
float Department::getHourlyRate() const { return hourlyRate; }
float Department::getOvertimeRate() const { return overtimeRate; }

// Display method
void Department::display() const {
    cout << "+-------------------+--------------------------+----------------+-------------------+" << endl;
    cout << "| Department Code   | Department Name          | Hourly Rate    | Overtime Rate     |" << endl;
    cout << "+-------------------+--------------------------+----------------+-------------------+" << endl;
    cout << "| " << setw(17) << left << getCode()
         << "| " << setw(26) << left << getName().substr(0, 24)
         << "| $" << setw(14) << right << fixed << setprecision(2) << getHourlyRate()
         << " | $" << setw(16) << right << fixed << setprecision(2) << getOvertimeRate()
         << " |" << endl;
    cout << "+-------------------+--------------------------+----------------+-------------------+" << endl;
}

// Create department
Department Department::createDepartment(int deptcode) {
    string name;
    float hourlyRate, overtimeRate;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Department name: ";
    getline(cin, name);
    cout << "Enter Department hourly rate: ";
    cin >> hourlyRate;
    cout << "Enter Department overtime rate: ";
    cin >> overtimeRate;

    return Department(deptcode, name, hourlyRate, overtimeRate);
}

// Utility function to check file access
bool Department::checkFileAccess(std::ios& file) {
    if (file.fail()) {
        throw std::runtime_error("ERROR ACCESSING FILE!");
    }
    return true; // Return true if no error
}



// Add record
void Department::addRecord(const Department& dept) {
    if (dept.getCode() == 0 || dept.getName().empty() || dept.getHourlyRate() == 0.0f || dept.getOvertimeRate() == 0.0f) {
        cout << "\t\t\a\nCannot add record: All fields must be non-empty and non-zero!\n\n";
        return;
    }

    string deptFileName = "department.txt";
    string ratesFileName = "rates.txt";

    try {
        ifstream deptFileCheck(deptFileName);
        checkFileAccess(deptFileCheck);

        int deptCode;
        string detname;
        bool exists = false;

        while (deptFileCheck >> deptCode) {
            deptFileCheck.ignore(); // skip tab
            getline(deptFileCheck, detname);
            if (dept.getCode() == deptCode) {
                exists = true;
                break;
            }
        }
        deptFileCheck.close();

        if (exists) {
            cout << "\t\t\a\nRecord with Department Code: " << dept.getCode() << " already exists!!!\n\n";
            return;
        }

        ofstream deptFile(deptFileName, ios::app);
        ofstream ratesFile(ratesFileName, ios::app);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        deptFile << dept.getCode() << "\t" << dept.getName() << endl;
        ratesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
        cout << "Record with code: " << dept.getCode() << " added successfully..." << endl;

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Update record
void Department::updateRecord(int updateCode) {
    string deptFileName = "department.txt";
    string tempDeptFileName = "tempdept.txt";
    string ratesFileName = "rates.txt";
    string tempRatesFileName = "temprates.txt";

    try {
        ifstream deptFile(deptFileName);
        ifstream ratesFile(ratesFileName);
        ofstream tempDeptFile(tempDeptFileName);
        ofstream tempRatesFile(tempRatesFileName);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);
        checkFileAccess(tempDeptFile);
        checkFileAccess(tempRatesFile);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, deptName);
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(deptName);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            if (updateCode == dept.getCode() && dept.getCode() == deptRateCode) {
                found = true;
                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|           DEPARTMENT RECORD FOUND                |" << endl;
                cout << "+--------------------------------------------------+" << endl;
                cout << "Department Code: " << dept.getCode() << " | Department Name: " << dept.getName() 
                     << " | Hourly Rate: " << dept.getHourlyRate() << " | Overtime Rate: " << dept.getOvertimeRate() << endl;

                cout << "\n+--------------------------------------------------+" << endl;
                cout << "|       ENTER UPDATE DEPARTMENT RECORD INFORMATION |" << endl;
                cout << "+--------------------------------------------------+" << endl;

                Department updateDept = createDepartment(updateCode);
                tempDeptFile << updateDept.getCode() << "\t" << updateDept.getName() << endl;
                tempRatesFile << updateDept.getCode() << "\t" << updateDept.getHourlyRate() << "\t" << updateDept.getOvertimeRate() << endl;
                cout << "\nRecord with Department Code: " << updateCode << " has been updated" << endl;
            } else {
                tempDeptFile << dept.getCode() << "\t" << dept.getName() << endl;
                tempRatesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
            }
        }

        if (!found) {
            cout << "\t\t\a\nRecord with Department Code: " << updateCode << " does not exist!!!\n\n";
        }

        // Clean up
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        remove(deptFileName.c_str());
        rename(tempDeptFileName.c_str(), deptFileName.c_str());
        remove(ratesFileName.c_str());
        rename(tempRatesFileName.c_str(), ratesFileName.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// View record
void Department::viewRecord(int searchCode) {
    string deptFileName = "department.txt";
    string ratesFileName = "rates.txt";

    try {
        ifstream deptFile(deptFileName);
        ifstream ratesFile(ratesFileName);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string nm;
        float hrRate, otRate;

        while (deptFile >> deptCode) {
            deptFile.ignore(); // skip tab
            getline(deptFile, nm);
            if (!(ratesFile >> deptRateCode >> hrRate >> otRate)) break;

            dept.setCode(deptCode);
            dept.setName(nm);
            dept.setHourlyRate(hrRate);
            dept.setOvertimeRate(otRate);

            if (searchCode == dept.getCode() && dept.getCode() == deptRateCode) {
                found = true;
                dept.display();
                break;
            }
        }

        if (!found) {
            cout << "\t\t\a\nRecord with Department Code: " << searchCode << " does not exist!!!\n\n";
        }

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// View all records
void Department::viewAllRecords() {
    string deptFileName = "department.txt";
    string ratesFileName = "rates.txt";

    try {
        ifstream deptFile(deptFileName);
        ifstream ratesFile(ratesFileName);
        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);

        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;
        int recordsCounter = 0;

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
            cout << "\t\t\a\nNo Department records exist!!!\n\n";
        }

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}

// Delete record
void Department::deleteRecord(int deleteCode) {
    string deptFileName = "department.txt";
    string tempDeptFileName = "tempdept.txt";
    string ratesFileName = "rates.txt";
    string tempRatesFileName = "temprates.txt";

    try {
        ifstream deptFile(deptFileName);
        ifstream ratesFile(ratesFileName);
        ofstream tempDeptFile(tempDeptFileName);
        ofstream tempRatesFile(tempRatesFileName);

        checkFileAccess(deptFile);
        checkFileAccess(ratesFile);
        checkFileAccess(tempDeptFile);
        checkFileAccess(tempRatesFile);

        bool found = false;
        Department dept;
        int deptCode, deptRateCode;
        string deptName;
        float hrRate, otRate;

        cout << "\nAttempting to delete record with Department Code: " << deleteCode << endl;

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
                cout << "Department Code: " << dept.getCode() << " | "
                     << "Department Name: " << dept.getName() << " | "
                     << "Hourly Rate: " << dept.getHourlyRate() << " | "
                     << "Overtime Rate: " << dept.getOvertimeRate() << endl;

                cout << "Are you sure you want to delete this record? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    cout << "\nDeleting record..." << endl;
                    // Do not write this record to temp files (effectively deleting)
                } else {
                    cout << "\nDeletion cancelled. Record will be kept." << endl;
                    tempDeptFile << dept.getCode() << "\t" << dept.getName() << endl;
                    tempRatesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
                }
            } else {
                tempDeptFile << dept.getCode() << "\t" << dept.getName() << endl;
                tempRatesFile << dept.getCode() << "\t" << dept.getHourlyRate() << "\t" << dept.getOvertimeRate() << endl;
            }
        }

        if (!found) {
            cout << "\t\t\a\nRecord with Department Code: " << deleteCode << " does not exist!!!\n\n";
        } else {
            cout << "\nRecord with Department Code: " << deleteCode << " has been deleted (if confirmed)." << endl << endl;
        }

        // Clean up
        deptFile.close();
        ratesFile.close();
        tempDeptFile.close();
        tempRatesFile.close();

        remove(deptFileName.c_str());
        rename(tempDeptFileName.c_str(), deptFileName.c_str());
        remove(ratesFileName.c_str());
        rename(tempRatesFileName.c_str(), ratesFileName.c_str());

    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}