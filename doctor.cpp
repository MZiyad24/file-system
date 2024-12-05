#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "primaryIndex.cpp"
#include "secondaryIndex.cpp"
using namespace std;

class Doctor{
private:
    char id [15];
    char name [30];
    char address [30];
    PrimaryIndex px;
    SecondaryIndex sx;
    AvaiList avl;

public:
    Doctor(const string& prim_filename="doctor_primary_index.txt",const string& sec_filename="doctor_secondary_index.txt"):px() , sx(){}
    
    void set_id(char* id){
        assert(sizeof(id)<sizeof(this->id));
        strcpy(this->id,id);
    }
    char* get_id(){
        return id;
    }
    
    void set_name(char* name){
        assert(sizeof(name)<sizeof(this->name));
        strcpy(this->name,name);
    }
    char* get_name(){
        return name;
    }
    
    void set_address(char* address){
        assert(sizeof(address)<sizeof(this->address));
        strcpy(this->address,address);
    }
    char* get_address(){
        return address;
    }
    
    //add
    void add(char* id, char * name, char* address){
        /*
         * Check data size integrity
         * Check AVAIL list
         * if(true)
         * {
         *      get offset from AVAIL list
         *      pop AVAIL LIST
         * }
         * else
         * {
         *      get offset from data file
         *      add doctor to doctor vector
         *      save file
         *      add doctor to primary index
         *      add doctor to secondary index
         * }
         * */
    }
    
    //delete
    void Delete(char * id){
        /*
         * char * offset = px.delete(id);
         * if( offset != (char*)'-1')
         * {
         *      search in doctor file for the offset
         *      get the name and mark as deleted
         *      use the name and id to delete from secondary idx
         *      add the offset to the AVAIL list
         *      update doctor vector
         * }
         * */
    }
    //update
    void updata_docName(char* ID,char* newname) {
        string oldname = this->name;
        strcpy(this->name,newname);
        //update the secondary index
        sx.updateDoctorName(ID,newname,oldname);
        //load the docror file into vector
        vector<pair<string,vector<string>>>docfile;
        ifstream file("doctor.txt");
        if (!file.is_open()) {
            cerr << "Error opening file: " << "doctor.txt" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            istringstream stream(line);
            string key;
            getline(stream, key, '|');

            vector<string> values;
            string value;
            while (getline(stream, value, '|')) {
                if (!value.empty()) {
                    values.push_back(value);
                }
            }

            docfile.push_back({key, values});
        }

        file.close();
        //
        // Loop through the docfile and update the length
        for (auto& entry : docfile) {
            string length = entry.first; // Get the length indicator of the record
            vector<string>& record = entry.second;

            if (record[0] == ID) { // Check  the ID
                int oldLength = stoi(length);
                int diff = strlen(newname) - strlen(oldname.c_str());
                int newLength = oldLength + diff;

                // Update the length in the record
                entry.first = to_string(newLength);
                break;
            }
        }
        // save it ,load vector back int doctor file
        ofstream File("doctor.txt", ios::trunc);
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << "doctor.txt"<< endl;
            return;
        }

        for (const auto& entry : docfile) {
            File << entry.first << "|";  // Write the key
            for (size_t i = 0; i < entry.second.size(); ++i) {
                File << entry.second[i];  // Write the values
                if (i != entry.second.size() - 1) {
                    File << ",";
                }
            }
            File << endl;
        }
        File.close();

    }
    
    //print info
    void print(){
        /*
         * loop the vector and print all the doctor data
         * */
    }
    
    //search
    void search(char * id)
    {
        /*
         *  Binary search the vector for the id and print the doctor info
         * */
    }
};
