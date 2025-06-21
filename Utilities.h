#include "Headers.h" // Include all necessary headers

//------------- constants -----------------||
const string ratesFileName = "rates.txt";
const string empFileName = "employee.txt";
const string empPayrollFileName = "employee_payroll.txt";
const string payrollFileName = "monthly_payroll.txt";
const string tempPayFileName = "monthly_payroll_temp.txt";

//------------- method prototypes -------||
void mainConsole();
void departmentConsole();
void employeeConsole();
void sortEmployeeConsole(const string &empFileName, const string &empPayrollFileName);
void payrollConsole();
void payrollProcessing(const string& ratesFile, const string& empFile, const string& empPayrollFile, const string& payrollFile);
void viewSinglePayroll(int searchId, const string &payrollFileName);
void sortPayrollConsole(const string &payrollFileName);

//---------------------------------------- methods ---------------------------------------||

void shutdownCounter(int seconds) {
    for (int i = seconds; i >= 0; i--) {
        cout << "\r\t\t[ 🖐️ SHUTTING DOWN SYSTEM... " << setw(2) << i << "  ] " << flush;
          usleep(1000000);
    }
}

// Function: Clear screen 
void clearScreen() {
    system("clear");  
}

// Function: Press Enter to continue
void pressEnterContinue() {
    cout << "\n\n\n\t▶️ Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter key
    cin.get(); // Consume the Enter key
}

// Function: Print current date and time
void printDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Format: YYYY-MM-DD HH:MM:SS
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║   📅 Date: " 
         << 1900 + ltm->tm_year << "-"
         << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
         << setw(2) << setfill('0') << ltm->tm_mday
         << "   ⏰ Time: "
         << setw(2) << setfill('0') << ltm->tm_hour << ":"
         << setw(2) << setfill('0') << ltm->tm_min << ":"
         << setw(2) << setfill('0') << ltm->tm_sec
         << "                     ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
}

// Function: Main menu for the application
int mainMenu()
{
    clearScreen();
    int choice;
    cout << "\n\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                  SMART SOLUTION NOW (SSN)                    ║\n";
    cout << "\t║                        PAYROLL SYSTEM                          ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime();
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ❌  CLOSE PROGRAM                                      ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  🏢  DEPARTMENT RECORDS                                ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  👤  EMPLOYEE RECORDS                                  ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  💰  PAYROLL RECORDS                                   ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your option: ";
    cin >> choice;
    cout << endl;

    return choice;
}

// Function: Department menu
int departmentMenu()
{
    clearScreen();
    int choice;
    cout << "\n\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                  🏢  DEPARTMENT MAIN MENU                   ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime();
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ⬅️  RETURN TO MAIN                                  ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  ➕  ADD DEPARTMENT                                  ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  ✏️  UPDATE DEPARTMENT                               ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  🔍  VIEW DEPARTMENT                                 ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [4]  📋  VIEW ALL DEPARTMENTS                            ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [5]  🗑️  DELETE DEPARTMENT                               ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your option: ";
    cin >> choice;
    cout << endl;

    return choice;
}

// Function: Employee menu
int employeeMenu()
{
    clearScreen();
    int choice;
    cout << "\n\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                  👤  EMPLOYEE MAIN MENU                     ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime();
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ⬅️  RETURN TO MAIN                                  ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  ➕  ADD EMPLOYEE                                    ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  ✏️  UPDATE EMPLOYEE                                 ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  🔍  VIEW EMPLOYEE                                   ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [4]  📊  VIEW SORTED EMPLOYEE                            ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [5]  🗑️  DELETE EMPLOYEE                                 ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your option: ";
    cin >> choice;
    cout << endl;
    
    return choice;
}

// Function: Payroll logo and header
void payrollLogo()
{
    cout << "\n";
    cout << "\t" << " ╔════════════╦══════════════════════╦══════════════════════╦════════════════╦════════════════════════╦════════════╦════════════╦════════════════╦═══════════════╗" << endl;
    cout << "\t" << " ║    ID      ║     FIRST NAME       ║      LAST NAME       ║  DEPT CODE     ║       POSITION         ║  HOURS     ║ BASIC PAY  ║ OVERTIME PAY   ║  GROSS PAY    ║" << endl;
    cout << "\t" << " ╠════════════╬══════════════════════╬══════════════════════╬════════════════╬════════════════════════╬════════════╬════════════╬════════════════╬═══════════════╣" << endl;
}

// Function to display the header for sorting
void displayHeader(const string &title)
{
    clearScreen();
    cout << "\n\t╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM                    ║\n";
    cout << "\t║                          " << title << "                       ║\n";
    cout << "\t╠══════════════════════════════════════════════════════════════════════════════╣\n";
}

