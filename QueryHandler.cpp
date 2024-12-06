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
QueryHandler::QueryHandler() : primaryIndex(), secondaryIndex() {}


void QueryHandler::printDoctorDetails(int offset) {
    // Fetch the doctor record using offset (file handling to be implemented)
    cout << "Doctor record at offset: " << offset << endl;
}


void QueryHandler::printAppointmentDetails(int offset) {
    // Fetch the appointment record using offset (file handling to be implemented)
    cout << "Appointment record at offset: " << offset << endl;
}


void QueryHandler::handle(const string &query) {
    if (query.find("Select all from Doctors where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        int offset = primaryIndex.search_doctor(doctorID.c_str());
        if (offset != -1) {
            printDoctorDetails(offset);
        } else {
            cout << "Doctor ID not found!" << endl;
        }
    } else if (query.find("Select all from Appointments where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        vector<string> appointmentIDs = secondaryIndex.search_by_doctor_id(doctorID);
        if (!appointmentIDs.empty()) {
            for (const string &appointmentID : appointmentIDs) {
                int offset = primaryIndex.search_appointment(appointmentID.c_str());
                if (offset != -1) {
                    printAppointmentDetails(offset);
                }
            }
        } else {
            cout << "No appointments found for Doctor ID: " << doctorID << endl;
        }
    } else if (query.find("Select Doctor Name from Doctors where Doctor ID") != string::npos) {
        string doctorID = extractValue(query, "Doctor ID");
        int offset = primaryIndex.search_doctor(doctorID.c_str());
        if (offset != -1) {
            //  function to fetch just the Doctor Name using offset
            cout << "Doctor Name fetched from offset: " << offset << endl;
        } else {
            cout << "Doctor ID not found!" << endl;
        }
    } else if (query.find("Select all from Doctors where Doctor Name") != string::npos) {
        string doctorName = extractValue(query, "Doctor Name");
        vector<string> doctorIDs = secondaryIndex.search_by_doctor_name(doctorName);
        if (!doctorIDs.empty()) {
            for (const string &doctorID : doctorIDs) {
                int offset = primaryIndex.search_doctor(doctorID.c_str());
                if (offset != -1) {
                    printDoctorDetails(offset);
                }
            }
        } else {
            cout << "No doctors found with Name: " << doctorName << endl;
        }
    } else {
        cout << "Invalid query!" << endl;
    }
}
