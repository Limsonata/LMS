#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "PhysicalBook.cpp"
#include "VirtualBook.cpp"

using namespace std;

class Book {
private:
    vector<Book*> books;

public:
    Book(const string& title, const string& author, int publicationYear)
        : title(title), author(author), publicationYear(publicationYear) {}

    const string& getTitle() const {
        return title;
    }

    const string& getAuthor() const {
        return author;
    }

    int getPublicationYear() const {
        return publicationYear;
    }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << ", Author: " << book.author << ", Publication Year: " << book.publicationYear;
        return os;
    }
};

class Library {
private:
    vector<Book*> books;

public:
    void loadBooksFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening the file." << endl;
            return;
        }

        string title, author, publicationYearStr;
        int publicationYear;

        while (inFile >> title >> author >> publicationYearStr) {
            try {
                publicationYear = stoi(publicationYearStr);
                Book book(title, author, publicationYear);
                books.push_back(book);
            } catch (const exception& e) {
                cout << "Error loading book: " << e.what() << endl;
            }
        }

        inFile.close();
        cout << "Books loaded from file successfully!" << endl;
    }

   void addBook(Book* book) {
        books.push_back(book);
        cout << "Book added successfully!" << endl;
    }

    void removeBook(const string& title) {
        bool found = false;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getTitle() == title) {
                books.erase(it);
                cout << "Book removed successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found." << endl;
        }
    }

    void searchBooksByAuthor(const string& author) {
        bool found = false;
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                cout << book << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No books found by author: " << author << endl;
        }
    }

    void updateBook(const string& title) {
        bool found = false;
        for (auto& book : books) {
            if (book.getTitle() == title) {
                string newTitle, newAuthor;
                int newPublicationYear;

                cout << "Enter new title: ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "Enter new author: ";
                getline(cin, newAuthor);
                cout << "Enter new publication year: ";
                cin >> newPublicationYear;

                book = Book(newTitle, newAuthor, newPublicationYear);
                cout << "Book details updated successfully!" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Book not found." << endl;
        }
    }

     void displayBooks() const {
        if (books.empty()) {
            cout << "No books found." << endl;
        } else {
            cout << "Books in the library:" << endl;
            for (const auto& book : books) {
                cout << *book << endl;
            }
        }
    }

    void saveBooksToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening the file for writing." << endl;
            return;
        }

        for (const auto& book : books) {
            outFile << book.getTitle() << " " << book.getAuthor() << " " << book.getPublicationYear() << endl;
        }

        outFile.close();
        cout << "Books saved to file successfully!" << endl;
    }
};

class Application {
private:
    Library library;

public:
    void run() {
        library.loadBooksFromFile("books.txt");

        int choice;
        do {
            cout << "\n--- Library Management System ---" << endl;
            cout << "1. Add a book" << endl;
            cout << "2. Remove a book" << endl;
            cout << "3. Search books by author" << endl;
            cout << "4. Update book details" << endl;
            cout << "5. Display all books" << endl;
            cout << "6. Save books to file" << endl;
            cout << "0. Exit" << endl;
            coutHere's the continuation of the code:

```cpp
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string title, author;
                    int publicationYear;

                    cin.ignore();
                    cout << "Enter the title: ";
                    getline(cin, title);
                    cout << "Enter the author: ";
                    getline(cin, author);
                    cout << "Enter the publication year: ";
                    cin >> publicationYear;

                    Book book(title, author, publicationYear);
                    library.addBook(book);
                    break;
                }
                case 2: {
                    string title;
                    cin.ignore();
                    cout << "Enter the title of the book to remove: ";
                    getline(cin, title);
                    library.removeBook(title);
                    break;
                }
                case 3: {
                    string author;
                    cin.ignore();
                    cout << "Enter the author name: ";
                    getline(cin, author);
                    library.searchBooksByAuthor(author);
                    break;
                }
                case 4: {
                    string title;
                    cin.ignore();
                    cout << "Enter the title of the book to update: ";
                    getline(cin, title);
                    library.updateBook(title);
                    break;
                }
                case 5:
                    library.displayBooks();
                    break;
                case 6:
                    library.saveBooksToFile("books.txt");
                    cout << "Books saved to file successfully!" << endl;
                    break;
                case 0:
                    library.saveBooksToFile("books.txt");
                    cout << "Thank you for using our Library Management System. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } while (choice != 0);
    }
};
