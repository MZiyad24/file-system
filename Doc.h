
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
    fstream Dfile;
    PIndex px;
    SIndex sx;
    App app;
    AvaiList avl;
    

public:
    Doc(const string& prim_filename = "doctor_primary_index.txt", const string& sec_filename = "doctor_secondary_index.txt");
    void search_byId(char * id);
    int calc();
    void add(char* id, char* name, char* address);
    void Delete(char* id);
    void updata_docName(char* ID, char* newname);
    void print();
    vector<string> split(const string& str, char delimiter);
    void search(char* id);// edit this to fitch the record
    // make search by name function that fetch the record 
    // make search by id function that fetch the adress 
   // make search by id function that fetch the name 
};


#endif //FILES_ASSIGNMENT_DOC_H
