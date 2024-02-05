#include "User.cpp"
#include <iostream>
#include <vector>
#pragma once
#include "Application.cpp"
using namespace std;


class AuthenticationService {
private:
    vector<User> users;

public:
    AuthenticationService() {
        // Initialize with some pre-existing users
        users.push_back(User("admin", "password", "admin"));
        users.push_back(User("user1", "pass123", "user"));
    }

    User* authenticateUser(const string& username, const string& password) {
        for (auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                return &user; // Return a pointer to the authenticated user
            }
        }
        return nullptr; // Return nullptr if authentication fails
    }
};