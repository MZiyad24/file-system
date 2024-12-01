#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
using namespace std;

class PrimaryIndex{
private:
    fstream file;
    map<char* , int > idx;

public:
    PrimaryIndex(const string& filename){
        file.open(filename,ios::in | ios::out);
    }
    
    ~PrimaryIndex(){
        this->file.close();
    }
    
    //add
    
    //delete
    
    //update
    
    //print info
    
    //search
};
