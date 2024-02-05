#pragma once

#include <iostream>
using namespace std;

class User{
    private:
        string username;
        string password;
        string role;
    public:
        //constructors
        User():username("unknown"), password("unknown"), role("unknown"){

        }
        User(string username, string password, string role):username(username), password(password),role(role){

        }
        //setter and getter methods
        string getUsername() const{
            return username;
        }
        void setUsername(string username){
            this->username=username;
        }
        string getPassword() const{
            return password;
        }
        void setPassword(string password){
            this->password=password;
        }
        string getRole() const{
            return role;
        }
        void setRole(string role){
            this->role=role;
        }
        //methods
        void display(){
            cout<<"Username: "<<username<<" Password:"<<password<<" Role:"<<role<<endl;
        }

        void inputUser(){
            cout<<"Enter username:";
            cin>>username;
            cout<<"Enter password:";
            cin>>password;
            cout<<"Enter role:";
            cin>>role;
        }

};