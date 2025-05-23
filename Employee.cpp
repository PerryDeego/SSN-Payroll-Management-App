#include "Employee.h"
#include "EmpList.h"
#include <iostream> 					                                  
#include <string> 
#include <fstream>

using namespace std;

//destructor
Employee::~Employee()
{

}

//default constructor
Employee::Employee()
{
	setId(0);
	setFirstName("fist name");
	setLastName("last name");
	setDepartmentCode(0);
	setPosition("position");
	setHoursWorked(0.0f);
}


//primary constructor
Employee::Employee(int id, string fistName, string lastName, int departmentCode, string position, float hoursWorked)
{
	setId(id);
	setFirstName(fistName);
	setLastName(lastName);
	setDepartmentCode(departmentCode);
	setPosition(position);
	setHoursWorked(hoursWorked);
}

//copy constructor
Employee::Employee(const Employee &Emp)
{
	this->id = Emp.getId();
	this->firstName = Emp.getFirstName();
	this->lastName = Emp.getLastName();
	this->departmentCode = Emp.getDepartmentCode();
	this->position = Emp.getPosition();
	this->hoursWorked = Emp.getHoursWorked();
}

//mutators
void Employee::setId(int empId)
{
	id = empId;
}

void Employee::setFirstName(string fn)
{
	firstName = fn;
}

void Employee::setLastName(string ln)
{
	lastName = ln;
}
void Employee::setDepartmentCode(int deptCode)
{
	departmentCode = deptCode;
}

void Employee::setPosition(string post)
{
	position = post;
}
void Employee::setHoursWorked(float hr)
{
	hoursWorked = hr;
}

//--------------- accessors -------------------//
int Employee::getId() const
{
	return id;
}

string Employee::getFirstName() const
{
	return firstName;
}

string Employee::getLastName() const
{
	return lastName;
}

int Employee::getDepartmentCode() const
{
	return departmentCode;
}

string Employee::getPosition() const
{
	return position;
}
float Employee::getHoursWorked() const
{
	return hoursWorked;
}

//---- to string method ----//
void Employee::display() const
{
	cout << "Employee Id: " << getId() << " | " << "First Name : " << getFirstName() << " | " << "Last Name : " << getLastName()
		<< " | " << "Department Code : " << getDepartmentCode() << " | " << "Position : " << getPosition() << " | " << "Hours Worked : " << getHoursWorked() << endl;

}


//------------------------------------ methods ---------------------------------//
Employee Employee::createEmployee(int empId)
{
	string firstName, lastName, position;
	int departmentCode;
	float hoursWorked;
	


	cout << "Enter Employee first name : ";
	cin >> firstName;
	cout << endl;

	cout << "Enter Employee last name : ";
	cin >> lastName;
	cout << endl;

	cout << "Enter Employee department code : ";
	cin >> departmentCode;
	cout << endl;

	cout << "Enter Employee position : ";
	cin.ignore();
	getline(cin, position);
	cout << endl;

	cout << "Enter Employee hours worked : ";
	cin >> hoursWorked;

	Employee emp(empId, firstName, lastName, departmentCode, position, hoursWorked);

	return emp;

}


//------------------------------------ file methods ---------------------------------//
void Employee::addRecord(Employee emp)
{
	string empFileName = "employee.txt";
	string empPayrollFileName = "employeepayroll.txt";

	try {
		// First, check if the employee ID already exists
		ifstream empFileCheck(empFileName, ios::in);
		int id, deptCode;
		string firstName, lastName, position;
		bool exists = false;

		while (empFileCheck >> id >> firstName >> lastName >> deptCode >> position) {
			if (id == emp.getId()) {
				exists = true;
				break;
			}
		}
		empFileCheck.close();

		if (exists) {
			cout << endl << "Record with Employee Id: " << emp.getId() << " already exists. Cannot add duplicate." << endl << endl;
			return;
		}

		ofstream empFile(empFileName, ios::app);
		ofstream empPayrollFile(empPayrollFileName, ios::app);

		if (empFile.fail() || empPayrollFile.fail())
		{
			throw runtime_error("ERROR ACCESSING FILE!");
		} //end if

		empFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t" << emp.getPosition() << endl;
		empPayrollFile << emp.getId() << "\t" << emp.getDepartmentCode() << "\t" << emp.getHoursWorked() << endl;
		
		cout << endl << endl << "Record with code : " << emp.getId() << " added successfully..." << endl << endl;

		empFile.close();
		empPayrollFile.close();

	} //end try
	catch (exception &i)
	{
		cerr << i.what();
	} //end catch

}


