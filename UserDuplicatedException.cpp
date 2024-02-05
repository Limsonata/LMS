#pragma once
#include <iostream>
using namespace std;

class UserDuplicatedException: public exception{
    public:
        const char* what() const throw(){
            return "user duplicated";
        }
};