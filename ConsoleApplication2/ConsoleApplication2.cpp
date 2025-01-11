#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

// Function prototypes
void displayLoginMenu();
void studentMenu();
void teacherMenu();
void librarianMenu();
void principalMenu();
void deputyPrincipalMenu();
void accountantMenu();
void menu();
void addPerson();
void deletePerson();
void viewTable();
// Function declarations

void issue_book();
void return_book();
void search_book();
void add_book();

void viewTimeTable();
void manageGrades();
void manageAttendance();

// Function declarations for studentMenu() and related functionalities

void viewReport();


// Function declarations for accountantMenu() and related functionalities

void viewAccounts();
void updateAccounts();
void generateReport();

// Add login functions for other roles as needed


//viewing all tables

       
void viewPersonTable();
         
void viewTeacherTable();

void viewStudentTable();
      
void viewClassTable();
     
void viewSubjectTable();
        
void viewTimetableTable();
 
void viewBookTable();
  
void viewAttendanceTable();
 //------classes

class Person {
private:
    int id;
    string name;
    string phoneNumber;
    string emailAddress;
    string dateOfBirth;
    string address;
    string password;
    string roll;
public:
    void search();
    void displayAll();
    void add();
    void dele();
    void login(int);
};


void Person::login(int choice) {
    int inputID;
    string inputPassword;
    string roll; // Declare roll here
    cout << "Enter ID: ";
    cin >> inputID;
    cout << "Enter Password: ";
    cin >> inputPassword;


    switch (choice) {
    case 1:
        roll = "S"; // Student
        break;
    case 2:
        roll = "T"; // Teacher
        break;
    case 3:
        roll = "L"; // Librarian
        break;
    case 4:
        roll = "P"; // Principal
        break;
    case 5:
        roll = "D"; // Deputy Principal
        break;
    case 6:
        roll = "A"; // Accountant
        break;
    default:
        cerr << "Invalid choice. Please try again." << endl;
        return;
    }

    try {
        // Establish connection to the database
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        // Create a non-transactional object
        pqxx::nontransaction N(C);

        // Prepare and execute SQL query to check credentials
        string sql = "SELECT ID, Name, roll FROM Person WHERE ID = " + N.quote(to_string(inputID)) + " AND password = " + N.quote(inputPassword) + " AND roll = " + N.quote(roll) + ";";
        pqxx::result R(N.exec(sql));

        if (R.size() == 1) {
            // Successfully authenticated
            id = R[0][0].as<int>();
            name = R[0][1].as<string>();
            roll = R[0][2].as<string>();
            cout << "Welcome, " << name << " (" << roll << ")!" << endl;


          
        }
        else {
            // Invalid credentials
            cout << "Invalid ID or password. Please try again." << endl;
            login(choice);
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}

class Teacher : public Person {
private:
    string teacherID;
    string performance;
    int numberOfSubjects;
public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class Class {
private:
    string classID;
    string classTeacherID;
    int numberOfStudents;

public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class Student : public Person {
private:
    string studentNumber;
    float averageMark;
    string classID;

public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class Staff : public Person {
private:
    string staffID;
    double salary;
    int yearOfHire;

public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class Librarian : public Person {
private:
    string librarianID;
    string userName;
    string lpassword;

public:
    void search();
    void displayAll();
    void add();
    void libdele();
};

class Accountant : public Person {
private:
    string accountantID;
    string userName;
    string apassword;
public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class SupportStaff : public Person {
private:
    string supportStaffID;
    string role;

public:
    void search();
    void displayAll();
    void add();
    void dele();
};

class Management : public Person {
private:
    string position;
    string deputyPosition;

public:
    void search();
    void displayAll();
    void add();
    void dele();
};
class Book {
public:
    static void issueBook(int bookID, int personID);
    static void returnBook(int bookID);
    static void searchBook(const string& title);
    static void addBook(const string& shelf_no, const string& title);
};

int main() {
    displayLoginMenu();
    return 0;
}

void displayLoginMenu() {
    int choice;
    bool invalidChoice = false;

    do {
        if (invalidChoice) {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << "Welcome to the School Management System!" << endl;
        cout << "Please select your role:" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Librarian" << endl;
        cout << "4. Principal" << endl;
        cout << "5. Deputy Principal" << endl;
        cout << "6. Accountant" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        Person p1;
        p1.login(choice);
        switch (choice) {
        case 1:
            studentMenu();
            break;
        case 2:
            teacherMenu();
            break;
        case 3:
            librarianMenu();
            break;
        case 4:
            principalMenu();
            break;
        case 5:
            deputyPrincipalMenu();
            break;
        case 6:
            accountantMenu();
            break;
        default:
            invalidChoice = true;
            break;
        }
    } while (choice < 1 || choice > 6); // Adjust condition based on options
}

//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
// Define other menu functions like studentMenu(), teacherMenu(), etc.

// Define other menu functions

void studentMenu() {
    system("cls"); // Clear the console
    cout << "Student Menu" << endl;
    cout << "1. View Grades" << endl;
    cout << "2. View Timetable" << endl;
    cout << "3. View Attendance" << endl;
    cout << "4. Logout" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewReport();
        break;
    case 2:
        viewTimetableTable();
        break;
    case 3:
        viewAttendanceTable();
        break;
    case 4:
        cout << "Logging out..." << endl;
        displayLoginMenu();
        return; // Return to previous menu
    default:
        cout << "Invalid choice. Please try again." << endl;
        studentMenu(); // Show menu again
        break;
    }
}

//-------------------------------------------------------------------------------------------------
void viewReport() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        std::string studentID, password;
        std::cout << "Enter your Student ID: ";
        std::cin >> studentID;
        std::cout << "Enter your password: ";
        std::cin >> password;

        // Validate student credentials
        pqxx::nontransaction N(C);
        std::string sql = "SELECT * FROM Student WHERE StudentNumber = '" + studentID + "' AND Password = '" + password + "'";
        pqxx::result R(N.exec(sql));

        if (R.empty()) {
            std::cout << "Invalid Student ID or Password." << std::endl;
            return;
        }

        // Student found, display their report
        std::cout << "Report for Student ID: " << studentID << std::endl;
        sql = "SELECT * FROM Student WHERE StudentNumber = '" + studentID + "'";
        pqxx::result studentResult(N.exec(sql));
        for (auto row : studentResult) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
void accountantMenu() {
    system("cls"); // Clear the console
    cout << "Accountant Menu" << endl;
    cout << "1. View Accounts" << endl;
    cout << "2. Update Accounts" << endl;
    cout << "3. Generate Report" << endl;
    cout << "4. Logout" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewAccounts();
        break;
    case 2:
        updateAccounts();
        break;
    case 3:
        generateReport();
        break;
    case 4:
        cout << "Logging out..." << endl;
        displayLoginMenu();
        return; // Return to previous menu
    default:
        cout << "Invalid choice. Please try again." << endl;
        accountantMenu(); // Show menu again
        break;
    }
}
//________________________________________________________________________________________
void viewAccounts() {
    // Add functionality to view accounts
    cout << "Viewing Accounts..." << endl;
}

void updateAccounts() {
    // Add functionality to update accounts
    cout << "Updating Accounts..." << endl;
}

void generateReport() {
    // Add functionality to generate report
    cout << "Generating Report..." << endl;
}

//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________

void teacherMenu() {
    system("cls"); // Clear the console
    cout << "Teacher Menu" << endl;
    cout << "1. View Timetable" << endl;
    cout << "2. Manage Grades" << endl;
    cout << "3. Manage Attendance" << endl;
    cout << "4. Logout" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        viewTimeTable();
        break;
    case 2:
        manageGrades();
        break;
    case 3:
        manageAttendance();
        break;
    case 4:
        cout << "Logging out..." << endl;
        displayLoginMenu();
        return; // Return to previous menu
    default:
        cout << "Invalid choice. Please try again." << endl;
        teacherMenu(); // Show menu again
        break;
    }
}

//________________________________________________________________________________________
void viewTimeTable() {
    system("cls"); // Clear the console
    cout << "View Schedule" << endl;

    // Connect to the database
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 hostaddr=127.0.0.1 port=5432");
        if (C.is_open()) {
            // SQL query to retrieve timetable information
            std::string sql = "SELECT * FROM Timetable";

            // Execute SQL query
            pqxx::nontransaction N(C);
            pqxx::result R(N.exec(sql));

            // Display the results
            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
                cout << "Timetable ID: " << c[0].as<int>() << endl;
                cout << "Subject ID: " << c[1].as<int>() << endl;
                cout << "Time: " << c[2].as<string>() << endl;
                cout << "Days: " << c[3].as<string>() << endl;
                cout << "Class ID: " << c[4].as<string>() << endl;
                cout << "---------------------" << endl;
            }
        }
        else {
            cerr << "Can't open database" << endl;
        }
        
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue . . .";
    cin.ignore();
    cin.get();
    teacherMenu();
}

void manageGrades() {
    system("cls"); // Clear the console
    cout << "Manage Grades" << endl;

    string studentID;
    int subjectID;
    float mark;

    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Subject ID: ";
    cin >> subjectID;
    cout << "Enter Mark: ";
    cin >> mark;

    // Connect to the database
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 hostaddr=127.0.0.1 port=5432");
        if (C.is_open()) {
            // SQL query to insert or update the grade
            std::string sql = "INSERT INTO StudentMarks (StudentID, SubjectID, Mark) VALUES ('" + studentID + "', " + to_string(subjectID) + ", " + to_string(mark) + ") "
                "ON CONFLICT (StudentID, SubjectID) DO UPDATE SET Mark = EXCLUDED.Mark";

            // Execute SQL query
            pqxx::work W(C);
            W.exec(sql);
            W.commit();

            cout << "Grade updated successfully" << endl;
        }
        else {
            cerr << "Can't open database" << endl;
        }
       
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue . . .";
    cin.ignore();
    cin.get();
    teacherMenu();
}

void manageAttendance() {
    system("cls"); // Clear the console
    cout << "Manage Attendance" << endl;

    string studentID;
    string date;
    bool isPresent;
    string classID;

    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter Attendance (1 for present, 0 for absent): ";
    cin >> isPresent;
    cout << "Enter Class ID: ";
    cin >> classID;

    // Connect to the database
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 hostaddr=127.0.0.1 port=5432");
        if (C.is_open()) {
            // SQL query to insert or update the attendance
            std::string sql = "INSERT INTO Attendance (StudentID, Date, IsPresent, ClassID) VALUES ('" + studentID + "', '" + date + "', " + to_string(isPresent) + ", '" + classID + "') "
                "ON CONFLICT (StudentID, Date, ClassID) DO UPDATE SET IsPresent = EXCLUDED.IsPresent";

            // Execute SQL query
            pqxx::work W(C);
            W.exec(sql);
            W.commit();

            cout << "Attendance updated successfully" << endl;
        }
        else {
            cerr << "Can't open database" << endl;
        }
        
    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue . . .";
    cin.ignore();
    cin.get();
    teacherMenu();
}

//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________
//________________________________________________________________________________________




// Function to issue a book to a person
void Book::issueBook(int bookID, int personID) {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        pqxx::work W(C);

        // Check if the book is already issued
        pqxx::result R = W.exec("SELECT * FROM Book WHERE borrowed_by_person_id IS NULL AND BookID = " + W.quote(bookID));
        if (R.size() == 0) {
            cout << "The book is already issued to someone else or does not exist." << endl;
            return;
        }

        // Issue the book
        W.exec("UPDATE Book SET borrowed_by_person_id = " + W.quote(to_string(personID)) + " WHERE BookID = " + W.quote(to_string(bookID)));
        W.commit();
        cout << "Book issued successfully." << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

// Function to return a book
void Book::returnBook(int bookID) {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        pqxx::work W(C);

        // Check if the book is issued
        pqxx::result R = W.exec("SELECT * FROM Book WHERE \"borrowed by(personID)\" IS NOT NULL AND BookID = " + W.quote(bookID));
        if (R.size() == 0) {
            cout << "The book is not issued or does not exist." << endl;
            return;
        }

        // Return the book
        W.exec("UPDATE Book SET \"borrowed by(personID)\" = NULL WHERE BookID = " + W.quote(to_string(bookID)));
        W.commit();
        cout << "Book returned successfully." << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

// Function to search for a book by title
void Book::searchBook(const string& title) {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R = N.exec(
            "SELECT Book.BookID, Book.Title, Book.Shelf_NO, Person.Name AS Borrower "
            "FROM Book "
            "LEFT JOIN Person ON Book.borrowed_by_person_id = Person.ID "
            "WHERE Book.Title ILIKE '%' || " + N.quote(title) + " || '%'"
        );

        cout << "Search Results:" << endl;
        for (auto row : R) {
            cout << "Book ID: " << row["BookID"].as<int>()
                << ", Title: " << row["Title"].c_str()
                << ", Shelf No: " << row["Shelf_NO"].c_str();
            if (row["Borrower"].is_null()) {
                cout << ", Borrower: None" << endl;
            }
            else {
                cout << ", Borrower: " << row["Borrower"].c_str() << endl;
            }
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}


// Function to add a new book
void Book::addBook(const string& shelf_no, const string& title) {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        pqxx::work W(C);
        W.exec("INSERT INTO Book (Shelf_NO, Title) VALUES (" + W.quote(shelf_no) + ", " + W.quote(title) + ")");
        W.commit();
        cout << "Book added successfully." << endl;
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}


void issue_book() {
    int bookID, personID;
    cout << "Enter Book ID: ";
    cin >> bookID;
    cout << "Enter Person ID: ";
    cin >> personID;
    Book::issueBook(bookID, personID);
    system("pause");
    librarianMenu();
}

void return_book() {
    int bookID;
    cout << "Enter Book ID: ";
    cin >> bookID;
    Book::returnBook(bookID);
    system("pause");
    librarianMenu();
}

void search_book() {
    string title;
    cout << "Enter Book Title: ";
    cin.ignore(); // Clear newline character from input buffer
    getline(cin, title);
    Book::searchBook(title);
    system("pause");
    librarianMenu();
}

void add_book() {
    string shelf_no, title;
    cout << "Enter Shelf Number: ";
    cin.ignore(); // Clear newline character from input buffer
    getline(cin, shelf_no);
    cout << "Enter Book Title: ";
    getline(cin, title);
    Book::addBook(shelf_no, title);
    system("pause");
    librarianMenu();
}


void librarianMenu() {
    system("cls"); // Clear the console
    cout << "Librarian Menu" << endl;
    cout << "1. Issue Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Add Book" << endl;
    cout << "5. Logout" << endl;

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        issue_book();
        break;
    case 2:
        return_book();
        break;
    case 3:
        search_book();
        break;
    case 4:
        add_book();
        break;
    case 5:
        cout << "Logging out..." << endl;
        displayLoginMenu();
        return; // Return to previous menu
    default:
        cout << "Invalid choice. Please try again." << endl;
        librarianMenu(); // Show menu again
        break;
    }
}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void principalMenu() {
    system("cls"); // Clear the console
    cout << "Principal Menu" << endl;;
    menu();
 
}
void deputyPrincipalMenu() {
    system("cls"); // Clear the console
    cout << "deputy Principal Menu" << endl;;
    menu();

}

void menu() {
    int choice;
    do {
        cout << "1. Add Person" << endl;
        cout << "2. Delete Person" << endl;
        cout << "3. View Table" << endl;
        cout << "4. Logout" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPerson();
            break;
        case 2:
            deletePerson();
            break;
        case 3:
            viewTable();
            break;
        case 4:
            cout << "Logging out..." << endl;
            displayLoginMenu();
            return; // Return to previous menu
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice < 1 || choice > 4);
}



void addPerson() {
    // Get input for the new person
    int id;
    string name;
    string phoneNumber;
    string emailAddress;
    string dateOfBirth;
    string address;
    string password;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(); // Ignore newline character
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);
    cout << "Enter Email Address: ";
    getline(cin, emailAddress);
    cout << "Enter Date of Birth: ";
    getline(cin, dateOfBirth);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Password: ";
    getline(cin, password);

    try {
        // Establish connection to the database
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        // Create a transactional object
        pqxx::work W(C);

        // Insert into the Person table
        string insertPersonSQL = "INSERT INTO Person (ID, Name, PhoneNumber, EmailAddress, DateOfBirth, Address, Password) VALUES ("
            + W.quote(to_string(id)) + ", "
            + W.quote(name) + ", "
            + W.quote(phoneNumber) + ", "
            + W.quote(emailAddress) + ", "
            + W.quote(dateOfBirth) + ", "
            + W.quote(address) + ", "
            + W.quote(password) + ");";
        W.exec(insertPersonSQL);

        // Check the role of the person and insert into the respective table
        // For example, if the person is a teacher, insert into the Teacher table
        // You need to handle each role accordingly

        // Commit the transaction
        W.commit();

        cout << "Person added successfully!" << endl;

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}


void deletePerson() {
    // Get the ID of the person to delete
    int id;
    cout << "Enter ID of the person to delete: ";
    cin >> id;

    try {
        // Establish connection to the database
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            cerr << "Can't open database" << endl;
            return;
        }

        // Create a transactional object
        pqxx::work W(C);

        // Check if the person exists in the database
        string checkPersonSQL = "SELECT * FROM Person WHERE ID = " + W.quote(to_string(id)) + ";";
        pqxx::result R(W.exec(checkPersonSQL));

        if (R.empty()) {
            cout << "Person with ID " << id << " does not exist." << endl;
            return;
        }

        // Delete the person from the Person table
        string deletePersonSQL = "DELETE FROM Person WHERE ID = " + W.quote(to_string(id)) + ";";
        W.exec(deletePersonSQL);

        // You need to handle deleting data from the related tables based on the role of the person
        // For example, if the person is a teacher, delete from the Teacher table
        // You need to handle each role accordingly

        // Commit the transaction
        W.commit();

        cout << "Person with ID " << id << " deleted successfully!" << endl;

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
}



void viewTable() {
    int choice;
    do {
        cout << "View Tables" << endl;
        cout << "1. View Person Table" << endl;
        cout << "2. View Teacher Table" << endl;
        cout << "3. View Student Table" << endl;
        cout << "4. View Class Table" << endl;
        cout << "5. View Subject Table" << endl;
        cout << "6. View Timetable Table" << endl;
        cout << "7. View Book Table" << endl;
        cout << "8. View Attendance Table" << endl;
        cout << "9. View Other Table" << endl;
        cout << "10. Back to Main Menu" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewPersonTable();
            break;
        case 2:
            viewTeacherTable();
            break;
        case 3:
            viewStudentTable();
            break;
        case 4:
            viewClassTable();
            break;
        case 5:
            viewSubjectTable();
            break;
        case 6:
            viewTimetableTable();
            break;
        case 7:
            viewBookTable();
            break;
        case 8:
            viewAttendanceTable();
            break;
        case 9:
            cout << "wait for future updates";
            break;
            system("cls");
            cout << "Returning to the main menu..." << endl;
            return; // Return to the main menu
        case 10:
            cout << "Returning to the main menu..." << endl;
            return; // Return to the main menu
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
 
    } while (choice < 1 || choice > 10);
    system("cls");
    viewTable();
}
void viewPersonTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Person"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to view the Teacher table
void viewTeacherTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Teacher"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
// Function to view the Student table
void viewStudentTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Student"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to view the Class table
void viewClassTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Class"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to view the Subject table
void viewSubjectTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Subject"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
// Function to view the Timetable table
void viewTimetableTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Timetable"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to view the Book table
void viewBookTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Book"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to view the Attendance table
void viewAttendanceTable() {
    try {
        pqxx::connection C("dbname=School_Management_System user=postgres password=654321 port=5432");
        if (!C.is_open()) {
            std::cerr << "Can't open database" << std::endl;
            return;
        }

        pqxx::nontransaction N(C);
        pqxx::result R(N.exec("SELECT * FROM Attendance"));

        // Output table content
        for (auto row : R) {
            for (auto field : row) {
                std::cout << field.c_str() << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
