#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "primaryIndex.cpp"
#include "AvaiList.h"
using namespace std;

class SecondaryIndex {
private:
    vector<pair<char*, vector<char*>>> appointmentIdx; 
    vector<pair<char*, vector<char*>>> doctorIdx;       
    const string appointmentFile = "appointment_secondary_index.txt";
    const string doctorFile = "doctor_secondary_index.txt";
    AvaiList Doc_Avail ;
    AvaiList Appointment_Avail ;
    PrimaryIndex primaryIndex;



    void loadFileToVector(const string& filename, vector<pair<char*, vector<char*>>>& indexVec) 
    {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream stream(line);

            string key_str;
            getline(stream, key_str, '|');  
            char* key = strdup(key_str.c_str());  
            vector<char*> values;
            string value_str;
            while (getline(stream, value_str, ',')) {  
                if (!value_str.empty()) {
                    char* value = strdup(value_str.c_str());  
                    values.push_back(value);
                }
            }

            indexVec.push_back({key, values});
        }

        file.close();
    }



    void saveToFile(const string& filename, const vector<pair<char*, vector<char*>>>& indexVec) {
        ofstream file(filename, ios::trunc); 
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto& entry : indexVec) {
            if(entry.second.empty()) continue;
            file << entry.first << "|";  
            for (size_t i = 0; i < entry.second.size(); ++i) {
                file << entry.second[i];  
                if (i != entry.second.size() - 1) {
                    file << ",";
                }
            }
            file << endl;
        }
        file.close();
    }