// Function: Payroll menu
int payrollMenu()
{
    clearScreen();
    int choice;

    cout << "\n\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                  💰  PAYROLL MAIN MENU                      ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime();
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ⬅️  RETURN TO MAIN                                   ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  ⚙️  PROCESS PAYROLL                                  ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  📄  VIEW PAYROLL                                     ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  📊  VIEW SORTED PAYROLL                              ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [4]  🗑️  DELETE PAYROLL RECORD                            ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your option: ";
    cin >> choice;
    cout << endl;

    return choice;
}

// Function: Sorted Employee menu
int sortedEmployeeMenu()
{
    clearScreen();
    int choice;

    cout << "\n\n\t╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "\t║                SMART SOLUTION NOW (SSN) PAYROLL SYSTEM - SORTED EMPLOYEE RECORDS                     ║\n";
    cout << "\t╠════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "\t║  This option allows you to view all employee records sorted by various criteria. Please select an option:  ║\n";
    cout << "\t╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

    cout << "\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║              📊  SORT EMPLOYEE RECORD MENU                  ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime(); // Print current date and time
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ⬅️  RETURN TO EMPLOYEE MENU                          ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  🆔  SORT BY ID                                       ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  🔤  SORT BY LAST NAME                                ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  🏢  SORT BY DEPARTMENT                               ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [4]  💼  SORT BY POSITION                                 ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [5]  ⏱️  SORT BY HOURS WORKED                             ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your option: ";
    cin >> choice;
    cout << endl;

    return choice;
}

// Function: Sorted Payroll menu
int sortedPayrollMenu()
{
    clearScreen();
    int choice;

    cout << "\n\n\t╔════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "\t║           SMART SOLUTION NOW (SSN) PAYROLL SYSTEM - SORTED PAYROLL RECORDS                            ║\n";
    cout << "\t╠════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "\t║  This option allows you to view all employee payroll records sorted by various criteria.                  ║\n";
    cout << "\t║  Please select an option:                                                                                ║\n";
    cout << "\t╚════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

    cout << "\n";
    cout << "\t╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "\t║              📊  PAYROLL SORT MAIN MENU                     ║\n";
    cout << "\t╠═══════════════════════════════════════════════════════════════╣\n";
    printDateTime();
    cout << "\t║                                                             ║\n";
    cout << "\t║   [0]  ⬅️  RETURN TO MAIN                                   ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [1]  🆔  SORT BY ID                                       ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [2]  🔤  SORT BY LAST NAME                                ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [3]  🏢  SORT BY DEPARTMENT CODE                          ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t║   [4]  💼  SORT BY POSITION                                 ║\n";
    cout << "\t║                                                             ║\n";
    cout << "\t╚═══════════════════════════════════════════════════════════════╝\n";
    cout << "\n\tEnter your selection: ";
    cin >> choice;
    cout << endl;

    return choice;
}

// Function: Create and display payroll record
void createAndDisplayPayroll(const int id, const string& firstName, const string& lastName, const int deptCode,
                             const string& position, float hrs, float regularPay, float overtimePay, float grossPay) {
    Payroll payroll;
    payroll.setId(id);
    payroll.setFirstName(firstName);
    payroll.setLastName(lastName);
    payroll.setDepartmentCode(deptCode);
    payroll.setPosition(position);
    payroll.setHoursWorked(hrs);
    payroll.setBasicPay(regularPay);
    payroll.setOvertimePay(overtimePay);
    payroll.setGrossPay(grossPay);
    payroll.display();
}

// Function to handle input with validation
int getValidatedInput(const string &prompt)
{
    int id;
    while (true)
    {
        cout << prompt;
        cin >> id;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\t[ ℹ️ Invalid input. Please enter a valid Employee ID. ]\n";
            continue;
        }
        return id;
    }
}

// Utility function to check file access
bool checkFileAccess(ios& file) {
    if (file.fail()) {
        throw runtime_error("[❌ ERROR ACCESSING FILE! ]");
    }
    return true; 
}

//---------------------------- Payroll Calculations ---------------------------------||
float calculateRegularPay(float hourlyRate, float hoursWorked)
{
    return hourlyRate * min(hoursWorked, 40.0f);
}

float calculateOvertimePay(float hoursWorked, float overtimeRate)
{
    return max(0.0f, hoursWorked - 40.0f) * overtimeRate;
}

float calculateGrossPay(float regularPay, float overtimePay)
{
    return regularPay + overtimePay;
}