void Employee::updateRecord(int updateId)
{
	string empFileName = "employee.txt";
	string tempEmpFileName = "tempemp.txt";
	string empPayrollFileName = "employeepayroll.txt";
	string tempEmpPayrollFileName = "tempemppayroll.txt";

	try {
		bool found = false;
		ifstream empFile(empFileName, ios::in);
		ofstream empTempFile(tempEmpFileName, ios::app);
		ifstream empPayrollFile(empPayrollFileName, ios::in);
		ofstream tempEmpPayrollFile(tempEmpPayrollFileName, ios::app);
		
		Employee updateEmp;
		Employee emp;
		int id, rId, rdeptCode, deptCode;
		string fn, ln, post;
		float hrs;

		if (empFile.fail() || empPayrollFile.fail() || empTempFile.fail() || tempEmpPayrollFile.fail())
		{
			throw runtime_error("ERROR ACCESSING FILE!");
		} //end if

		while (true)
		{
			empFile >> id >> fn >> ln >> deptCode >> post;
			empPayrollFile >> rId >> rdeptCode >> hrs;

			emp.setId(id);
			emp.setFirstName(fn);
			emp.setLastName(ln);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(post);
			emp.setHoursWorked(hrs);

			if (updateId == emp.getId() && updateId == rId && deptCode == rdeptCode)
			{
				system("cls");
				found = true; //case where record is found

				cout << "\t~~~~~~~~~~~~~ EMPLOYEE RECORD FOUND ~~~~~~~~~~~~~" << endl << endl;
				cout << "Employee Id : " << emp.getId() << " | " << "First Name : " << emp.getFirstName() << " | " << "Last Name : " << emp.getLastName() << " | " << "Department Code : " << emp.getDepartmentCode() << " | " << "Position : " << emp.getPosition() << " | " << "Hours Worked : " << emp.getHoursWorked() << endl << endl;
				system("pause");
				system("cls");

				cout << "\t~~~~~~~~~~~~~ ENTER UPDATE EMPLOYEE RECORD INFORMATION HERE ~~~~~~~~~~~~~" << endl << endl;

				updateEmp = createEmployee(updateId);
				empTempFile << updateEmp.getId() << "\t" << updateEmp.getFirstName() << "\t" << updateEmp.getLastName() << "\t" << updateEmp.getDepartmentCode() << "\t" << updateEmp.getPosition() << endl;
				tempEmpPayrollFile << updateEmp.getId() << "\t" <<  updateEmp.getDepartmentCode() << "\t" << updateEmp.getHoursWorked() << endl;

				cout << "\n\n\t\t\a\nRecord with Employee Id: " << updateId << " has been updated" << endl << endl;
				break;
			} //end if
			else
			{
				empTempFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t" << emp.getPosition() << endl;
				tempEmpPayrollFile << emp.getId() << "\t" <<  emp.getHoursWorked() << endl;

			} //end else

			if (empFile.eof() || empPayrollFile.eof())
				break;

		} //end while

		if (found == false)
		{
			cout << "\t\t\a\nRecord with Employee Id : " << updateId << " does not exist!!!\n\n";
		} //end if

		empFile.close();
		empTempFile.close();
		empPayrollFile.close();
		tempEmpPayrollFile.close();

		remove("employee.txt");
		rename("tempemp.txt", "employee.txt");
		remove("employeepayroll.txt");
		rename("tempemppayroll.txt", "employeepayroll.txt");


	} //end try
	catch (exception &i)
	{
		cerr << i.what();
	} //end catch
}


void Employee::viewRecord(int searchId)
{
	string empFileName = "employee.txt";
	string empPayrollFileName = "employeepayroll.txt";

	try {
		ifstream empFile(empFileName, ios::in);
		ifstream empPayrollFile(empPayrollFileName, ios::in);

		bool found = false;
		Employee emp;
		int id, payrollId, deptCode;
		string fn, ln, post;
		float hrs;

		if (empFile.fail() || empPayrollFile.fail())
		{
		throw runtime_error("ERROR ACCESSING FILE!");
		} //end if

		while (!empFile.eof() || !empPayrollFile.eof())
		{
			empFile >> id >> fn >> ln >> deptCode >> post;
			empPayrollFile >> payrollId >> deptCode >> hrs;

			emp.setId(id);
			emp.setFirstName(fn);
			emp.setLastName(ln);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(post);
			emp.setHoursWorked(hrs);

			if (searchId == emp.getId() && emp.getId() == payrollId)
			{
				found = true;
				emp.display();
				break;
			} //end if

		} //end while

		if (found == false)
		{
			cout << "\t\t\a\nRecord with Employee Id : " << searchId << " does not exist!!!\n\n";
		} //end if

		empFile.close();
		empPayrollFile.close();

	} //end try
	catch (exception &i)
	{
		cerr << i.what();
	} //end catch

}


