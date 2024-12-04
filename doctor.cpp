#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "primaryIndex.cpp"
#include "secondaryIndex.cpp"
using namespace std;

class Doctor{
private:
    char id [15];
    char name [30];
    char address [30];
    PrimaryIndex px;
    SecondaryIndex sx;

public:
    Doctor(const string& prim_filename="doctor_primary_index.txt",const string& sec_filename="doctor_secondary_index.txt"):px() , sx(){}
    
    void set_id(char* id){
        assert(sizeof(id)<sizeof(this->id));
        strcpy(this->id,id);
    }
    char* get_id(){
        return id;
    }
    
    void set_name(char* name){
        assert(sizeof(name)<sizeof(this->name));
        strcpy(this->name,name);
    }
    char* get_name(){
        return name;
    }
    
    void set_address(char* address){
        assert(sizeof(address)<sizeof(this->address));
        strcpy(this->address,address);
    }
    char* get_address(){
        return address;
    }
    
    //add
    
    //delete
    
    //update
    
    //print info
    
    //search
};
