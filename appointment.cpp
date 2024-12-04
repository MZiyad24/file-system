#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "primaryIndex.cpp"
#include "secondaryIndex.cpp"
using namespace std;

class Appointment{
private:
    char id [15];
    char date [30];
    char doctor_id [15];
    PrimaryIndex px;
    SecondaryIndex sx;

public:
    Appointment(const string& prim_filename="appointment_primary_index.txt",const string& sec_filename="appointment_secondary_index.txt"):px(),sx(){}
    
    void set_id(char* id){
        assert(sizeof(id)<sizeof(this->id));
        strcpy(this->id,id);
    }
    char* get_id(){
        return id;
    }
    
    void set_date(char* date){
        assert(sizeof(date)<sizeof(this->date));
        strcpy(this->date,date);
    }
    char* get_date(){
        return date;
    }
    
//    void set_doctor_id(char* doctor_id){
//        assert(sizeof(doctor_id)<sizeof(this->doctor_id));
//        strcpy(this->doctor_id,doctor_id);
//    }
//    char* get_doctor_id(){
//        return doctor_id;
//    }
    
    //add
    
    //delete
    
    //update
    
    //print info
    
    //search
};
