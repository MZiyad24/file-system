//
// Created by mziya on 12/6/2024.
//
#include "App.h"
#include "bits/stdc++.h"
using namespace std;

App::App(const string& prim_filename, const string& sec_filename)
        : px(), sx() {}
        

void App::add(char* id, char * date, char* doctor_id){
    // px . search doctor
    int check = px.search_appointment(id);
    if(check!= -1)
    {
        cout<<"appointment already exists!!!! \n";
        file.close();
        return;
    }
    int offset = avl.get();
    int size = strlen(id)+ strlen(date) + strlen(doctor_id);
    string ssize = to_string(size);
    sx.addNewApponitment(doctor_id, id);
    if (offset == -1) {
        file.open("appointment.txt",ios::in|ios::out|ios::app);
        string iddd = id;
        string Name = date;
        string Address = doctor_id;
        file << size << "|" << iddd << "|" << Name << "|"<<Address<<"\n";
        file.close();
        px.add_appointment(id, calc());
        
    }
    else
    {
        file.open("appointment.txt",ios::in|ios::out|ios::app);
        //px.add_doctor(id,offset);
        file.seekp(offset,ios::beg);
        file << size << '|' << id <<'|' << date << '|' <<doctor_id <<"\n";
        file.close();
    }

//    int offset = px.search_doctor(doctor_id);
//    if(offset !=-1)
//    {
//        file.open("appointment.txt",ios::out|ios::trunc);
//        int check = px.search_appointment(id);
//        if(check!= -1)
//        {
//            cout<<"doctor already exists!!!! \n";
//            return;
//        }
//        int offset = avl.get();
//        if(file.is_open()) {
//            int size = sizeof(id)+sizeof(date)+sizeof(doctor_id);
//            sx.addNewApponitment(doctor_id,id);
//            if (offset == -1) {
//                px.add_appointment(id,calc());
//                file.seekp(0, ios::end);
//                file << size << '|' << id <<'|' << date << '|' <<doctor_id <<"\n";
//            }
//            else
//            {
//                px.add_appointment(id,offset);
//                file.seekp(offset,ios::beg);
//                file << size << '|' << id <<'|' << date << '|' <<doctor_id <<"\n";
//            }
//            file.close();
//        }
//    }
    
    
    //---------------
//    int doc_offset=px.search_doctor(doctor_id);
//    if(doc_offset==-1)
//    {
//        cerr<<"doctor doesn't exist!!\n";
//        return;
//    }
//
//    int offset=avl.get();
//    pair<int,int> data_nums;
//    data_nums=calc(id,date,doctor_id);
//    if(offset==-1)
//    {
//        app_data.push_back(make_pair(make_pair(make_pair(data_nums.first,id), make_pair(date,doctor_id)),(char*)&data_nums.second));
//    }
//    else
//    {
//        int start = 0; // binary search
//        int end = (int)app_data.size() - 1;
//        int location=-1;
//
//        while (start <= end)
//        {
//            int mid = (start + end) / 2;
//
//            if (strcmp(app_data[mid].second, (char*)&offset) == 0)
//            {
//                app_data[mid]=make_pair(make_pair(make_pair(data_nums.first,id), make_pair(date,doctor_id)),(char*)&offset);
//                location = mid;
//                break;
//            }
//            else if (strcmp(app_data[mid].second, (char*)&offset) < 0)
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
//            for(int i=location+1;i<(int)app_data.size()-1;i++)
//            {
//                offset+=app_data[i-1].first.first.first;
//                app_data[i].second=(char*)&offset;
//            }
//        }
//    }
//    save();
//    px.add_appointment(id,offset);
//    sx.addNewApponitment(doctor_id,id);
    
    /*
     * Check app id from primary index search
     * Check AVAIL list
     * if(true)
     * {
     *      get offset from AVAIL list
     *      pop AVAIL LIST
     * }
     * else
     * {
     *      get offset from data file
     *      add app to app vector
     *      save file
     *      add app to primary index
     *      add app to secondary index
     * }
     * */
}

void App::Delete(char* id){     ////////////// cast all strings to char * !!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /*
     * char * offset = px.delete(id);
     * if( offset != (char*)'-1')
     * {
     *      search in appointment file for the offset
     *      get the doc_id and mark as deleted
     *      use the doc_id and id to delete from secondary idx
     *      add the offset to the AVAIL list
     *      update appointment vector
     * }
     * */
    
    char * offset;
    strcpy(offset,px.delete_appointment(id));
    if(strcmp(offset,"-1") !=0)
    {
        file.open("appointment.txt",ios::in | ios::out | ios::trunc);
        if(file.is_open())
        {
            file.seekg(stoi(string(offset)),ios::beg);
            file.getline(this->id,'|');
            file.seekp(file.tellg(),ios::beg);
            file << "deleted";
            file.getline(this->id,'|');
            file.getline(date,'|');
            
            sx.delete_doctor_appointment(id,doctor_id);
            avl.add(stoi(string(offset)));
            file.close();
        }
        assert(file.is_open());
    }
//
//    char * offset = px.delete_appointment(id);
//    if(strcmp(offset,(char*)"-1")!=0)
//    {
//        // deleted from px and got the offset
//        load();
//        int start = 0; // binary search
//        int end = (int)app_data.size() - 1;
//        char*doctor_id;
//
//        // search for the offset and delete from file
//        while (start <= end)
//        {
//            int mid = (start + end) / 2;
//
//            if (strcmp(app_data[mid].second, (char*)&offset) == 0)
//            {
//                strcpy(app_data[mid].first.first.second,(char*)"deleted");
//                strcpy(doctor_id,app_data[mid].first.second.second);
//                break;
//            }
//            else if (strcmp(app_data[mid].second, (char*)&offset) < 0)
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
//        // delete from secondary index
//        sx.delete_doctor_appointment(id,doctor_id);
//        save();
//    }
}

