#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "AvaiList.h"

using namespace std;

class PrimaryIndex{
private:
    fstream file,file2;
    vector<pair<char*,int>>doc_idx;
    vector<pair<char*,int>>app_idx;
    AvaiList doctor_avillist ;
    AvaiList appointment_availlist ;

    
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
    PrimaryIndex(){
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
//    void Delete(char*key)
//    {
//        int offset;
//        char entry [15];
//        int record_size = sizeof(entry)+sizeof(offset)+1;
//        file.seekg(0,ios::beg);
//        int file_size=file.tellg();
//        int num_of_records=file_size/record_size;
//        int first =0 , last=num_of_records-1 , mid;
//        bool found = false;
//        while (first<=last)
//        {
//            mid = (int) first + (last - first)/2;
//            file.seekg(mid*record_size,ios::beg); // getting the middle record
//            file.read((char*)&entry,sizeof(entry));
//            file.ignore(1); // delimiter
//            file.read((char*)&offset,sizeof(offset));
//
//            if(strcmp(entry,key)==0) // they are the same
//            {
//                found=true;
//                break;
//            }
//            else
//            {
//                if(strcmp(entry,key)<0) // key is bigger
//                {
//                    first=mid+1;
//                }
//                else
//                {
//                    last= mid-1;
//                }
//            }
//        }
//        if(!found) cerr<<"record isn't available! \n";
//        else
//        {
//            // push to avail list
//            file.seekp(offset,ios::beg);
//            file.write((char*)"00", sizeof(entry));
//            int deleted_offset = -1;
//            file.write((char*)deleted_offset, sizeof(offset));
//
//        }
//    }

    //4-print info
    void print_doctor(){
    
    }
    
    void print_app();
    // Awad test push
    //5-search
    int search_doctor(const char *id)
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
    
    ~PrimaryIndex(){
        if(file.is_open())this->file.close();
        if(file2.is_open())this->file2.close();
    }
   
};
