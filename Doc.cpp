//
// Created by mziya on 12/6/2024.
//
#include "Doc.h"
#include "bits/stdc++.h"
using namespace std;

Doc::Doc(const string& prim_filename, const string& sec_filename) : px(), sx() {}

void Doc::add(char* id, char * name, char* address){
    
    file.open("C:\\Users\\mziya\\OneDrive\\Desktop\\files-assignment\\cmake-build-debug\\doctor.txt",ios::in|ios::out|ios::app);
    int check = px.search_doctor(id);
    if(check!= -1)
    {
        cout<<"doctor already exists!!!! \n";
        file.close();
        return;
    }
    int offset = avl.get();
        int size = strlen(id)+ strlen(name) + strlen(address);
        string ssize = to_string(size);
        sx.addNewDoctor(name, id);
        if (offset == -1) {
            string iddd = id;
            string Name = name;
            string Address = address;
            file << size;
            file << "|";
            file << iddd;
            file << "|";
            file << Name;
            file << "|";
            file<<Address ;
            file<<"\n";
            file.close();
            px.add_doctor(id, calc());
        }
        else
        {
            //px.add_doctor(id,offset);
            file.seekp(offset,ios::beg);
            file << size << '|' << id <<'|' << name << '|' <<address <<"\n";
            file.close();
        }
    
    //file.close();
    
    

    
    
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
        file.open("doctor.txt",ios::app);
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
        }
        assert(file.is_open());
        file.close();
    }
 
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
    file.close();
 
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
    file.close();
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
    file.open("doctor.txt",ios::in | ios::out);
    if(file.is_open()) {
        avl.clear();
        string line;
        int currentOffset=0;
        if (file.peek() != std::ifstream::traits_type::eof()) {
            while (getline(file, line)) {
                istringstream stream(line);
                string tempLength;
                string id;
                int rowLength;
                getline(stream, tempLength, '|');
                stringstream (tempLength)>>rowLength;
                getline(stream, id, '|');
                if (id == "deleted") {
                    avl.add(currentOffset);
                } else {
                    px.update_doctor((char *) &id, currentOffset);
                }
                currentOffset += rowLength;
            }
        }
        return currentOffset;
    }
    file.close();
    
}
