#include <iostream>
#include <fstream>
#include "User.cpp"
#include "FileNotFoundException.cpp"
#include "UserNotFoundException.cpp"
#include "UserDuplicatedException.cpp"
#include <vector>
#include "FileUtil.cpp"
using namespace std;

class UserService{
private:
    vector<User> userList;
    User user;
    const string filename="users.dat";
public:
    // void addUser(User& user){
    //     ofstream fout;
    //     fout.open(filename, ios::out|ios::app|ios::binary);
    //     if(!fout){
    //         // cerr<<"file open failed"<<endl;
    //         // exit(0);
    //         throw FileNotFoundException();
    //     }
    //     if(getUserByName(user.getUsername())==nullptr){
    //         fout.write((char*)& user, sizeof(User));
    //     }else{
    //         throw UserDuplicatedException();
    //     }
        
    //     fout.close();
    // }

    void addUser(User& user){
        FileUtil fio;
        fio.openOutputFile(filename);
        if(getUserByName(user.getUsername())==nullptr){
            fio.writeDataToFile(user);
        }else{
            throw UserDuplicatedException();
        }
        
        fio.closeOutputFile();
    }
    void addUser(string username, string password, string role){
        User user(username, password, role);
        ofstream fout;
        fout.open(filename, ios::out|ios::app|ios::binary);
        if(!fout){
             // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        if(getUserByName(username)==nullptr){
            fout.write((char*)& user, sizeof(User));
        }else{
            throw UserDuplicatedException();
        }
        fout.close();
    }
    // void viewUsers(){
    //     User user;
    //     ifstream fin;
    //     bool flag=false;
    //     fin.open(filename, ios::in|ios::binary);
    //     if(!fin){
    //         // cerr<<"file open failed"<<endl;
    //         // exit(0);
    //         throw FileNotFoundException();
    //     }
    //     while(fin.read((char*)& user, sizeof(User))){
    //         user.display();
    //         flag=true;
    //     }
    //     fin.close();
    //     if(!flag){
    //         throw UserNotFoundException();
    //     }
    // }
    void viewUsers(){
        User user;
        ifstream fin;
        bool flag=false;
        FileUtil fio;
        fin=fio.openInputFile(filename);
        if(!fin){
            // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            user.display();
            flag=true;
        }
        fin.close();
        if(!flag){
            throw UserNotFoundException();
        }
    }


    void updateUser(string username){
        User user;
        fstream fio;
        bool flag=false;
        fio.open(filename, ios::in|ios::out|ios::binary);
        if(!fio){
             // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fio.read((char*)& user, sizeof(User))){
            if(user.getUsername()==username){
                user.inputUser();
                int position=(-1)*static_cast<int>(sizeof(User));
                fio.seekp(position, ios::cur);
                fio.write((char*)& user, sizeof(User));
                flag=true;
                break;
            }
        }
        fio.close();
        if(!flag){
            throw UserNotFoundException();
        }
        
    }
    void deleteUser(string username){
        User user;
        ifstream fin;
        ofstream fout;
        bool flag=false;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
             // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        fout.open("temp.dat", ios::out|ios::app|ios::binary);
        if(!fout){
            // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }

        while(fin.read((char*)& user, sizeof(User))){
            if(user.getUsername()!=username){
                fout.write((char*)& user, sizeof(User));
            }else{
                flag=true;
            }
        }
        fin.close();
        fout.close();

        remove("users.dat");
        rename("temp.dat", "users.dat");
        if(!flag){
            throw UserNotFoundException();
        }
       
    }
    vector<User> getUsers(){
        vector<User> users;
        User user;
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
             // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            users.push_back(user);
        }
        fin.close();
        return users;
    }

    User* getUserByName(string username){
      
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
            // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            if(user.getUsername()==username){
                return &user;
            }
        }
        fin.close();
        return nullptr;
    }
    bool getUser(string username){
      
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
            // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            if(user.getUsername()==username){
                return true;
            }
        }
        fin.close();
        return false;
    }

    bool authenticateUser(string username, string password){
        User user;
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
            // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            if(user.getUsername()==username && user.getPassword()==password){
                return true;
            }
        }
        fin.close();
        return false;
    }

    User* authenticateUser2(string username, string password){
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
             // cerr<<"file open failed"<<endl;
            // exit(0);
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            if(user.getUsername()==username && user.getPassword()==password){
                return &user;
            }
        }
        fin.close();
        return nullptr;
    }

    vector<User> getUsers2(){
        User user1("dara","123", "admin");
        User user2("lina","123", "user");
        userList.push_back(user1);
        userList.push_back(user2);
        return userList;
    }

   User* authenticateUser3(const string& username, const string& password)
{
    for (const User& user : userList) {
        if (user.getUsername() == username && user.getPassword() == password) {
            User* userPtr = new User(user); // Dynamically allocate a new User object
            return userPtr; // Return a pointer to the object
        }
    }
    // Handle authentication failure
    throw runtime_error("Authentication failed");
}

    void saveDataToFile(){
        ofstream fout;
        fout.open(filename, ios::out|ios::app|ios::binary);
        if(!fout){
            throw FileNotFoundException();
        }
        for(User user: userList){
            fout.write((char*)& user, sizeof(User));
        }
       
        fout.close();
    }

    void LoadDataFromFile(){
        ifstream fin;
        fin.open(filename, ios::in|ios::binary);
        if(!fin){
            throw FileNotFoundException();
        }
        while(fin.read((char*)& user, sizeof(User))){
            userList.push_back(user);
        }
        fin.close();

    }



   
   

};