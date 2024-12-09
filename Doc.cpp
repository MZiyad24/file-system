#include "Doc.h"
#include "bits/stdc++.h"
using namespace std;

Doc::Doc(const string& prim_Dfilename, const string& sec_Dfilename) : px(), sx() {}

void Doc::add(char* id, char * name, char* address){
    calc();
    int check = px.search_doctor(id);
    if(check!= -1)
    {
        cout<<"doctor already exists!!!! \n";
        Dfile.close();
        return;
    }
    int offset = avl.get();
        int size = strlen(id)+ strlen(name) + strlen(address)+3+sizeof(int);
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
            Dfile.open("doctor.txt",ios::in|ios::out);
            Dfile.seekg(offset,ios::beg);
            string lng="";
            getline(Dfile,lng);
            vector<string>row=split(lng,'|');
            //Dfile.read((char*)&lng,sizeof(int));
            if(size> stoi(row[0]))
            {
                cout<<"The entered record's size is too large to fit the deleted one \n";
                string iddd = id;
                string Name = name;
                string Address = address;
                Dfile << size << "|" << iddd << "|" << Name << "|"<<Address<<"\n";
                Dfile.close();
                px.add_doctor(id, calc());
            }
            else {
                int diff = stoi(row[0])-size;
                string s ="";
                for(int i =0 ;i<diff ; i++)
                {
                    s+=' ';
                }
                px.add_doctor(id,offset);
                Dfile.seekp(offset,ios::beg);
                Dfile << size << '|' << id << '|' << name << '|' << address << s << "\n";
            }
            Dfile.close();
        }
        
}

void Doc::Delete(char * id){
    char * offset;
    strcpy(offset,px.delete_doctor(id));
    if(strcmp(offset,"-1") !=0)
    {
        Dfile.open("doctor.txt",ios::in | ios::out);
        if(Dfile.is_open())
        {
            string temp = offset;
            int ser;
            stringstream ss(temp);
            ss >> ser;
            Dfile.seekg(ser, ios::beg);
            string line;
            getline(Dfile, line);
    
            vector<string>row=split(line,'|');
            
            string ID = row[1];
            string NAME = row[2];
            string ADDRESS = row[3];
            string LENGTH = row[0];
            int len = strlen("*") + (int)NAME.size()+ (int)ADDRESS.size()+3+sizeof(int);
            Dfile.seekp(ser, ios::beg);
            Dfile << len << '|' <<"*" <<'|'<< NAME <<'|'<< ADDRESS << "\n";
            Dfile.close();
            sx.delete_doctor_name(NAME, id);
            avl.add(ser);
            app.Delete_by_Doctor(id);
        }
        
    }

}

void Doc::updata_docName(char* ID,char* newname) {
     //  we made some changes
    int offset=px.search_doctor(ID);
    Dfile.open("doctor.txt",ios::in | ios::out );
    if(Dfile.is_open())
    {
        Dfile.seekg(offset,ios::beg);
        string line = "";
        getline(Dfile,line);
        vector<string> lines = split(line,'|');
        int length ;
        stringstream ss(lines[2]) ;
        ss>>length;
        if(strlen(newname) > (int)lines[2].size())
        {
            cout<<"cannot update with a name with that size! \n";
            return;
        }
        int diff = lines[2].size() - strlen(newname);
        string s ="";
        for(int i =0 ;i<diff ; i++)
        {
            s+=' ';
        }
        Dfile.seekp(offset+sizeof(int)+(int)lines[1].size(),ios::beg);
        Dfile << newname << s ;
        string n = lines[2];
        sx.updateDoctorName(string(ID),string(newname),n);
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

void Doc::search_byId(const char * id){
    int off=px.search_doctor(id);
    Dfile.open("doctor.txt",ios::in|ios::out);
    Dfile.seekg(off,ios::beg);
    string lin ="";
    getline(Dfile,lin);
    vector<string>line = split(lin,'|');
    cout<<"Doctor id : "<<id<<"  Doctor Name : "<<line[2]<<"  Doctor Address : "<<line[3]<<"\n";
}

void Doc::search(char * name)
{
    vector<string>ans;
    ans=sx.search_by_doctor_name(name);
    cout<<"The IDs associated with the name "<<name<<"are: \n";
    for(auto&entry: ans){
        cout<<entry << " ";
    }
    cout<<"\n";
    
}

void Doc::search_byName(const char * name)
{
    vector<string>ans;
    ans=sx.search_by_doctor_name(name);
    for(auto&entry: ans){
        const char* name_cstr = entry.c_str();
        int off=px.search_doctor(name_cstr);
        Dfile.open("doctor.txt",ios::in|ios::out);
        Dfile.seekg(off,ios::beg);
        string lin ="";
        getline(Dfile,lin);
        vector<string>line = split(lin,'|');
        cout<<"Doctor id : "<<line[1]<<"  Doctor Name : "<<line[2]<<"  Doctor Address : "<<line[3]<<"\n";
        Dfile.close();
    }
    cout<<"\n";
    
}

void Doc::getName_byId(const char *id) {
    int off=px.search_doctor(id);
    Dfile.open("doctor.txt",ios::in|ios::out);
    Dfile.seekg(off,ios::beg);
    string lin ="";
    getline(Dfile,lin);
    vector<string>line = split(lin,'|');
    cout<<"the Doctor Name : "<<line[2]<<"\n";
    Dfile.close();
}

void Doc::getAdress_byId(const char *id) {
    int off=px.search_doctor(id);
    Dfile.open("doctor.txt",ios::in|ios::out);
    Dfile.seekg(off,ios::beg);
    string lin ="";
    getline(Dfile,lin);
    vector<string>line = split(lin,'|');
    cout<<"the Doctor Address : "<<line[3]<<"\n";
    Dfile.close();
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
            if (id == "*") {
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
