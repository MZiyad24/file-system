//
// Created by mziya on 12/6/2024.
//

#ifndef FILES_ASSIGNMENT_APP_H
#define FILES_ASSIGNMENT_APP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include "PIndex.h"
#include "SIndex.h"

class App {
private:
    char id[15];
    char date[30];
    char doctor_id[15];
    char* offset;
    int length_indicator;
    std::fstream file;
    PIndex px;
    SIndex sx;
    AvaiList avl;
    
    std::vector<std::pair<std::pair<std::pair<int, char*>, std::pair<char*, char*>>, char*>> app_data;
    
    void load();
    void save();

public:
    App(const std::string& prim_filename = "appointment_primary_index.txt",
                const std::string& sec_filename = "appointment_secondary_index.txt");
    
    void set_id(char* id);
    char* get_id();
    
    void set_date(char* date);
    char* get_date();
    
    void add(char* id, char* date, char* doctor_id);
    void Delete(char* id);
    void Delete_by_Doctor(char* doctor_id);
    void update_appDate(char* appId, char* newDate);
    void print();
    void search(char* id);
    
    std::pair<int, int> calc(char* id, char* date, char* doc_id);
};


#endif //FILES_ASSIGNMENT_APP_H
