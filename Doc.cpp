//
// Created by mziya on 12/6/2024.
//
#include "Doc.h"
#include "bits/stdc++.h"
using namespace std;

Doc::Doc(const string& prim_filename, const string& sec_filename) : px(), sx() {}

void Doc::add(char* id, char * name, char* address){
    
    file.open("doctor.txt",ios::out|ios::trunc);
    int check = px.search_doctor(id);
    if(check!= -1)
    {
        cout<<"doctor already exists!!!! \n";
        return;
    }
    int offset = avl.get();
    if(file.is_open()) {
        int size = sizeof(id)+sizeof(name)+sizeof(address);
        sx.addNewDoctor(name,id);
        if (offset == -1) {
            px.add_doctor(id,calc());
            file.seekp(0, ios::beg);
            file << size << '|' << id <<'|' << name << '|' <<address <<"\n";
        }
        else
        {
            px.add_doctor(id,offset);
            file.seekp(offset,ios::beg);
            file << size << '|' << id <<'|' << name << '|' <<address <<"\n";
        }
        file.close();
    }
//
//    int doc_search = px.search_doctor(id);
//    if(doc_search !=-1)
//    {
//        cout<<"doctor already exists!!\n";
//        return;
//    }
//    int offset = avl.get();
//    pair<int,int> data_nums;
//    data_nums=calc(id,name,address);
//    if(offset==-1)  // no place in AVAIL list
//    {
//        doc_data.push_back(make_pair(make_pair(make_pair(data_nums.first,id), make_pair(name,address)),(char*)&data_nums.second));
//    }
//    else
//    {
//
//        int start = 0; // binary search
//        int end = (int)doc_data.size() - 1;
//        int location=-1;
//
//        while (start <= end)
//        {
//            int mid = (start + end) / 2;
//
//            if (strcmp(doc_data[mid].second, (char*)&offset) == 0)
//            {
//                doc_data[mid]=make_pair(make_pair(make_pair(data_nums.first,id), make_pair(name,address)),(char*)&offset);
//                location = mid;
//                break;
//            }
//            else if (strcmp(doc_data[mid].second, (char*)&offset) < 0)
//            {
//                start = mid + 1;
//            }
//            else
//            {
//                end = mid - 1;
//            }
//        }
//
//        if(location != -1)
//        {
//            for(int i=location+1;i<(int)doc_data.size()-1;i++)
//            {
//                offset+=doc_data[i-1].first.first.first;
//                doc_data[i].second=(char*)&offset;
//            }
//        }
//
//
//    }
//    save();
//    px.add_doctor(id,data_nums.second);
//    sx.addNewDoctor(name,id);
    
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

void Doc::Delete(char * id){
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
    char * offset;
    strcpy(offset,px.delete_doctor(id));
    if(strcmp(offset,"-1") !=0)
    {
        file.open("doctor.txt",ios::in | ios::out | ios::trunc);
        if(file.is_open())
        {
            file.seekg(stoi(string(offset)),ios::beg);
            file.getline(this->id,'|');
            file.seekp(file.tellg(),ios::beg);
            file << "deleted";
            file.getline(this->id,'|');
            file.getline(name,'|');
            
            sx.delete_doctor_name(name,id);
            avl.add(stoi(string(offset)));
            app.Delete_by_Doctor(id);
            file.close();
        }
        assert(file.is_open());
    }
    
//    char * offset = px.delete_doctor(id);
//    if(strcmp(offset,(char*)"-1")!=0)
//    {
//        // deleted from px and got the offset
//        load();
//        int start = 0; // binary search
//        int end = (int)doc_data.size() - 1;
//        char* name;
//
//        // search for the offset and delete from file
//        while (start <= end)
//        {
//            int mid = (start + end) / 2;
//
//            if (strcmp(doc_data[mid].second, (char*)&offset) == 0)
//            {
//                strcpy(doc_data[mid].first.first.second,(char*)"deleted");
//                strcpy(name,doc_data[mid].first.second.first);
//                break;
//            }
//            else if (strcmp(doc_data[mid].second, (char*)&offset) < 0)
//            {
//                start = mid + 1;
//            }
//            else
//            {
//                end = mid - 1;
//            }
//        }
//        int avail_off = stoi(string(offset));
//
//        // add to AVAIL list
//        avl.add(avail_off);
//
//        // delete from appointment file
//        app.Delete_by_Doctor(id);
//
//        // delete from secondary index
//        sx.delete_doctor_name(name,id);
//        save();
//    }
}

void Doc::updata_docName(char* ID,char* newname) {
    /*
     * search by id for the old name
     * change name
     * calc offset
     * change px
     * change sx
     * */
    int offset=px.search_doctor(ID);
    file.open("doctor.txt",ios::in | ios::out | ios::trunc);
    assert(file.is_open());
    if(file.is_open())
    {
        file.seekg(offset,ios::beg);
        char* length;
        file.getline(length,'|');
        file.getline(id,'|');
        int pos = file.tellg();
        file.getline(name,'|');
        file.seekp(pos,ios::beg);
        file << newname;
        
        int newOffset = calc();
        px.update_doctor(ID,newOffset);
        sx.updateDoctorName(string(ID),string(newname),string(name));
        calc();
    }
    
//    string oldname = this->name;
//    strcpy(this->name,newname);
//    //update the secondary index
//    sx.updateDoctorName(ID,newname,oldname);
//    //load the docror file into vector
//    vector<pair<string,vector<string>>>docfile;
//    ifstream file("doctor.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening file: " << "doctor.txt" << endl;
//        return;
//    }
//    string line;
//    while (getline(file, line)) {
//        istringstream stream(line);
//        string key;
//        getline(stream, key, '|');
//
//        vector<string> values;
//        string value;
//        while (getline(stream, value, '|')) {
//            if (!value.empty()) {
//                values.push_back(value);
//            }
//        }
//
//        docfile.push_back({key, values});
//    }
//
//    file.close();
//    //
//    // Loop through the docfile and update the length
//    for (auto& entry : docfile) {
//        string length = entry.first; // Get the length indicator of the record
//        vector<string>& record = entry.second;
//
//        if (record[0] == ID) { // Check  the ID
//            int oldLength = stoi(length);
//            int diff = strlen(newname) - strlen(oldname.c_str());
//            int newLength = oldLength + diff;
//
//            // Update the length in the record
//            entry.first = to_string(newLength);
//            break;
//        }
//    }
//    // save it ,load vector back int doctor file
//    ofstream File("doctor.txt", ios::trunc);
//    if (!file.is_open()) {
//        cerr << "Error opening file for writing: " << "doctor.txt"<< endl;
//        return;
//    }
//
//    for (const auto& entry : docfile) {
//        File << entry.first << "|";  // Write the key
//        for (size_t i = 0; i < entry.second.size(); ++i) {
//            File << entry.second[i];  // Write the values
//            if (i != entry.second.size() - 1) {
//                File << ",";
//            }
//        }
//        File << endl;
//    }
//    File.close();
//
}

void Doc::print(){
    /*
     * loop the vector and print all the doctor data
     * */
    file.open("doctor.txt",ios::in);
    assert(file.is_open());
    file.seekg(0,ios::end);
    char* length;
    if(file.tellg()!=-1)
    {
        while(file.good())
        {
            file.getline(length,'|');
            file.getline(id,'|');
            file.getline(name,'|');
            file.getline(address,'|');
            cout<<"Doctor ID: "<<id<<" "
                <<"Name: "<<name <<" "
                <<"Address ID: "<<address<<"\n";
        }
    }
    else
        cout<<"no Doctors to show\n";
}

void Doc::search(char * name)
{
    /*
     *  Binary search the vector for the id and print the doctor info
     * */
    vector<string>ans;
    ans=sx.search_by_doctor_name(name);
    cout<<"The IDs associated with the name "<<name<<"are: \n";
    for(auto&entry: ans){
        cout<<entry << " ";
    }
    cout<<"\n";
    
}

int Doc::calc() {
    file.open("doctor.txt",ios::in);
    if(file.is_open()) {
        avl.clear();
        string line;
        int currentOffset=0;
        while (getline(file, line)) {
            istringstream stream(line);
            string tempLength;
            string id;
            int rowLength = stoi(tempLength);
        
            getline(stream, tempLength, '|');
            getline(stream, id, '|');
            if(id=="deleted")
            {
                avl.add(currentOffset);
            }
            else {
                px.update_doctor((char *) &id, currentOffset);
            }
            currentOffset += rowLength;
        }
        file.close();
        return currentOffset;
    }
    assert(file.is_open());
}
/*
 * int ans=0;
        while(file.good()) {
            char *length;
            file.getline(length, '|');
            int temp = stoi(string(length));
            file.seekg(temp, ios::cur);
            ans+=temp;
        }
    }*/

