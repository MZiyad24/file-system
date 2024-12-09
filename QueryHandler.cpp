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
    if (query.find("select all from doctors where doctor id") != string::npos) {
        string doctorID = extractValue(query, "doctor id");
        const char* doctorID_cstr = doctorID.c_str();
        doctor.search_byId(doctorID_cstr);
    }else if (query.find("select all from doctors where doctor Name") != string::npos) {
        string doctorName = extractValue(query, "doctor name");
        const char* doctorName_cstr = doctorName.c_str();
        doctor.search_byName(doctorName_cstr);
    }else if (query.find("select all from appointments where appointment id") != string::npos) {
        string AppointmentID = extractValue(query, "appointment id");
        const char* AppointmentID_cstr = AppointmentID.c_str();
        appointment.search_byAppId(AppointmentID_cstr);
    }else if (query.find("select all from appointments where doctor id") != string::npos) {
        string doctorID = extractValue(query, "doctor id");
        const char* doctorID_cstr = doctorID.c_str();
        appointment.search_by_docId(doctorID_cstr);
        
    } else if (query.find("select doctor name from doctors where doctor id") != string::npos) {
        string doctorID = extractValue(query, "doctor id");
        const char* doctorID_cstr = doctorID.c_str();
        doctor.getName_byId(doctorID_cstr);
    }else if (query.find("select address from doctors where doctor id") != string::npos) {
        string doctorID = extractValue(query, "doctor id");
        const char* doctorID_cstr = doctorID.c_str();
        doctor.getAdress_byId(doctorID_cstr);
        
    }else if (query.find("select date from appointments where appointment id") != string::npos) {
        string doctorID = extractValue(query, "appointment id");
        const char* doctorID_cstr = doctorID.c_str();
        appointment.search_byDate(doctorID_cstr);
        
    }else {
        cout << "Invalid query!" << endl;
    }
}