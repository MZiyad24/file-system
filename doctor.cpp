#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "primaryIndex.cpp"
#include "secondaryIndex.cpp"
#include "appointment.cpp"
using namespace std;

class Doctor{
private:
    char id [15];
    char name [30];
    char address [30];
    int length_indicator;
    char * offset;
    fstream file;
    PIndex px;
    SecondaryIndex sx;
    Appointment app;
    AvaiList avl;
    vector<pair<pair<pair<int,char*>,pair<char*,char*>>,char*>> doc_data ;
    // vector < pair< pair<pair<length , id>,pair<name,address>>,offset>>
    void load()
    {
        file.open("doctor.txt",ios::in|ios::out|ios::binary);
        assert(file.is_open());
        file.seekg(0,ios::beg);
        while(file.good())
        {
            file.read((char*)&length_indicator, sizeof(length_indicator));
            file.ignore(1);
            file.read((char*)&id, sizeof(id));
            file.ignore(1);
            file.read((char*)&name, sizeof(name));
            file.ignore(1);
            file.read((char*)&address, sizeof(address));
            file.ignore(1);
            file.read((char*)&offset, sizeof(int));
            doc_data.push_back(make_pair(make_pair(make_pair(length_indicator,id), make_pair(name,address)),offset));
        }
        file.close();
        
    }
    void save()
    {
        file.open("doctor.txt",ios::in|ios::out);
        assert(file.is_open());
        file.seekp(0,ios::beg);
        for(auto &entry : doc_data)
        {
            file.write((char*)&entry.first.first.first, sizeof(length_indicator));
            char del='|';
            file.write((char*)&del, sizeof(del));
            file.write((char*)&entry.first.first.second, sizeof(id));
            file.write((char*)&del, sizeof(del));
            file.write((char*)&entry.first.second.first, sizeof(name));
            file.write((char*)&del, sizeof(del));
            file.write((char*)&entry.first.second.second, sizeof(address));
            file.write((char*)&del, sizeof(del));
            file.write((char*)&entry.second,sizeof(int));
            file<< "\n";
        }
        file.close();
    }

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
        load();
        int offset = avl.get();
        pair<int,int> data_nums;
        data_nums=calc(id,name,address);
        if(offset==-1)  // no place in AVAIL list
        {
            doc_data.push_back(make_pair(make_pair(make_pair(data_nums.first,id), make_pair(name,address)),(char*)&data_nums.second));
        }
        else
        {
            
            int start = 0; // binary search
            int end = (int)doc_data.size() - 1;
            int location=-1;
    
            while (start <= end)
            {
                int mid = (start + end) / 2;
        
                if (strcmp(doc_data[mid].second, (char*)&offset) == 0)
                {
                    doc_data[mid]=make_pair(make_pair(make_pair(data_nums.first,id), make_pair(name,address)),(char*)&offset);
                    location = mid;
                    break;
                }
                else if (strcmp(doc_data[mid].second, (char*)&offset) < 0)
                {
                    start = mid + 1;
                }
                else
                {
                    end = mid - 1;
                }
            }
            
            if(location != -1)
            {
                for(int i=location+1;i<(int)doc_data.size()-1;i++)
                {
                    offset+=doc_data[i-1].first.first.first;
                    doc_data[i].second=(char*)&offset;
                }
            }
            
            
        }
        save();
        px.add_doctor(id,data_nums.second);
        sx.addNewDoctor(name,id);
        
        /*
         * Check data size integrity
         * Check AVAIL list
         * if(true)
         * {
         *      get the offset from AVAIL
         *      search for the offset
         *      add the data in that offset location in the vector
         *      calculate the new offsets
         * }
         * else
         * {
         *      get offset from data file
         *      add doctor to doctor vector
         *
         * }
         *      save file
         *      add doctor to primary index
         *      add doctor to secondary index
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
         *      call search by doctor to the appointment
         * }
         * */
        
        char * offset = px.delete_doctor(id);
        if(strcmp(offset,(char*)'-1')!=0)
        {
            // deleted from px and got the offset
            load();
            int start = 0; // binary search
            int end = (int)doc_data.size() - 1;
            char* name;
            
            // search for the offset and delete from file
            while (start <= end)
            {
                int mid = (start + end) / 2;
        
                if (strcmp(doc_data[mid].second, (char*)&offset) == 0)
                {
                    strcpy(doc_data[mid].first.first.second,(char*)'deleted');
                    strcpy(name,doc_data[mid].first.second.first);
                    break;
                }
                else if (strcmp(doc_data[mid].second, (char*)&offset) < 0)
                {
                    start = mid + 1;
                }
                else
                {
                    end = mid - 1;
                }
            }
            int avail_off = stoi(offset);
            
            // add to AVAIL list
            avl.add(avail_off);
            
            // delete from appointment file
            app.Delete_by_Doctor(id);
            
            // delete from secondary index
            sx.delete_doctor_name(name,id);
            save();
        }
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
        if (doc_data.size()>0)
        for(auto&entry:doc_data)
        {
            cout<<"length: "<<entry.first.first.first<<" "
                <<"Doctor ID: "<<entry.first.first.second<<" "
                <<"Doctor Name: "<<entry.first.second.first<<" "
                <<"Doctor's address: "<<entry.first.second.second<<" "
                <<"offset: "<<entry.second<<"\n";
        }
        else
            cout<<"No doctors to show\n";
    }
    
    //search
    void search(char * id)
    {
        /*
         *  Binary search the vector for the id and print the doctor info
         * */
    }
    
    pair<int,int> calc(char* id, char * name, char* address){
        int length = sizeof(id)+ sizeof(name)+ sizeof(address);
        int offset;
        if((int)doc_data.size()==0)
        {
            offset = 0;
        }
        else{
            int past_length = doc_data[(int)doc_data.size()-1].first.first.first;
            offset = stoi(doc_data[(int)doc_data.size()-1].second);
            offset+=past_length;
        }
        return make_pair(length,offset);
    }
};
