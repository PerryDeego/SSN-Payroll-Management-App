#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Department {
private:
    int code;
    string name;
    float hourlyRate;
    float overtimeRate;

public:
   
    ~Department();

    Department();

    Department(int code, const string& name, float hourlyRate, float overtimeRate);

    Department(const Department &dept);

    // Mutators
    void setCode(int code);
    void setName(const string& name);
    void setHourlyRate(float hourlyRate);
    void setOvertimeRate(float overtimeRate);

    // Accessors
    int getCode() const;
    string getName() const;
    float getHourlyRate() const;
    float getOvertimeRate() const;

    // Methods
    void displayHeader() const;
    void display() const;
    float getValidatedRate(const string& prompt);
    Department createDepartment(int deptCode);
    bool checkFileAccess(ifstream& file, const string& filename);
    bool checkFileAccess(ofstream& file, const string& filename);
    void writeRecord(ofstream& deptFile, ofstream& ratesFile, const Department& dept);
    void addRecord(const Department& dept);
    void updateRecord(int updateCode);
    void viewRecord(int searchCode);
    void viewAllRecordss();
    void deleteRecord(int deleteCode);
};

#endif // DEPARTMENT_H
