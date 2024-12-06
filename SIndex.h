//
// Created by mziya on 12/6/2024.
//

#ifndef FILES_ASSIGNMENT_SINDEX_H
#define FILES_ASSIGNMENT_SINDEX_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "AvaiList.h"
using namespace std;
class SIndex {
private:
    vector<pair<string, vector<string>>> appointmentIdx;
    vector<pair<string, vector<string>>> doctorIdx;
    const string appointmentFile = "appointment_secondary_index.txt";
    const string doctorFile = "doctor_secondary_index.txt";
    AvaiList Doc_Avail;
    AvaiList Appointment_Avail;
    
    void loadFileToVector(const string &filename, vector<pair<string, vector<string>>> &indexVec);
    void saveToFile(const string &filename, const vector<pair<string, vector<string>>> &indexVec);

public:
    SIndex();
    void printDoctorIndex() const;
    void printAppointmentIndex() const;
    const vector<pair<string, vector<string>>>& getAppointmentIndex() const;
    const vector<pair<string, vector<string>>>& getDoctorIndex() const;
    
    void addNewDoctor(string doctorName, string Id);
    void addNewApponitment(string DoctorId, string AppointmentId);
    
    void updateDoctorName(string id, string newname, string oldname);
    vector<string> search_by_doctor_name(const string &name);
    vector<string> search_by_doctor_id(const string &doctorID);
    
    bool delete_doctor_name(const string &name, const string &doctorID);
    bool delete_doctor_appointment(const string &appointmentId, const string &doctorId);
};

#endif //FILES_ASSIGNMENT_SINDEX_H
