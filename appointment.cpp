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

    void update_appDate(char* appId,char* newDate) {
    string oldDate;
    vector<pair<string, vector<string>>> appointmentFile;

    // Load the appointment file into a vector
    ifstream file("appointment.txt");
    if (!file.is_open()) {
        cerr << "Error opening file: " << "appointment.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string length;
        getline(stream, length, '|');

        vector<string> values;
        string value;
        while (getline(stream, value, '|')) {
            if (!value.empty()) {
                values.push_back(value);
            }
        }

        appointmentFile.push_back({length, values});
    }

    file.close();

    // Loop of  the appointment file and update the length and date
    for (auto& entry : appointmentFile) {
        string length = entry.first; // Get the length indicator of the record
        vector<string>& record = entry.second;

        if (record[0] == appId) { // Check if the ID matches
            oldDate = record[1]; // Store the old date
            int oldLength = stoi(length);
            int diff = strlen(newDate) - strlen(oldDate.c_str());
            int newLength = oldLength + diff;

            // Update the length and date in the record
            entry.first = to_string(newLength);
            record[1] = newDate;
            break;
        }
    }

    // Save the updated vector back to the appointment file
    ofstream outFile("appointment.txt", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing: " << "appointment.txt" << endl;
        return;
    }

    for (const auto& entry : appointmentFile) {
        outFile << entry.first << "|"; // Write the length
        for (size_t i = 0; i < entry.second.size(); ++i) {
            outFile << entry.second[i]; // Write the values
            if (i != entry.second.size() - 1) {
                outFile << "|";
            }
        }
        outFile << endl;
    }

    outFile.close();
    }
    
    //print info
    
    //search
};
