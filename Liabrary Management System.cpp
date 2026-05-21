#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Book Class demonstrating Encapsulation
class Book {
private:
    int bookID;
    string title;
    string author;
    bool isIssued;

public:
    Book() {
        bookID = 0;
        title = "";
        author = "";
        isIssued = false;
    }

    void inputBookDetails() {
        cout << "\n=====================================";
        cout << "\n       ENTER NEW BOOK DETAILS        ";
        cout << "\n=====================================";
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore(); // Clear buffer
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        isIssued = false;
        cout << "\nBook Added Successfully!\n";
    }

    void displayBookDetails() const {
        cout << "\n-------------------------------------";
        cout << "\nBook ID   : " << bookID;
        cout << "\nTitle     : " << title;
        cout << "\nAuthor    : " << author;
        cout << "\nStatus    : " << (isIssued ? "Issued ??" : "Available ??");
        cout << "\n-------------------------------------\n";
    }

    // Getters and Setters
    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIssuedStatus() const { return isIssued; }
    
    void setIssuedStatus(bool status) { isIssued = status; }
    void setBookID(int id) { bookID = id; }
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
};

// Member Class demonstrating Encapsulation
class Member {
private:
    int memberID;
    string memberName;

public:
    Member() {
        memberID = 0;
        memberName = "";
    }

    void inputMemberDetails() {
        cout << "\n=====================================";
        cout << "\n      ENTER NEW MEMBER DETAILS       ";
        cout << "\n=====================================";
        cout << "\nEnter Member ID: ";
        cin >> memberID;
        cin.ignore(); // Clear buffer
        cout << "Enter Member Name: ";
        getline(cin, memberName);
        cout << "\nMember Registered Successfully!\n";
    }

    void displayMemberDetails() const {
        cout << "\n-------------------------------------";
        cout << "\nMember ID   : " << memberID;
        cout << "\nName        : " << memberName;
        cout << "\n-------------------------------------\n";
    }

    int getMemberID() const { return memberID; }
    string getMemberName() const { return memberName; }
    
    void setMemberID(int id) { memberID = id; }
    void setMemberName(string n) { memberName = n; }
};

// Global Function Declarations for Database File Operations
void addBook();
void addMember();
void displayAllBooks();
void displayAllMembers();
void searchBook();
void issueBook();
void returnBook();

int main() {
    int choice;

    do {
        cout << "\n=====================================";
        cout << "\n     LIBRARY MANAGEMENT SYSTEM       ";
        cout << "\n=====================================";
        cout << "\n1. ADD NEW BOOK";
        cout << "\n2. REGISTER NEW MEMBER";
        cout << "\n3. DISPLAY ALL BOOKS";
        cout << "\n4. DISPLAY ALL MEMBERS";
        cout << "\n5. SEARCH BOOK (BY TITLE/AUTHOR)";
        cout << "\n6. ISSUE A BOOK";
        cout << "\n7. RETURN A BOOK";
        cout << "\n8. EXIT";
        cout << "\n=====================================";
        cout << "\nSelect Your Option (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: displayAllBooks(); break;
            case 4: displayAllMembers(); break;
            case 5: searchBook(); break;
            case 6: issueBook(); break;
            case 7: returnBook(); break;
            case 8: cout << "\nExiting Library Management System. Thank you!\n"; break;
            default: cout << "\nInvalid Choice! Please select options between 1-8.";
        }
    } while (choice != 8);

    return 0;
}

// Function to store Book records sequentially to a file
void addBook() {
    Book b;
    b.inputBookDetails();

    ofstream outFile("books_database.txt", ios::app);
    if (!outFile) {
        cout << "\nDatabase Error: Unable to open file!";
        return;
    }

    outFile << b.getBookID() << endl;
    outFile << b.getTitle() << endl;
    outFile << b.getAuthor() << endl;
    outFile << b.getIssuedStatus() << endl;
    outFile.close();
}

// Function to store Member records sequentially to a file
void addMember() {
    Member m;
    m.inputMemberDetails();

    ofstream outFile("members_database.txt", ios::app);
    if (!outFile) {
        cout << "\nDatabase Error: Unable to open file!";
        return;
    }

    outFile << m.getMemberID() << endl;
    outFile << m.getMemberName() << endl;
    outFile.close();
}

// Function to view all library books
void displayAllBooks() {
    ifstream inFile("books_database.txt");
    if (!inFile) {
        cout << "\nNo records found! Database file empty.";
        return;
    }

    int id;
    string title, author;
    bool status;

    cout << "\n=====================================================================";
    cout << "\n                            ALL BOOKS                                ";
    cout << "\n=====================================================================";
    cout << "\n" << left << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Status";
    cout << "\n---------------------------------------------------------------------";

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, title);
        getline(inFile, author);
        inFile >> status;

        cout << "\n" << left << setw(10) << id 
             << setw(30) << title 
             << setw(20) << author 
             << (status ? "Issued ??" : "Available ??");
    }
    cout << "\n=====================================================================\n";
    inFile.close();
}