public:
    SecondaryIndex() {
        loadFileToVector(appointmentFile, appointmentIdx);  
        loadFileToVector(doctorFile, doctorIdx);          

        sort(appointmentIdx.begin(), appointmentIdx.end());
        sort(doctorIdx.begin(), doctorIdx.end());
    }

    void printDoctorIndex() const {
        for (const auto& entry : doctorIdx) {
            cout << "Doctor Name: " << entry.first << ", Doctor IDs: ";
            for (const auto& doctorID : entry.second) {
                cout << doctorID << " ";
            }
            cout << endl;
        }
    }

    void printAppointmentIndex() const {
        for (const auto& entry : appointmentIdx) {
            cout << "Appointment ID: " << entry.first << ", Doctor IDs: ";
            for (const auto& doctorID : entry.second) {
                cout << doctorID << " ";
            }
            cout << endl;
        }
    }

    const vector<pair<char*, vector<char*>>>& getAppointmentIndex() const {
        return appointmentIdx;
    }

    const vector<pair<char*, vector<char*>>>& getDoctorIndex() const {
        return doctorIdx;
    }
    void addNewDoctor(char* doctorName , char* Id ) {

        auto it = find_if(doctorIdx.begin(), doctorIdx.end(),
                          [&doctorName](const pair<string, vector<string>>& entry) {
                              return entry.first == doctorName;
                          });

        if (it != doctorIdx.end()) {
            it->second.push_back(Id);
        }
        else
        {
                doctorIdx.emplace_back(make_pair(doctorName , vector<string>{Id}));
        }

        sort(doctorIdx.begin(), doctorIdx.end(), [](const pair<string, vector<string>>& a, const pair<string, vector<string>>& b) {
            return a.first < b.first;
        });


        saveToFile(doctorFile , doctorIdx);

    }

    // do not forget saveToFile()
    void addNewApponitment(char* DoctorId , char* AppointmentId ){
        auto it = find_if(appointmentIdx.begin(), appointmentIdx.end(),
                          [&DoctorId](const pair<string, vector<string>>& entry) {
                              return entry.first == DoctorId;

        });
        if (it != appointmentIdx.end()) {
            it->second.push_back(AppointmentId);
        }

        else
        {
            appointmentIdx.emplace_back(make_pair(DoctorId , vector<string>{AppointmentId}));
        }

        sort(appointmentIdx.begin(), appointmentIdx.end(), [](const pair<string, vector<string>>& a, const pair<string, vector<string>>& b) {
            return a.first < b.first;
        });


        saveToFile(appointmentFile , appointmentIdx);


    } // do not forget saveToFile()
    // deletApponitment()  // do not forget saveToFile() using avail List
    //  deletDoctor()  // do not forget saveToFile()   using avail List
    // updateDoctorName() // do not forget saveToFile()
    void updateDoctorName(char* id,char* newname,char* oldname) {
        vector<pair<char*,vector<char*>>>idxdata;
        loadFileToVector(doctorFile, idxdata);//load the index file to vector
        for (auto it = idxdata.begin(); it != idxdata.end(); ++it) {
            if (it->first == oldname) {
                if (it->second.size() == 1) { // Check if there's only one ID
                    idxdata.erase(it); // Remove the entire entry
                    break;
                } else {
                    // Loop through IDs to find and delete the specific one
                    for (auto idIt = it->second.begin(); idIt != it->second.end(); ++idIt) {
                        if (*idIt == id) {
                            it->second.erase(idIt); // Remove the ID is assosiated
                            break;
                        }
                    }
                    break;
                }
            }
            else {
                cout<<"the doctor not found\n";
                return;
            }

        }
        bool newnameExists = false;
        for (auto &entry: idxdata) {
            if (entry.first == newname) {
                entry.second.push_back(id); // Add id to the existing newname
                newnameExists = true;
                break;
            }
        }

        // if newname doesn't existit will create a new entry
        if (!newnameExists) {
            idxdata.push_back({newname, {id}});
        }
        saveToFile(doctorFile, idxdata);// save it back to doctor index file
    }

    // at doctor_secondary_index
    vector<char*> search_by_doctor_name(const char* &name)
    {
        int start = 0;                  
        int end = doctorIdx.size() - 1; 
        vector<char*> doctorIDs;
        while (start <= end)
        {
            int mid = (start + end) / 2; 

            if (doctorIdx[mid].first == name)
            {
                doctorIDs = doctorIdx[mid].second;
                break;
            }
            else if (doctorIdx[mid].first < name)
            {
                start = mid + 1; 
            }
            else
            {
                end = mid - 1; 
            }
        }
        // return vector of doctor IDs
        return doctorIDs;

        return {}; 
    }

    // at appointment_secondary_index 
    vector<char*> search_by_doctor_id(const char* &doctorID)
    {
        vector<char*> appIDs;
        int start = 0;                       
        int end = (int)appointmentIdx.size() - 1;

        while (start <= end)
        {
            int mid = (start + end) / 2; 
            if (appointmentIdx[mid].first == doctorID)
            {
                appIDs = appointmentIdx[mid].second;
                break;
            }
            else if (appointmentIdx[mid].first < doctorID)
            {
                start = mid + 1; 
            }
            else
            {
                end = mid - 1; 
            }
        }
        return appIDs;
    }
    
    // at doctor_secondary_index
    // this function return true if successfully deleted , false if not found
    bool delete_doctor_name(const char* &name ,const char* &doctorID )
    {
        vector<char*>matchedIDs = search_by_doctor_name(name);
        if(matchedIDs.empty())
        {
            return false;
        }
        // sequential search 
        auto it = remove(matchedIDs.begin(), matchedIDs.end(), doctorID);
        matchedIDs.erase(it, matchedIDs.end());


        auto idxIt = find_if(doctorIdx.begin(), doctorIdx.end(),
        [&name](const pair<char*, vector<char*>>& entry) {
            return entry.first == name;
        });
        idxIt->second = matchedIDs;

        // sucess delete
        saveToFile(doctorFile , doctorIdx) ;       
        return true;
    }
    // at doctor_secondary_index
    // this function return true if successfully deleted , false if not found
    bool delete_doctor_appointment(const char* &appointmentId ,const char* &doctorId)
    {
        vector<char*>matchedAppointmentIDs = search_by_doctor_id(doctorId);
        if(matchedAppointmentIDs.empty())
        {
            return false;
        }
        auto it = remove(matchedAppointmentIDs.begin(), matchedAppointmentIDs.end(), appointmentId);
        matchedAppointmentIDs.erase(it, matchedAppointmentIDs.end());


        auto idxIt = find_if(appointmentIdx.begin(), appointmentIdx.end(),
        [&doctorId](const pair<string, vector<string>>& entry) {
            return entry.first == doctorId;
        });
        idxIt->second = matchedAppointmentIDs;

        // sucess delete
        saveToFile(appointmentFile, appointmentIdx) ;       
        return true;
    }
};
