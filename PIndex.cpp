//
// Created by mziya on 12/6/2024.
//
#include "PIndex.h"
#include "bits/stdc++.h"

using namespace std;

void PIndex::loadFile(string name){
    string line;
    if(name=="doctor") {
        doc_idx.clear();
        file.open("doctor_primary_index.txt", ios::in);
       
        while (getline(file, line)) {
            if ((int) line.size() == 0)break;
            istringstream stream(line);
            string key, off;
            getline(stream, key, '|');
            getline(stream, off, '|');
            char *entry = new char[key.size() + 1];
            strcpy(entry, key.c_str());
            doc_idx.push_back({entry, stoi(off)});
        
        }
        file.close();
    }
    else {
        app_idx.clear();
        file2.open("appointment_primary_index.txt", ios::in);
        while (getline(file2, line)) {
            if ((int) line.size() == 0)break;
            istringstream stream(line);
            string key, off;
            getline(stream, key, '|');
            getline(stream, off, '|');
            char *entry = new char[key.size() + 1];
            strcpy(entry, key.c_str());
            app_idx.push_back({entry, stoi(off)});
        }
        file2.close();
    }
}

void PIndex::save(){  // don't forget using this after each function
    
    
    if(!doc_idx.empty()) {
        file.open("doctor_primary_index.txt",ios::out);
        for (auto &entry: doc_idx) {
            string id = entry.first;
            file << id << '|' << entry.second << "\n";
        }
        file.close();
    }
    
    if(!app_idx.empty()) {
        file2.open("appointment_primary_index.txt",ios::out);
        for (auto &entry: app_idx) {
            file2 << entry.first << '|' << entry.second << "\n";
        }
        file2.close();
    }
    
    
}

PIndex::PIndex(){}

vector<pair<char*, int>> PIndex::get_doc_idx()
{
    return doc_idx;
}

vector<pair<char*, int>> PIndex::get_app_idx()
{
    return app_idx;
}

void PIndex::add_doctor(char* id , int offset) {
    char * ID = new char [15];
    strcpy(ID,id);
    doc_idx.emplace_back(make_pair(ID, offset));

    sort(doc_idx.begin(), doc_idx.end(), [](const pair<char*, int>& a, const pair<char*, int>& b) {
        return strcmp(a.first, b.first) < 0;
    });
    save();
}

void PIndex::add_appointment(char* id, int offset) {
    app_idx.emplace_back(make_pair(id, offset));
    sort(app_idx.begin(), app_idx.end(), [](const pair<char*, int>& a, const pair<char*, int>& b) {
        return strcmp(a.first, b.first) < 0;
    });
    save();
}

char* PIndex::delete_doctor(char* id)  // returning offset as char *
{
    int awad = search_doctor(id);
    char* offset = new char [ 15 ];
    string zft = to_string(awad);
    strcpy(offset, zft.c_str());
    auto err = NULL;
    if( offset!=(char*)&err)
    {
        for (auto it = doc_idx.begin(); it != doc_idx.end(); ++it) {
            if (strcmp(it->first, id) == 0) {
                delete[] it->first;
                doc_idx.erase(it);
                break;
            }
        }
    }
    else
    {
        cerr<<"doctor doesn't exist!\n";
        
    }
    return offset;
}

char* PIndex::delete_appointment(char* id)  // returning offset as char *
{
    char* offset = reinterpret_cast<char*>(search_appointment(id));
    string err = "-1";
    if( offset!=(char*)&err)
    {
        int start = 0; // binary search
        int end = app_idx.size() - 1;
        
        while (start <= end)
        {
            int mid = (start + end) / 2;
            
            if (strcmp(app_idx[mid].first, id) == 0)
            {
                if(app_idx[0].first!=id)
                {
                    app_idx[mid].first=(char*)"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
                    sort(app_idx.begin(),app_idx.end());
                }
                app_idx.pop_back();
                save();
                return offset;
            }
            else if (strcmp(app_idx[mid].first, id) < 0)
            {
                start = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }
    }
    else
    {
        cerr<<"Appointment doesn't exist!\n";
    }
    return offset;
}

void PIndex::print_doctor() {
    for (const auto& entry : doc_idx) {
        cout << "Doctor's ID: " << entry.first << " Offset: " << entry.second << "\n";
    }
}

void PIndex::print_app(){
    for(const auto & entry : app_idx)
    {
        cout<<"Doctor's ID: "<<entry.first
            <<" Offset: "<<entry.second<<"\n";
    }
};

int PIndex::search_doctor(const char *id)  // returning offset as int
{
    loadFile("doctor");
    if((int)doc_idx.size()==0)
    {
        return -1;
    }
    int start = 0; // binary search
    int end = doc_idx.size() - 1;
    
    while (start <= end)
    {
        int mid = (start + end) / 2;
        
        if (strcmp(doc_idx[mid].first, id) == 0)
        {
            return doc_idx[mid].second; // offset
        }
        else if (strcmp(doc_idx[mid].first, id) < 0)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return -1;
}

void PIndex::update_doctor(char *id, int offset) {
    int start = 0; // binary search
    int end = doc_idx.size() - 1;
    
    while (start <= end)
    {
        int mid = (start + end) / 2;
        
        if (strcmp(doc_idx[mid].first, id) == 0)
        {
            doc_idx[mid].second = offset; // offset
            return;
        }
        else if (strcmp(doc_idx[mid].first, id) < 0)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    
}

void PIndex::update_appointment(char *id, int offset) {
    int start = 0; // binary search
    int end = app_idx.size() - 1;
    
    while (start <= end)
    {
        int mid = (start + end) / 2;
        
        if (strcmp(app_idx[mid].first, id) == 0)
        {
            app_idx[mid].second = offset; // offset
            return;
        }
        else if (strcmp(app_idx[mid].first, id) < 0)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    
}

int PIndex::search_appointment(const char *id)
{
    loadFile("app");
    if((int)app_idx.size()==0)
    {
        return -1;
    }
    int start = 0; // binary search
    int end = app_idx.size() - 1;
    
    while (start <= end)
    {
        int mid = (start + end) / 2;
        
        if (strcmp(app_idx[mid].first, id) == 0)
        {
            return app_idx[mid].second; // offset
        }
        else if (strcmp(app_idx[mid].first, id) < 0)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return -1;
}

PIndex::~PIndex(){
}
