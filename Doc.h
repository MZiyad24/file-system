//
// Created by mziya on 12/6/2024.
//

#ifndef FILES_ASSIGNMENT_DOC_H
#define FILES_ASSIGNMENT_DOC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include "PIndex.h"
#include "SIndex.h"
#include "App.h"
#include "avaiList.h"

using namespace std;

class Doc {
private:
    char id[15];
    char name[30];
    char address[30];
    int length_indicator;
    char* offset;
    fstream file;
    PIndex px;
    SIndex sx;
    App app;
    AvaiList avl;
    
    vector<pair<pair<pair<int, char*>, pair<char*, char*>>, char*>> doc_data;
    
    void load();
    void save();
    pair<int, int> calc(char* id, char* name, char* address);

public:
    Doc(const string& prim_filename = "doctor_primary_index.txt", const string& sec_filename = "doctor_secondary_index.txt");
    
    void set_id(char* id);
    char* get_id();
    
    void set_name(char* name);
    char* get_name();
    
    void set_address(char* address);
    char* get_address();
    
    void add(char* id, char* name, char* address);
    void Delete(char* id);
    void updata_docName(char* ID, char* newname);
    void print();
    void search(char* id);
};


#endif //FILES_ASSIGNMENT_DOC_H
