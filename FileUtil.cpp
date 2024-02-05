#include "FileNotFoundException.cpp"
#include <iostream>
#include <fstream>
#include "User.cpp"
using namespace std;

class FileUtil{
    private:
        ofstream fout;
    public:
        void openOutputFile(string filename){
            try{
                fout.open(filename, ios::out|ios::app|ios::binary);
            }catch(FileNotFoundException e){
                cerr<<e.what()<<endl;
            }
        }
        void writeDataToFile(User user){
            fout.write((char*)& user, sizeof(User));
        }
        void closeOutputFile(){
            fout.close();
        }

        ifstream openInputFile(string filename){
            ifstream fin;
            try{
                fin.open(filename, ios::in|ios::binary);
            }catch(FileNotFoundException e){
                cerr<<e.what()<<endl;
            }
            return fin;
        }
        
};