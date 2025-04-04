// ----------4️⃣ Design a Library Management System-----------
// Problem Statement
// Design a Library System that allows:
// ✅ Users to borrow and return books
// ✅ Admin to add or remove books
// ✅ Maintain book inventory and due dates
// ✅ Handle book reservations

// 👉 Think about: User, Book, Librarian, BorrowRecord.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------------- Book Class -----------------
class Book {
private:
    int bookId;
    string title;
    bool isAvailable;

public:
    Book(int id, string t) : bookId(id), title(t), isAvailable(true) {}

    int getBookId() const { return bookId; }
    string getTitle() const { return title; }
    bool isBookAvailable() const { return isAvailable; }

    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }
};

// Custom Hash Function for unordered_map
struct BookHash {
    size_t operator()(const Book* b) const {
        return hash<int>()(b->getBookId());
    }
};

// Custom Equality Check for unordered_map
struct BookEqual {
    bool operator()(const Book* b1, const Book* b2) const {
        return b1->getBookId() == b2->getBookId();
    }
};

// ---------------- User Class -----------------
class User {
private:
    int userId;
    unordered_set<Book*> borrowedBooks; // Set of borrowed book pointers

public:
    User(int id) : userId(id) {}

    int getUserId() const { return userId; }

    void borrowBook(Book* book) {
        if (!book->isBookAvailable()) {
            cout << "Book '" << book->getTitle() << "' is already borrowed!" << endl;
            return;
        }
        book->borrowBook();
        borrowedBooks.insert(book);
        cout << "Book '" << book->getTitle() << "' borrowed successfully." << endl;
    }

    void returnBook(Book* book) {
        if (borrowedBooks.find(book) != borrowedBooks.end()) {
            book->returnBook();
            borrowedBooks.erase(book);
            cout << "Book '" << book->getTitle() << "' returned successfully." << endl;
        } else {
            cout << "You don't have this book borrowed." << endl;
        }
    }
};

// ---------------- Borrow Record Class -----------------
class BorrowRecord {
private:
    unordered_map<Book*, pair<User*, ll>, BookHash, BookEqual> borrowedBooks; // Book → {User, Due Date}
    queue<User*> reservationQueue; // Queue for book reservations

public:
    void borrowBook(User* user, Book* book, ll dueDate) {
        if (book->isBookAvailable()) {
            borrowedBooks[book] = {user, dueDate};
            book->borrowBook();
            cout << "Book '" << book->getTitle() << "' borrowed by User " << user->getUserId() << ". Due in " << dueDate << " days." << endl;
        } else {
            cout << "Book '" << book->getTitle() << "' is already borrowed. Added to reservation queue." << endl;
            reservationQueue.push(user);
        }
    }

    void returnBook(Book* book) {
        if (borrowedBooks.find(book) != borrowedBooks.end()) {
            borrowedBooks.erase(book);
            book->returnBook();
            cout << "Book '" << book->getTitle() << "' returned." << endl;

            // Assign book to next user in queue if any
            if (!reservationQueue.empty()) {
                User* nextUser = reservationQueue.front();
                reservationQueue.pop();
                borrowBook(nextUser, book, 7); // Assign for 7 days
            }
        } else {
            cout << "Book was not borrowed." << endl;
        }
    }
};

// ---------------- Librarian Class -----------------
class Librarian {
private:
    unordered_set<Book*> bookInventory; // Stores all books

public:
    void addBook(Book* book) {
        if (bookInventory.find(book) != bookInventory.end()) {
            cout << "Book '" << book->getTitle() << "' already exists!" << endl;
        } else {
            bookInventory.insert(book);
            cout << "Book '" << book->getTitle() << "' added to library." << endl;
        }
    }

    void removeBook(Book* book) {
        if (bookInventory.erase(book)) {
            cout << "Book '" << book->getTitle() << "' removed from library." << endl;
        } else {
            cout << "No such book exists in the library." << endl;
        }
    }
};

// ---------------- Library Class -----------------
class Library {
private:
    Librarian librarian;
    BorrowRecord borrowRecord;
    unordered_map<int, User*> users;

public:
    void addBook(Book* book) { librarian.addBook(book); }
    void removeBook(Book* book) { librarian.removeBook(book); }

    void registerUser(int userId) {
        if (users.find(userId) == users.end()) {
            users[userId] = new User(userId);
            cout << "User " << userId << " registered successfully." << endl;
        } else {
            cout << "User " << userId << " already exists." << endl;
        }
    }

    void borrowBook(int userId, Book* book, ll dueDate) {
        if (users.find(userId) != users.end()) {
            borrowRecord.borrowBook(users[userId], book, dueDate);
        } else {
            cout << "User ID " << userId << " not found." << endl;
        }
    }

    void returnBook(Book* book) { borrowRecord.returnBook(book); }
};

// ---------------- Main Function -----------------
int main() {
    Library library;

    // Create books
    Book* book1 = new Book(101, "C++ Programming");
    Book* book2 = new Book(102, "Data Structures");

    // Register users
    library.registerUser(1);
    library.registerUser(2);

    // Add books to library
    library.addBook(book1);
    library.addBook(book2);

    // Borrow and return books
    library.borrowBook(1, book1, 14); // User 1 borrows book1
    library.borrowBook(2, book1, 14); // User 2 tries to borrow book1 (reservation added)

    library.returnBook(book1); // User 1 returns book1 → Auto assigns to User 2

    // Clean up
    delete book1;
    delete book2;

    return 0;
}
