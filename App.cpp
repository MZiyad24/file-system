//
// Created by mziya on 12/6/2024.
//
#include "App.h"
#include "bits/stdc++.h"
using namespace std;

App::App(const string& prim_filename, const string& sec_filename){}
        

void App::add(char* id, char * date, char* doctor_id){
    int doctorId = px.search_doctor(doctor_id);
    if(doctorId == -1)
    {
        cout<<"Doctor Don not exists \n";
        return;

    }
    int check = px.search_appointment(id);
    if(check!= -1)
    {
        cout<<"appointment already exists!!!! \n";
        return;
    }
    int offset = avl.get();
    int size = strlen(id)+ strlen(date) + strlen(doctor_id)+3+sizeof(int);
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
        file.open("appointment.txt",ios::in|ios::out);
        file.seekg(offset,ios::beg);
        string lng="";
        getline(file,lng);
        vector<string>row=split(lng,'|');
        if(size> stoi(row[0]))
        {
            cout<<"The entered record's size is too large to fit the deleted one \n";
            string iddd = id;
            string Name = date;
            string Address = doctor_id;
            file << size << "|" << iddd << "|" << Name << "|"<<Address<<"\n";
            file.close();
            px.add_appointment(id, calc());
        }
        else {
            int diff = stoi(row[0])-size;
            string s ="";
            for(int i =0 ;i<diff ; i++)
            {
                s+=' ';
            }
            px.add_appointment(id,offset);
            file.seekp(offset,ios::beg);
            file << size << '|' << id << '|' << date << '|' << doctor_id << s << "\n";
        }
        file.close();
    }
}

void App::Delete(char* id){
    char * offset = new char [ 15 ];
    strcpy(offset,px.delete_appointment(id));
    if(strcmp(offset,"-1") !=0)
    {
        file.open("appointment.txt",ios::in | ios::out);
        if(file.is_open())
        {
            string temp = offset;
            int ser;
            stringstream ss(temp);
            ss >> ser;
            file.seekg(ser, ios::beg);
            string line;
            getline(file, line);
            vector<string>row=split(line,'|');
            string ID = row[1];
            string DATE = row[2];
            string DOC_ID = row[3];
            string LENGTH = row[0];
            int len = strlen("*") + (int)DATE.size()+ (int)DOC_ID.size()+3+sizeof(int);
            file.seekp(ser, ios::beg);
            file << len << '|' <<"*" <<'|'<< DATE <<'|'<< DOC_ID;
            file.close();
            sx.delete_doctor_appointment( id,DOC_ID);
            avl.add(ser);
        }
        delete [] offset;
    }
    
}

void App::Delete_by_Doctor(char*doctor_id){
    vector<string> apIDs;
    apIDs=sx.search_by_doctor_id(doctor_id);
    if((int)apIDs.size()>0)
    {
        for(auto entry:apIDs)
        {
            Delete(entry.data());
        }
    }
}

void App::update_appDate(char* appId,char* newDate) {
    
    if(strlen(newDate)>10 || strlen(newDate)<10)
    {
        cout<<"invalid date!!!!!\n";
        return;
    }
    int offset=px.search_appointment(appId);
    file.open("appointment.txt",ios::in | ios::out );
    if(file.is_open()) {
        file.seekg(offset, ios::beg);
        string line = "";
        getline(file,line);
        vector<string> lines = split(line,'|');
        file.seekp(offset+ sizeof(int)+(int)lines[1].size(), ios::beg);
        file << newDate;
    }
        file.close();
}

void App::print() {

    ifstream file("appointment.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open appointment.txt file\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> fields = split(line, '|');
        if (fields.size() == 4) {
            cout << "Appointment ID: " << fields[1]
                 << " Date: " << fields[2]
                 << " Doctor: " << fields[3] << "\n";
        } else {
            cerr << "Error: Malformed line: " << line << "\n";
        }
    }

    if (file.eof()) {
        cout << "All appointments displayed.\n";
    } else if (file.fail()) {
        cerr << "Error: Read failure.\n";
    }

    file.close();
}

vector<string> App::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void App::search(char * id)
{
    cout<<"The appointments for the doctor with this ID "<<id<<" are: \n";
    vector<string>ans = sx.search_by_doctor_id(id);
    for(auto&entry : ans)
    {
        cout<<entry<<" ";
    }
    cout<<"\n";
}

void App::search_by_docId(const char *id) {
    vector<string>ans;
    ans=sx.search_by_doctor_id(id);
    for(auto&entry: ans){
        const char* DocId_cstr = entry.c_str();
        int off=px.search_appointment(DocId_cstr);
        file.open("appointment.txt",ios::in|ios::out);
        file.seekg(off,ios::beg);
        string lin ="";
        getline(file,lin);
        vector<string>line = split(lin,'|');
        cout<<"Appointment ID : "<<line[1]<<"   Appointment Date : "<<line[2]<<"   Doctor ID : "<<line[3]<<"\n";
        file.close();
    }
    cout<<"\n";
}

void App::search_byAppId(const char * id)
{
    int off=px.search_appointment(id);
    file.open("appointment.txt",ios::in|ios::out);
    file.seekg(off,ios::beg);
    string lin ="";
    getline(file,lin);
    vector<string>line = split(lin,'|');
    cout<<"Appointment ID : "<<line[1]<<"   Appointment Date : "<<line[2]<<"   Doctor ID : "<<line[3]<<"\n";
    file.close();
}

void App::search_byDate(const char *id) {
    int off=px.search_appointment(id);
    file.open("appointment.txt",ios::in|ios::out);
    file.seekg(off,ios::beg);
    string lin ="";
    getline(file,lin);
    vector<string>line = split(lin,'|');
    cout<<"Appointment Date : "<<line[2]<<"\n";
    file.close();
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
            if (id == "*") {
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
