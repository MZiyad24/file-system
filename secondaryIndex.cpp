#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
using namespace std;

class SecondaryIndex{
private:
    fstream file;
    // map of <char* , linked list >

public:
    SecondaryIndex(string file){
        this->file.open(file,ios::in | ios::out);
    }
    
    ~SecondaryIndex(){
        this->file.close();
    }
    
    //add
    
    //delete
    
    //update
    
    //print info
    
    //search
};
