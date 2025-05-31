#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <fstream>
#include <string>

class Department {
private:
    int code;
    std::string name;
    float hourlyRate;
    float overtimeRate;

public:
    // Destructor
    ~Department();

    // Default constructor
    Department();

    // Primary constructor
    Department(int code, const std::string& name, float hourlyRate, float overtimeRate);

    // Copy constructor
    Department(const Department &dept);

    // Mutators
    void setCode(int code);
    void setName(const std::string& name);
    void setHourlyRate(float hourlyRate);
    void setOvertimeRate(float overtimeRate);

    // Accessors
    int getCode() const;
    std::string getName() const;
    float getHourlyRate() const;
    float getOvertimeRate() const;

    // Methods
    void displayHeader() const;
    void display() const;
    float getValidatedRate(const std::string& prompt);
    Department createDepartment(int deptCode);
	bool checkFileAccess(std::ios& file);
    void writeRecord(std::ofstream& deptFile, std::ofstream& ratesFile, const Department& dept);
    void addRecord(const Department& dept);
    void updateRecord(int updateCode);
    void viewRecord(int searchCode);
    void viewAllRecords();
    void deleteRecord(int deleteCode);
};

#endif // DEPARTMENT_H
