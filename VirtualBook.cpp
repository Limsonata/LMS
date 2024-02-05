#pragma once
#include <iostream>
#include <sstream>
#include "Book.cpp"

using namespace std;

class VirtualBook: public Book {
public:
    void read() override {
        cout << "This is a virtual book. You can read it online." << endl;
    }
};