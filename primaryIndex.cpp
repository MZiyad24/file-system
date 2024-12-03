#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
using namespace std;

class PrimaryIndex{
private:
    fstream file;
    map<char* , int> idx;
    

public:
    PrimaryIndex(const string& filename){
        file.open(filename,ios::in | ios::out);
        assert(!file.is_open());
    }
    
    
    ~PrimaryIndex(){
        this->file.close();
    }
    
    //1-add
    
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
    
    //3-update
    
    //4-print info
    
    //5-search
    
    // 2 print + delete (primary , sec ) , 2 add , 2 update , 2 search
};
