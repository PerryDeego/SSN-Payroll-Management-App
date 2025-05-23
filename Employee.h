//........Preprocessor Directives.......||
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream> 					                                                                          			
//......................................||

class Employee {
private:
	int id;
	std:: string firstName;
	std:: string lastName;
	int departmentCode;
	std:: string position;
	float hoursWorked;

public:
	//destructor
	~Employee();

	//default constructor
	Employee();


	//primary constructor
	Employee(int, std::string, std::string, int, std::string, float);

	//copy constructor
	Employee(const Employee &Emp);

	//mutators
	void setId(int);
	void setFirstName(std::string);
	void setLastName(std::string);
	void setDepartmentCode(int);
	void setPosition(std::string);
	void setHoursWorked(float);

	//accessors
	int getId() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	int getDepartmentCode() const;
	std::string getPosition() const;
	float getHoursWorked() const;

	//--------- methods -----------//
	void display() const;

	Employee createEmployee(int);
	void addRecord(Employee emp);
	void updateRecord(int);
	void viewRecord(int);
	void viewAllRecord();
	void deleteRecord(int);

};
#endif