void App::Delete_by_Doctor(char*doctor_id){
    vector<string> apIDs;
    apIDs=sx.search_by_doctor_id(doctor_id);
    if((int)apIDs.size()>0)
    {
        for(const auto &entry:apIDs)
        {
            Delete((char*)&entry);
        }
    }
    /*
     * delete by sec index
     * return offset use it in primary
     * delete from data file
     * */
}

void App::update_appDate(char* appId,char* newDate) {
    int offset=px.search_appointment(appId);
    file.open("appointment.txt",ios::in | ios::out | ios::trunc);
    assert(file.is_open());
    if(file.is_open())
    {
        file.seekg(offset,ios::beg);
        char* length;
        file.getline(length,'|');
        file.getline(id,'|');
        int pos = file.tellg();
        file.getline(date,'|');
        file.seekp(pos,ios::beg);
        file << newDate;
        
        int newOffset = calc();
        px.update_appointment(appId,newOffset);
        sx.updateDoctorName(string(appId),string(newDate),string(doctor_id));
        calc();
    }
    
    
    
//    string oldDate;
//    vector<pair<string, vector<string>>> appointmentFile;
//
//    // Load the appointment file into a vector
//    ifstream file("appointment.txt");
//    if (!file.is_open()) {
//        cerr << "Error opening file: " << "appointment.txt" << endl;
//        return;
//    }
//
//    string line;
//    while (getline(file, line)) {
//        istringstream stream(line);
//        string length;
//        getline(stream, length, '|');
//
//        vector<string> values;
//        string value;
//        while (getline(stream, value, '|')) {
//            if (!value.empty()) {
//                values.push_back(value);
//            }
//        }
//
//        appointmentFile.push_back({length, values});
//    }
//
//    file.close();
//
//    // Loop of  the appointment file and update the length and date
//    for (auto& entry : appointmentFile) {
//        string length = entry.first; // Get the length indicator of the record
//        vector<string>& record = entry.second;
//
//        if (record[0] == appId) { // Check if the ID matches
//            oldDate = record[1]; // Store the old date
//            int oldLength = stoi(length);
//            int diff = strlen(newDate) - strlen(oldDate.c_str());
//            int newLength = oldLength + diff;
//
//            // Update the length and date in the record
//            entry.first = to_string(newLength);
//            record[1] = newDate;
//            break;
//        }
//    }
//
//    // Save the updated vector back to the appointment file
//    ofstream outFile("appointment.txt", ios::trunc);
//    if (!outFile.is_open()) {
//        cerr << "Error opening file for writing: " << "appointment.txt" << endl;
//        return;
//    }
//
//    for (const auto& entry : appointmentFile) {
//        outFile << entry.first << "|"; // Write the length
//        for (size_t i = 0; i < entry.second.size(); ++i) {
//            outFile << entry.second[i]; // Write the values
//            if (i != entry.second.size() - 1) {
//                outFile << "|";
//            }
//        }
//        outFile << endl;
//    }
//
//    outFile.close();
}

void App::print (){
    /*
    * loop the vector and print all the appointment data
    * */
    file.open("appointment.txt",ios::in);
    assert(file.is_open());
    file.seekg(0,ios::end);
    char* length;
    if(file.tellg()!=-1)
    {
        while(file.good())
        {
            file.getline(length,'|');
            file.getline(id,'|');
            file.getline(date,'|');
            file.getline(doctor_id,'|');
            cout<<"Appointment ID: "<<id<<" "
                <<"Date: "<<date <<" "
                <<"Doctor ID: "<<doctor_id<<"\n";
        }
    }
    else
        cout<<"no appointment to show\n";
}

void App::search(char * id)
{
    /*
     *  Binary search the vector for the id and print the appointment info
     * */
    cout<<"The appointments for the doctor with this ID "<<id<<" are: \n";
    vector<string>ans = sx.search_by_doctor_id(id);
    for(auto&entry : ans)
    {
        cout<<entry<<" ";
    }
    cout<<"\n";
}

int App::calc(){
    file.open("appointment.txt" , ios::in | ios::out);
    if(file.is_open()) {
        avl.clear();
        string line;
        int currentOffset=0;
        int rowLength=0;
        while (getline(file, line)) {
            istringstream stream(line);
            string tempLength;
            string id;
            rowLength=0;
            getline(stream, tempLength, '|');
            stringstream (tempLength)>>rowLength;
            getline(stream, id, '|');
            if (id == "deleted") {
                avl.add(currentOffset);
            } else {
                //px.update_doctor((char *) &id, currentOffset);
            }
            currentOffset += rowLength;
        }
        file.close();
        return currentOffset-rowLength;
    }
}  // calculates the length indicator and offset
