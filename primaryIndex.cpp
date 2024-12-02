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
    
    //1-add
    
    //2-delete
    
    //3-update
    
    //4-print info
    
    //5-search
    
    // 2 print + delete (primary , sec ) , 2 add , 2 update , 2 search
};
