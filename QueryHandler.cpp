#include "QueryHandler.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to extract value (where key='value')
string extractValue(const string &query, const string &key) {
    size_t pos = query.find(key + "='");
    if (pos != string::npos) {
        size_t start = pos + key.length() + 2; // Skip key='
        size_t end = query.find("'", start);
        return query.substr(start, end - start);
    }
    return "";
}

// Constructor
QueryHandler::QueryHandler() : doctor(), appointment() {}


void QueryHandler::handle(const string &query) {
    if (query.find("Select all from Doctors where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        char* doctorID_cstr = doctorID.c_str();
    //  doctor.search_byId(doctorID_cstr);
    }else if (query.find("Select all from Doctors where Doctor Name") != string::npos) {
        string doctorName = extractValue(query, "Doctor Name");
        char* doctorName_cstr = doctorName.c_str();
        //doctor.search_byName(doctorName_cstr);
    }else if (query.find("Select all from Appointments where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        char* doctorID_cstr = doctorID.c_str();
        // appointment.search_by_docId(doctorID_cstr);


    } else if (query.find("Select Doctor Name from Doctors where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        char* doctorID_cstr = doctorID.c_str();
        //doctor.getName_byId(doctorID_cstr);
    }else if (query.find("Select Address from Doctors where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        char* doctorID_cstr = doctorID.c_str();
        //doctor.getAdress_byId(doctorID_cstr);

    }else {
        cout << "Invalid query!" << endl;
    }
}
