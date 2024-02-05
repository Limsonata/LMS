#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class Book {
private:
    string title;
    string author;
    int publicationYear;

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
        static int catalogNumber = 1;
        os << "Catalog Number: " << catalogNumber << endl;
        os << "Title: " << book.title << endl;
        os << "Author: " << book.author << endl;
        os << "Publication Year: " << book.publicationYear << endl;
        catalogNumber++;
        return os;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void loadBooksFromFile() {
        ifstream inFile("books.txt");
        if (inFile) {
            string line;
            while (getline(inFile, line)) {
                string title, author;
                int publicationYear;

                size_t pos = line.find(',');
                title = line.substr(0, pos);
                line.erase(0, pos + 2);

                pos = line.find(',');
                author = line.substr(0, pos);
                line.erase(0, pos + 2);

                publicationYear = stoi(line);

                Book book(title, author, publicationYear);
                books.push_back(book);
            }
            inFile.close();
            cout << "Books loaded from file successfully!" << endl;
        } else {
            cout << "Error opening the file for reading." << endl;
        }
    }

    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added successfully!" << endl;

        ofstream outFile("books.txt", ios::app);
        if (outFile) {
            outFile << book.getTitle() << ", " << book.getAuthor() << ", " << book.getPublicationYear() << endl;
            outFile.close();
            cout << "Book details stored in file successfully!" << endl;
        } else {
            cout << "Error opening the file for writing." << endl;
        }
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
        for (size_t i = 0; i < books.size(); ++i) {
            cout << "Catalog Number: " << (i + 1) << endl;
            cout << "Title: " << books[i].getTitle() << endl;
            cout << "Author: " << books[i].getAuthor() << endl;
            cout << "Publication Year: " << books[i].getPublicationYear() << endl;
            cout << "-------------------------" << endl;
        }
    }
}
};

class Application {
private:
    Library library;

public:
    void run() {
        library.loadBooksFromFile();

        int choice;
        do {
            cout << "\n----- Library Management System -----" << endl;
            cout << "1. Add a book" << endl;
            cout << "2. Remove a book" << endl;
            cout << "3. Search books by author" << endl;
            cout << "4. Update book details" << endl;
            cout << "5. Display allbooks" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                string title, author;
                int publicationYear;

                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);

                // Validate that the title is not empty
                if (title.empty()) {
                    cout << "Invalid input. Title cannot be empty." << endl;
                    break;
                }

                cout << "Enter book author: ";
                getline(cin, author);

                // Validate that the author is not empty
                if (author.empty()) {
                    cout << "Invalid input. Author cannot be empty." << endl;
                    break;
                }

                cout << "Enter publication year: ";
                cin >> publicationYear;

                // Validate that the publication year is a positive number
                if (publicationYear <= 0) {
                    cout << "Invalid input. Publication year must be a positive number." << endl;
                    break;
                }

    Book book(title, author, publicationYear);
    library.addBook(book);
    break;
                }
                case 2: {
                    string title;
                    cin.ignore();
                    cout << "Enter book title to remove: ";
                    getline(cin, title);
                    library.removeBook(title);
                    break;
                }
                case 3: {
                    string author;
                    cin.ignore();
                    cout << "Enter author name to search: ";
                    getline(cin, author);
                    library.searchBooksByAuthor(author);
                    break;
                }
                case 4: {
                    string title;
                    cin.ignore();
                    cout << "Enter book title to update: ";
                    getline(cin, title);
                    library.updateBook(title);
                    break;
                }
                case 5: {
                    library.displayBooks();
                    break;
                }
                case 0: {
                    cout << "Exiting the program..." << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        } while (choice != 0);
    }
};
