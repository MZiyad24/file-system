#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>  
using namespace std;

class SecondaryIndex {
private:
    vector<pair<string, vector<string>>> appointmentIdx; 
    vector<pair<string, vector<string>>> doctorIdx;       
    const string appointmentFile = "appointment_secondary_index.txt";
    const string doctorFile = "doctor_secondary_index.txt";

    void loadFileToVector(const string& filename, vector<pair<string, vector<string>>>& indexVec) {
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
    void saveToFile(const string& filename, const vector<pair<string, vector<string>>>& indexVec) {
        ofstream file(filename, ios::trunc); 
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto& entry : indexVec) {
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

    const vector<pair<string, vector<string>>>& getAppointmentIndex() const {
        return appointmentIdx;
    }

    const vector<pair<string, vector<string>>>& getDoctorIndex() const {
        return doctorIdx;
    }
    // addNewDoctor() // do not forget saveToFile()
    // addNewApponitment() // do not forget saveToFile()
    // deletApponitment()  // do not forget saveToFile() using avail List
    //  deletDoctor()  // do not forget saveToFile()   using avail List
    // updateDoctorName() // do not forget saveToFile()
    void updateDoctorName(string id,string newname,string oldname) {
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

    // searchByName()
    //  make for loop on matching Ids = this name and call searchById() for primary index

};