// Function to view all registered members
void displayAllMembers() {
    ifstream inFile("members_database.txt");
    if (!inFile) {
        cout << "\nNo records found! Member database file empty.";
        return;
    }

    int id;
    string name;

    cout << "\n========================================";
    cout << "\n             LIBRARY MEMBERS            ";
    cout << "\n========================================";
    cout << "\n" << left << setw(15) << "Member ID" << "Name";
    cout << "\n----------------------------------------";

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, name);

        cout << "\n" << left << setw(15) << id << name;
    }
    cout << "\n========================================\n";
    inFile.close();
}

// Function to search books dynamically by keyword (Title or Author)
void searchBook() {
    ifstream inFile("books_database.txt");
    if (!inFile) {
        cout << "\nDatabase file missing.";
        return;
    }

    cin.ignore();
    string searchKeyword;
    cout << "\nEnter Book Title or Author name to search: ";
    getline(cin, searchKeyword);

    int id;
    string title, author;
    bool status;
    bool found = false;

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, title);
        getline(inFile, author);
        inFile >> status;

        // Simple case-insensitive simulation check
        if (title == searchKeyword || author == searchKeyword) {
            Book temp;
            temp.setBookID(id);
            temp.setTitle(title);
            temp.setAuthor(author);
            temp.setIssuedStatus(status);
            temp.displayBookDetails();
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "\nNo match found for: \"" << searchKeyword << "\".";
    }
}

// Processing Book Issue System using clean File-swaps
void issueBook() {
    ifstream bookFile("books_database.txt");
    ofstream tempFile("temp_books.txt");

    if (!bookFile) {
        cout << "\nDatabase missing. No books available to issue.";
        return;
    }

    int targetID;
    cout << "\nEnter Book ID to Issue: ";
    cin >> targetID;

    int id;
    string title, author;
    bool status;
    bool found = false;

    while (bookFile >> id) {
        bookFile.ignore();
        getline(bookFile, title);
        getline(bookFile, author);
        bookFile >> status;

        Book temp;
        temp.setBookID(id);
        temp.setTitle(title);
        temp.setAuthor(author);
        temp.setIssuedStatus(status);

        if (id == targetID) {
            found = true;
            if (temp.getIssuedStatus()) {
                cout << "\nError: This book is already issued to someone else.";
            } else {
                temp.setIssuedStatus(true);
                cout << "\nBook \"" << temp.getTitle() << "\" has been successfully issued.";
            }
        }

        tempFile << temp.getBookID() << endl;
        tempFile << temp.getTitle() << endl;
        tempFile << temp.getAuthor() << endl;
        tempFile << temp.getIssuedStatus() << endl;
    }

    bookFile.close();
    tempFile.close();

    remove("books_database.txt");
    rename("temp_books.txt", "books_database.txt");

    if (!found) {
        cout << "\nError: Book ID " << targetID << " not found.";
    }
}

// Processing Book Return operations
void returnBook() {
    ifstream bookFile("books_database.txt");
    ofstream tempFile("temp_books.txt");

    if (!bookFile) {
        cout << "\nDatabase missing.";
        return;
    }

    int targetID;
    cout << "\nEnter Book ID to Return: ";
    cin >> targetID;

    int id;
    string title, author;
    bool status;
    bool found = false;

    while (bookFile >> id) {
        bookFile.ignore();
        getline(bookFile, title);
        getline(bookFile, author);
        bookFile >> status;

        Book temp;
        temp.setBookID(id);
        temp.setTitle(title);
        temp.setAuthor(author);
        temp.setIssuedStatus(status);

        if (id == targetID) {
            found = true;
            if (!temp.getIssuedStatus()) {
                cout << "\nError: This book was never issued. It is already in the library.";
            } else {
                temp.setIssuedStatus(false);
                cout << "\nBook \"" << temp.getTitle() << "\" has been successfully returned.";
            }
        }

        tempFile << temp.getBookID() << endl;
        tempFile << temp.getTitle() << endl;
        tempFile << temp.getAuthor() << endl;
        tempFile << temp.getIssuedStatus() << endl;
    }

    bookFile.close();
    tempFile.close();

    remove("books_database.txt");
    rename("temp_books.txt", "books_database.txt");

    if (!found) {
        cout << "\nError: Book ID " << targetID << " not found.";
    }
}

