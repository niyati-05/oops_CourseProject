//library management system
#include <iostream>
#include <string>
using namespace std;

/* ================= INLINE FUNCTION ================= */
inline int calculateFine(int daysLate = 0) {
    return daysLate * 5;
}

/* ================= ABSTRACT BASE CLASS ================= */
class Person {
protected:
    string name;

public:
    virtual void getData() = 0;
    virtual void showData() = 0;
};

/* ================= STUDENT CLASS ================= */
class Student : public Person {
private:
    int rollNo;

public:
    void getData() {
        cout << "Enter Student Name: ";
        cin >> name;
        cout << "Enter Roll No: ";
        cin >> rollNo;
    }

    void showData() {
        cout << "Student Name: " << name << endl;
        cout << "Roll No: " << rollNo << endl;
    }

    int getRollNo() {
        return rollNo;
    }
};

/* ================= OPERATOR OVERLOADING CLASS ================= */
class FineAmount {
private:
    int amount;

public:
    FineAmount(int a = 0) {
        amount = a;
    }

    void operator ++() {        // Unary
        amount += 5;
    }

    FineAmount operator +(FineAmount f) {   // Binary
        return FineAmount(amount + f.amount);
    }

    operator int() {           // Data Conversion
        return amount;
    }
};

/* ================= BOOK CLASS ================= */
class Book {
private:
    int bookId;
    string title;
    string author;
    bool issued;
    int issuedToRoll;   

public:
    static int bookCount;

    Book() {
        bookId = 0;
        issued = false;
        issuedToRoll = -1;
    }

    void input() {
        cout << "Enter Book ID: ";
        cin >> bookId;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin,title);
        cout << "Enter Author Name: ";
        cin.ignore();
        getline(cin,author);
        issued = false;
        issuedToRoll = -1;
        bookCount++;
    }

    void display() {
        cout << "Book ID: " << bookId << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Status: " << (issued ? "Issued" : "Available") << endl;
        if (issued)
            cout << "Issued To Roll No: " << issuedToRoll << endl;
    }

    int getId() { return bookId; }
    bool isIssued() { return issued; }

    void issueBook(int roll) {
        issued = true;
        issuedToRoll = roll;
    }

    void returnBook() {
        issued = false;
        issuedToRoll = -1;
    }

    int getIssuedRoll() {
        return issuedToRoll;
    }

    friend void showTotalBooks();
};

int Book::bookCount = 0;

/* ================= FRIEND FUNCTION ================= */
void showTotalBooks() {
    cout << "Total Books in Library: " << Book::bookCount << endl;
}

/* ================= LIBRARY CLASS ================= */
class Library {
private:
    Book books[50];
    int count;

public:
    Library() {
        count = 0;
    }

    void addBook() {
        books[count].input();
        count++;
        cout << "Book Added Successfully!\n";
    }

    void displayBooks() {
        for (int i = 0; i < count; i++) {
            books[i].display();
            cout << "-----------------------\n";
        }
    }

    void issueBook(int id, Student &s) {
        for (int i = 0; i < count; i++) {
            if (books[i].getId() == id && !books[i].isIssued()) {
                books[i].issueBook(s.getRollNo());
                cout << "\nBook Issued Successfully To:\n";
                s.showData();
                return;
            }
        }
        cout << "Book not available!\n";
    }

    void returnBook(int id) {
        int days;
        for (int i = 0; i < count; i++) {
            if (books[i].getId() == id && books[i].isIssued()) {

                cout << "Enter number of days late: ";
                cin >> days;

                FineAmount fine(calculateFine(days));
                ++fine;

                FineAmount extra(10);
                FineAmount totalFine = fine + extra;

                int finalAmount = totalFine;

                cout << "\nBook was issued to Roll No: "
                     << books[i].getIssuedRoll() << endl;

                books[i].returnBook();

                cout << "Book Returned Successfully!\n";
                cout << "Total Fine Amount: Rs. " << finalAmount << endl;
                return;
            }
        }
        cout << "Invalid Book ID!\n";
    }
};

/* ================= MAIN FUNCTION ================= */
int main() {
    Library lib;
    Student s;
    int choice, id;

    do {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Show Total Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            lib.addBook();
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            s.getData();
            cout << "Enter Book ID: ";
            cin >> id;
            lib.issueBook(id, s);
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.returnBook(id);
            break;

        case 5:
            showTotalBooks();
            break;

        case 6:
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 6);

    return 0;
}
