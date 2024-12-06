#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "AvaiList.h"

using namespace std;

class PIndex{
private:
    fstream file,file2;
    vector<pair<char*,int>>doc_idx;
    vector<pair<char*,int>>app_idx;
//    AvaiList doctor_avillist ;
//    AvaiList appointment_availlist ;

    void loadFile(){
        file.open("doctor_primary_index.txt",ios::in | ios::out);
        if(file.is_open()) {
            char entry[15];
            int offset;
            file.seekg(0, ios::beg);
            file.seekp(0, ios::beg);
            while (file.good()) {
                file.read((char *) &entry, sizeof(entry));
                file.ignore(1);
                file.read((char *) &offset, sizeof(offset));
                doc_idx.push_back(make_pair(entry, offset));
            }
        }
        assert(file.is_open());
        file2.open("appointment_primary_index.txt",ios::in|ios::out);
        if(file2.is_open()) {
            char entry[15];
            int offset;
            file2.seekg(0, ios::beg);
            file2.seekp(0, ios::beg);
            while (file2.good()) {
                file2.read((char *) &entry, sizeof(entry));
                file2.ignore(1);
                file2.read((char *) &offset, sizeof(offset));
                app_idx.push_back(make_pair(entry, offset));
            }
        }
        assert(file2.is_open());
        file.close();
        file2.close();
    }
    void save(){  // don't forget using this after each function
        file.seekp(0,ios::beg);
        file2.seekp(0,ios::beg);
        for(int i=0;i<(int)doc_idx.size();i++)
        {
            file.write((char*)&doc_idx[i].first,sizeof(doc_idx[i].first));
            char del = '|';
            file.write((char*)&del,sizeof(del));
            file.write((char*)&doc_idx[i].second,sizeof(doc_idx[i].second));
        }
        for(int i=0;i<(int)app_idx.size();i++)
        {
            file.write((char*)&app_idx[i].first,sizeof(app_idx[i].first));
            char del = '|';
            file.write((char*)&del,sizeof(del));
            file.write((char*)&app_idx[i].second,sizeof(app_idx[i].second));
        }
    }
public:
    PIndex(){
        loadFile();
        sort(doc_idx.begin(),doc_idx.end());
        sort(app_idx.begin(),app_idx.end());
    }
    
    vector<pair<char*,int>> get_doc_idx()
    {
        return doc_idx;
    }
    
    
    vector<pair<char*,int>> get_app_idx()
    {
        return app_idx;
    }
    
    
    //1-add

    void add_doctor(char* id , int offset) {
        if (search_doctor(id) != -1){
            cout << "Doctor already found" ;
            return;
        }

        doc_idx.emplace_back(make_pair(id, offset));
        sort(doc_idx.begin(), doc_idx.end(), [](const pair<char*, int>& a, const pair<char*, int>& b) {
            return strcmp(a.first, b.first) < 0;
        });
        save();
    }

    void add_appointment(char* id, int offset) {
        if (search_appointment(id) != -1){
            cout << "Appointment Found";
            return;
        }
        app_idx.emplace_back(make_pair(id, offset));
        sort(app_idx.begin(), app_idx.end(), [](const pair<char*, int>& a, const pair<char*, int>& b) {
            return strcmp(a.first, b.first) < 0;
        });
        save();
    }
    
    //2-delete
    char* delete_doctor(char* id)  // returning offset as char *
    {
        char* offset = reinterpret_cast<char*>(search_doctor(id));
        string err = "-1";
        if( offset!=(char*)&err)
        {
            int start = 0; // binary search
            int end = doc_idx.size() - 1;
    
            while (start <= end)
            {
                int mid = (start + end) / 2;
        
                if (strcmp(doc_idx[mid].first, id) == 0)
                {
                    if(doc_idx[0].first!=id)
                    {
                        doc_idx[mid].first=(char*)"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";
                        sort(doc_idx.begin(),doc_idx.end());
                    }
                    doc_idx.pop_back();
                    save();
                    return offset;
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
        else
        {
            cerr<<"doctor doesn't exist!\n";
            
        }
        return offset;
    }
    
    char* delete_appointment(char* id)  // returning offset as char *
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

    //4-print info
    void print_doctor(){
        for(const auto & entry : doc_idx)
        {
            cout<<"Doctor's ID: "<<entry.first
                <<" Offset: "<<entry.second<<"\n";
        }
        
    }
    
    void print_app(){
        for(const auto & entry : app_idx)
        {
            cout<<"Doctor's ID: "<<entry.first
                <<" Offset: "<<entry.second<<"\n";
        }
    };
    
    //5-search
    int search_doctor(const char *id)  // returning offset as int
    {
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

    int search_appointment(const char *id)
    {
        int start = 0;                
        int end = app_idx.size() - 1; 

        while (start <= end)
        {
            int mid = (start + end) / 2; 

            if (strcmp(app_idx[mid].first, id) == 0)
            {
                return app_idx[mid].second; //  offset
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
    
    ~PIndex(){
        if(file.is_open())this->file.close();
        if(file2.is_open())this->file2.close();
    }
   
};
