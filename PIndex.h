//
// Created by mziya on 12/6/2024.
//

#ifndef FILES_ASSIGNMENT_PINDEX_H
#define FILES_ASSIGNMENT_PINDEX_H
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
using namespace std;

class PIndex {
private:
    fstream file, file2;
    vector<pair<char*, int>> doc_idx;
    vector<pair<char*, int>> app_idx;
    
    void loadFile(string name);
    void save(string filename);
public:
    PIndex();
    vector<pair<char*, int>> get_doc_idx();
    vector<pair<char*, int>> get_app_idx();
    void add_doctor(char* id, int offset);
    void add_appointment(char* id, int offset);
    char* delete_doctor(char* id);
    char* delete_appointment(char* id);
    void print_doctor();
    void print_app();
    void update_doctor(char*id , int offset);
    void update_appointment(char*id , int offset);
    int search_doctor(const char* id);
    int search_appointment(const char* id);
    ~PIndex();
};

#endif //FILES_ASSIGNMENT_PINDEX_H
