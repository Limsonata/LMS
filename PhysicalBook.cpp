#pragma once
#include <iostream>
#include <sstream>
#include "Book.cpp"

using namespace std;

class PhysicalBook: public Book {
public:
    void read() override {
        cout << "This is a physical book. You can read it by flipping the pages." << endl;
    }
};