void Employee::viewAllRecord()
{
	string empFileName = "employee.txt";
	string empPayrollFileName = "employeepayroll.txt";

	try {
		ifstream empFile(empFileName, ios::in);
		ifstream empPayrollFile(empPayrollFileName, ios::in);

		int recordCount = 0;
		Employee emp;
		int id, payrollId, deptCode;
		string fn, ln, post;
		float hrs;

		if (empFile.fail() || empPayrollFile.fail())
		{
		throw runtime_error("ERROR ACCESSING FILE!");
		} //end if

		while (true)
		{
			empFile >> id >> fn >> ln >> deptCode >> post;
			empPayrollFile >> payrollId >> deptCode >> hrs;

			emp.setId(id);
			emp.setFirstName(fn);
			emp.setLastName(ln);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(post);
			emp.setHoursWorked(hrs);

			if (empFile.eof() && empPayrollFile.eof()) //exit reading from file when end of file is reached
			{
				break;
			} //end if

			++recordCount;
			emp.display();
			cout << endl;

		} //end while

		if (recordCount == 0)
		{
			cout << "\t\t\a\nNo record(s) Employee exist!!!\n\n";
		} //end if

		empFile.close();
		empPayrollFile.close();

	} //end try
	catch (exception &i)
	{
		cerr << i.what();
	} //end catch

}


void Employee::deleteRecord(int deleteId)
{
	string empFileName = "employee.txt";
	string tempEmpFileName = "tempemp.txt";
	string empPayrollFileName = "employeepayroll.txt";
	string tempEmpPayrollFileName = "tempemppayroll.txt";

	try {
		bool found = false;
		ifstream empFile(empFileName, ios::in);
		ofstream empTempFile(tempEmpFileName, ios::app);
		ifstream empPayrollFile(empPayrollFileName, ios::in);
		ofstream tempEmpPayrollFile(tempEmpPayrollFileName, ios::app);

		Employee emp;
		int id, rId, rdeptCode, deptCode;
		string fn, ln, post;
		float hrs;

		if (empFile.fail() || empPayrollFile.fail() || empTempFile.fail() || tempEmpPayrollFile.fail())
		{
			throw runtime_error("ERROR ACCESSING FILE!");
		} //end if

		while (!empFile.eof() || !empPayrollFile.eof())
		{
			empFile >> id >> fn >> ln >> deptCode >> post;
			empPayrollFile >> rId >> rdeptCode >> hrs;

			emp.setId(id);
			emp.setFirstName(fn);
			emp.setLastName(ln);
			emp.setDepartmentCode(deptCode);
			emp.setPosition(post);
			emp.setHoursWorked(hrs);

			if (deleteId == emp.getId() && emp.getId() == rId)
			{
				system("cls");
				found = true; //case where record is found

				cout << "\t~~~~~~~~~~~~~ EMPLOYEE RECORD FOUND ~~~~~~~~~~~~~" << endl << endl;
				cout << "Employee Id : " << emp.getId() << " | " << "First Name : " << emp.getFirstName() << " | " << "Last Name : " << emp.getLastName() << " | " << "Department Code : " << emp.getDepartmentCode() << " | " << "Position : " << emp.getPosition() << " | " << "Hours Worked : " << emp.getHoursWorked() << endl << endl;
				system("pause");
				system("cls");

				continue; //skip writing record to temporay file

				cout << "\n\n\t\t\a\nRecord with Employee Id: " << deleteId << " has been deleted" << endl << endl;
				break;
			} //end if
			else
			{
				empTempFile << emp.getId() << "\t" << emp.getFirstName() << "\t" << emp.getLastName() << "\t" << emp.getDepartmentCode() << "\t" << emp.getPosition() << endl;
				tempEmpPayrollFile << emp.getId() << "\t" << emp.getHoursWorked() << endl;

			} //end else

		} //end while

		if (found == false)
		{
			cout << "\t\t\a\nRecord with Employee Id : " << deleteId << " does not exist!!!\n\n";
		} //end if

		empFile.close();
		empTempFile.close();
		empPayrollFile.close();
		tempEmpPayrollFile.close();

		remove("employee.txt");
		rename("tempemp.txt", "employee.txt");
		remove("employeepayroll.txt");
		rename("tempemppayroll.txt", "employeepayroll.txt");

	} //end try
	catch (exception &i)
	{
		cerr << i.what();
	} //end catch
}

