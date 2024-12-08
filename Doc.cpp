//
// Created by mziya on 12/6/2024.
//
#include "Doc.h"
#include "bits/stdc++.h"
using namespace std;

Doc::Doc(const string& prim_Dfilename, const string& sec_Dfilename) : px(), sx() {}

void Doc::add(char* id, char * name, char* address){
    int check = px.search_doctor(id);
    if(check!= -1)
    {
        cout<<"doctor already exists!!!! \n";
        Dfile.close();
        return;
    }
    int offset = avl.get();
        int size = strlen(id)+ strlen(name) + strlen(address)+4;
        string ssize = to_string(size);
        sx.addNewDoctor(name, id);
        if (offset == -1) {
            Dfile.open("doctor.txt",ios::in|ios::out|ios::app);
            string iddd = id;
            string Name = name;
            string Address = address;
            Dfile << size << "|" << iddd << "|" << Name << "|"<<Address<<"\n";
            Dfile.close();
            px.add_doctor(id, calc());
            
        }
        else
        {
            Dfile.open("doctor.txt",ios::in|ios::out|ios::app);
            //px.add_doctor(id,offset);
            Dfile.seekp(offset,ios::beg);
            Dfile << size << '|' << id <<'|' << name << '|' <<address <<"\n";
            Dfile.close();
        }
    
    //Dfile.close();
    
    
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
     *      get offset from data Dfile
     *      add doctor to doctor vector
     *
     * }
     *      save Dfile
     *      add doctor to primary index
     *      add doctor to secondary index
     * */
}

void Doc::Delete(char * id){
    /*
     * char * offset = px.delete(id);
     * if( offset != (char*)'-1')
     * {
     *      search in doctor Dfile for the offset
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
        Dfile.open("doctor.txt",ios::app);
        if(Dfile.is_open())
        {
            Dfile.seekg(stoi(string(offset)),ios::beg);
            Dfile.getline(this->id,'|');
            Dfile.seekp(Dfile.tellg(),ios::beg);
            Dfile << "deleted";
            Dfile.getline(this->id,'|');
            Dfile.getline(name,'|');
            
            sx.delete_doctor_name(name,id);
            avl.add(stoi(string(offset)));
            app.Delete_by_Doctor(id);
        }
        assert(Dfile.is_open());
        Dfile.close();
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
    Dfile.open("doctor.txt",ios::in | ios::out | ios::trunc);
    assert(Dfile.is_open());
    if(Dfile.is_open())
    {
        Dfile.seekg(offset,ios::beg);
        char* length;
        Dfile.getline(length,'|');
        Dfile.getline(id,'|');
        int pos = Dfile.tellg();
        Dfile.getline(name,'|');
        Dfile.seekp(pos,ios::beg);
        Dfile << newname;
        
        int newOffset = calc();
        px.update_doctor(ID,newOffset);
        sx.updateDoctorName(string(ID),string(newname),string(name));
        calc();
    }
    Dfile.close();
 
}

void Doc::print() {

    ifstream Dfile("doctor.txt");
    if (!Dfile.is_open()) {
        cerr << "Error: Unable to open doctor.txt file\n";
        return;
    }

    string line;
    while (getline(Dfile, line)) {
        vector<string> fields = split(line, '|');
        if (fields.size() == 4) {
            cout << "Doctor ID: " << fields[1]
                      << " Name: " << fields[2]
                      << " Address: " << fields[3] << "\n";
        } else {
            cerr << "Error: Malformed line: " << line << "\n";
        }
    }

    if (Dfile.eof()) {
        cout << "All doctors displayed.\n";
    } else if (Dfile.fail()) {
        cerr << "Error: Read failure.\n";
    }

    Dfile.close();
}

vector<string> Doc::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
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
    Dfile.open("doctor.txt" , ios::in | ios::out);
    if(Dfile.is_open()) {
        avl.clear();
        string line;
        int currentOffset=0;
        int rowLength=0;
        while (getline(Dfile, line)) {
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
        Dfile.close();
        return currentOffset-rowLength;
    }
    
}
