#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

class Login {
private:
    string LoginID;
    string Password;

public:
    Login() : LoginID(""), Password("") {}

    void setID(string id) {
        LoginID = id;
    }

    void setPW(string pw) {
        Password = pw;
    }

    string getID() {
        return LoginID;
    }

    string getPW() {
        return Password;
    }
};

void registration(Login log) {
    // Registration function implementation
    // ...
}

void login() {
    // Login function implementation
    // ...
}

int main() {
    Login log;

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Registration & Login Form" << endl;
        cout << "\t************************************" << endl;
        cout << "\t1.Register." << endl;
        cout << "\t2.Login." << endl;
        cout << "\t3.Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            registration(log);
        }
        else if (val == 2) {
            login();
        }
        else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
        Sleep(3000);
    }

    return 0;
}