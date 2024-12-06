//
// Created by mziya on 12/6/2024.
//
#include "SIndex.h"
#include "bits/stdc++.h"

using namespace std;
SIndex::SIndex() {
    loadFileToVector(appointmentFile, appointmentIdx);
    loadFileToVector(doctorFile, doctorIdx);
    
    sort(appointmentIdx.begin(), appointmentIdx.end());
    sort(doctorIdx.begin(), doctorIdx.end());
}

void SIndex::loadFileToVector(const string& filename, vector<pair<string, vector<string>>>& indexVec) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        string key;
        getline(stream, key, '|');
        
        vector<string> values;
        string value;
        while (getline(stream, value, ',')) {
            if (!value.empty()) {
                values.push_back(value);
            }
        }
        
        indexVec.push_back({key, values});
    }
    
    file.close();
}

void SIndex::saveToFile(const string& filename, const vector<pair<string, vector<string>>>& indexVec) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    
    for (const auto& entry : indexVec) {
        if(entry.second.empty()) continue;
        file << entry.first << "|";  // Write the key
        for (size_t i = 0; i < entry.second.size(); ++i) {
            file << entry.second[i];  // Write the values
            if (i != entry.second.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }
    file.close();
}

void SIndex::printDoctorIndex() const {
    for (const auto &entry : doctorIdx) {
        cout << "Doctor Name: " << entry.first << ", Doctor IDs: ";
        for (const auto &doctorID : entry.second) {
            cout << doctorID << " ";
        }
        cout << endl;
    }
}

void SIndex::printAppointmentIndex() const {
    for (const auto &entry : appointmentIdx) {
        cout << "Appointment ID: " << entry.first << ", Doctor IDs: ";
        for (const auto &doctorID : entry.second) {
            cout << doctorID << " ";
        }
        cout << endl;
    }
}

const vector<pair<string, vector<string>>>& SIndex::getAppointmentIndex() const {
    return appointmentIdx;
}

const vector<pair<string, vector<string>>>& SIndex::getDoctorIndex() const {
    return doctorIdx;
}

void SIndex::addNewDoctor(string doctorName , string Id ) {
    
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

void SIndex:: addNewApponitment(string DoctorId , string AppointmentId ){
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

void SIndex::updateDoctorName(string id,string newname,string oldname) {
    vector<pair<string,vector<string>>>idxdata;
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

vector<string> SIndex::search_by_doctor_name(const string &name)
{
    int start = 0;
    int end = doctorIdx.size() - 1;
    vector<string> doctorIDs;
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

vector<string> SIndex::search_by_doctor_id(const string &doctorID)
{
    vector<string> appIDs;
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

bool SIndex::delete_doctor_name(const string &name ,const string &doctorID )
{
    vector<string>matchedIDs = search_by_doctor_name(name);
    if(matchedIDs.empty())
    {
        return false;
    }
    // sequential search
    auto it = remove(matchedIDs.begin(), matchedIDs.end(), doctorID);
    matchedIDs.erase(it, matchedIDs.end());
    
    
    auto idxIt = std::find_if(doctorIdx.begin(), doctorIdx.end(),
                              [&name](const std::pair<std::string, std::vector<std::string>>& entry) {
                                  return entry.first == name;
                              });
    idxIt->second = matchedIDs;
    
    // sucess delete
    saveToFile(doctorFile , doctorIdx) ;
    return true;
}

bool SIndex::delete_doctor_appointment(const string &appointmentId ,const string &doctorId)
{
    vector<string>matchedAppointmentIDs = search_by_doctor_id(doctorId);
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
