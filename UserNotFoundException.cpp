#pragma once
#include <iostream>
using namespace std;

class UserNotFoundException: public exception{
    public:
        const char* what() const throw(){
            return "user was not found";
        }
};