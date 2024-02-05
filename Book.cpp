#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
};

ostream& operator<<(ostream& os, const Book& book) {
    os << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << ", Publication Year: " << book.getPublicationYear();
    return os;
}